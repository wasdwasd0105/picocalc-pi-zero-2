#!/bin/bash

# Check if running as root
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root. Use sudo ./setup_display.sh" 
   exit 1
fi

# Introduction and confirmation
clear
echo "TFT 4\" Setup Script for ILI9488 on PicoCalc with Pi Zero 2"
echo "Tested in December 2024 for TFT 4\" displays with dimensions 320x320."
echo "This process involves modifying system files, downloading files, and installing dependencies."
echo "These changes may affect the functionality of your Raspberry Pi."
echo "At the end of the process, your Raspberry Pi will automatically reboot."
echo "Please make sure your OS is Legacy 32-bit Bullseye Raspberry Pi OS!!!"
echo
read -p "Do you authorize this process and accept full responsibility for any changes? (Y/N): " user_input
if [[ "$user_input" != "Y" && "$user_input" != "y" ]]; then
    echo "No changes have been made. Process aborted."
    exit 0
fi

# Ensure locale settings
export LANGUAGE="en_GB.UTF-8"
export LC_ALL="en_GB.UTF-8"
export LC_CTYPE="en_GB.UTF-8"
export LANG="en_GB.UTF-8"

# Enable SPI using raspi-config
echo "Enabling SPI interface using raspi-config..."
raspi-config nonint do_spi 0

# Begin setup
echo "Starting TFT setup..."

# Update system and install dependencies
echo "Updating the system and installing dependencies..."
apt update && apt upgrade -y
apt install -y cmake git build-essential nano

# Configure fbcp-ili9341
echo "Downloading and configuring fbcp-ili9341..."
if [ ! -d "fbcp-ili9341-picocalc" ]; then
    git clone https://github.com/wasdwasd0105/fbcp-ili9341-picocalc.git
fi
cd fbcp-ili9341-picocalc
mkdir -p build
cd build
rm -rf *
cmake -DUSE_GPU=ON -DSPI_BUS_CLOCK_DIVISOR=12 \
      -DGPIO_TFT_DATA_CONTROL=24 -DGPIO_TFT_RESET_PIN=25 \
      -DILI9488=ON -DUSE_DMA_TRANSFERS=ON -DDMA_TX_CHANNEL=5 -DDMA_RX_CHANNEL=1 -DSTATISTICS=0 ..
make -j$(nproc)
sudo install fbcp-ili9341 /usr/local/bin/

# Prompt before modifying config.txt
echo
echo "The script will now modify the Raspberry Pi configuration file (config.txt)."
echo "Existing lines that are changed will be commented with a note."
read -p "Do you accept these changes and wish to proceed? (Y/N): " config_input
if [[ "$config_input" != "Y" && "$config_input" != "y" ]]; then
    echo "No changes have been made to the configuration file. Process aborted."
    exit 0
fi

# Define the configuration file path
CONFIG_FILE="/boot/firmware/config.txt"
if [ ! -f "$CONFIG_FILE" ]; then
    CONFIG_FILE="/boot/config.txt"
fi

update_config() {
    local key=$1
    local value=$2

    # Check if the line already exists
    if grep -q "^$key" "$CONFIG_FILE"; then
        # Remove any preceding # and update value if necessary
        sed -i "s/^#$key/$key/" "$CONFIG_FILE"
        if [ -n "$value" ]; then
            sed -i "s|^$key.*|$key=$value|" "$CONFIG_FILE"
        fi
    else
        # Add the line if it doesn't exist
        if [ -z "$value" ]; then
            echo "$key" >> "$CONFIG_FILE"
        else
            echo "$key=$value" >> "$CONFIG_FILE"
        fi
    fi
}

remove_duplicates() {
    local file=$1
    # Retain line breaks and remove duplicate lines
    awk '!seen[$0]++' "$file" > "${file}.tmp"
    mv "${file}.tmp" "$file"
}

# Comment the line max_framebuffers=2 if it exists
if grep -q "^max_framebuffers=2" "$CONFIG_FILE"; then
    sed -i "s|^max_framebuffers=2|#max_framebuffers=2 (line commented for TFT ILI9488 installation on $(date +%m/%d/%Y))|" "$CONFIG_FILE"
fi


# Comment the dtoverlay=vc4-kms-v3d line
sed -i "s|^dtoverlay=vc4-kms-v3d|#dtoverlay=vc4-kms-v3d (line commented for TFT ILI9488 installation on $(date +%m/%d/%Y))|" "$CONFIG_FILE"

sudo sed -i '/^\[pi4\]/s/^/#/' "$CONFIG_FILE"


# Add required configuration lines
echo "#Modifications for ILI9488 installation implemented by the script on $(date +%m/%d/%Y)" >> "$CONFIG_FILE"
update_config "dtoverlay" "spi0-0cs"
update_config "dtparam" "spi=on"
update_config "hdmi_force_hotplug" "1"
update_config "hdmi_cvt" "320 320 60 1 0 0 0"
update_config "hdmi_group" "2"
update_config "hdmi_mode" "87"
update_config "gpu_mem" "128"
echo "# Utilized for TFT ILI9488 setup script by AdamoMD" >> "$CONFIG_FILE"
echo "# https://github.com/adamomd/4inchILI9488RpiScript/" >> "$CONFIG_FILE"
echo "# Feel free to send feedback and suggestions." >> "$CONFIG_FILE"

# Remove duplicates in config.txt
echo "Removing duplicate lines in config.txt..."
remove_duplicates "$CONFIG_FILE"

# Configure sudoers for fbcp-ili9341
echo "Setting permissions in sudoers..."
VISUDO_FILE="/etc/sudoers.d/fbcp-ili9341"
if [ ! -f "$VISUDO_FILE" ]; then
    echo "ALL ALL=(ALL) NOPASSWD: /usr/local/bin/fbcp-ili9341" > "$VISUDO_FILE"
    chmod 440 "$VISUDO_FILE"
fi

# Set binary permissions
echo "Configuring permissions for fbcp-ili9341..."
chmod u+s /usr/local/bin/fbcp-ili9341

# Configure rc.local to start fbcp-ili9341
echo "Configuring /etc/rc.local..."
RC_LOCAL="/etc/rc.local"
if [ ! -f "$RC_LOCAL" ]; then
    cat <<EOT > "$RC_LOCAL"
#!/bin/bash
# rc.local
# This script is executed at the end of each multi-user runlevel.

# Start fbcp-ili9341
/usr/local/bin/fbcp-ili9341 >> /var/log/fbcp-ili9341.log 2>&1 &

exit 0
EOT
    chmod +x "$RC_LOCAL"
else
    if ! grep -q "fbcp-ili9341" "$RC_LOCAL"; then
        sed -i '/exit 0/i \\n# Start fbcp-ili9341\n/usr/local/bin/fbcp-ili9341 >> /var/log/fbcp-ili9341.log 2>&1 &' "$RC_LOCAL"
    fi
fi

# Remove duplicates in rc.local
echo "Removing duplicate lines in rc.local..."
remove_duplicates "$RC_LOCAL"

# Enable and start rc.local service
echo "Enabling rc.local service..."
sudo chmod +x /etc/rc.local
sudo systemctl enable rc-local
sudo systemctl start rc-local

# Finish and force reboot
echo "Finalizing processes..."
killall -9 fbcp-ili9341 2>/dev/null || true
sync

echo -e "\nSetup complete. The Raspberry Pi will now reboot."
sudo reboot
