#!/bin/bash
set -e

MODULE_NAME=picocalc_kbd
SRC_DIR=./picocalc_kbd
DTBO_DIR=./picocalc_kbd/dts
KO_FILE=${MODULE_NAME}.ko
DTBO_FILE=${MODULE_NAME}.dtbo

echo "🔧 Step 1: Installing dependencies..."
sudo apt update
sudo apt install -y \
    build-essential \
    raspberrypi-kernel-headers \
    device-tree-compiler \
    git

echo "🔧 Step 2: Building kernel module in ${SRC_DIR}..."
make -C ${SRC_DIR}

echo "📁 Step 3: Installing kernel module to system..."
sudo mkdir -p /lib/modules/$(uname -r)/extra
sudo cp ${SRC_DIR}/${KO_FILE} /lib/modules/$(uname -r)/extra/
sudo depmod

echo "📄 Step 4: Installing DTBO to /boot/overlays/..."
sudo cp ${DTBO_DIR}/${DTBO_FILE} /boot/overlays/

echo "📝 Step 5: Updating /boot/config.txt..."
CONFIG=/boot/config.txt
grep -q "^dtoverlay=${MODULE_NAME}" $CONFIG || echo "dtoverlay=${MODULE_NAME}" | sudo tee -a $CONFIG
grep -q "^dtparam=i2c_arm=on" $CONFIG || echo "dtparam=i2c_arm=on" | sudo tee -a $CONFIG

echo "✅ Installation complete."
echo "🔁 Reboot now to activate the driver:"
echo "    sudo reboot"
