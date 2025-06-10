/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Keyboard Driver for Blackberry Keyboards BBQ10 from arturo182. Software written by wallComputer.
 * bbq10kbd_codes.h: Keyboard Layout and Scancodes-Keycodes mapping.
 */

#ifndef BBQ10KBD_PMOD_CODES_H_
#define BBQ10KBD_PMOD_CODES_H_

/*
 *					BBQ10KBD PMOD KEYBOARD LAYOUT
 *
 *	+------+-----+----+----+----+----+----+-----+-----+-------+
 *	|#     |1    |2   |3   |(   |   )|_   |    -|    +|      @|
 *	|  Q   |  W  | E  | R  | T  |  Y |  U |  I  |  O  |   P   |
 *	|    S+|   S-|PgUp|PgDn|   \|UP  |^   |=    |{    |}      |
 *	+------+-----+----+----+----+----+----+-----+-----+-------+
 *	|*     |4    |5   |6   |/   |   :|;   |    '|    "|    ESC|
 *	|  A   |  S  | D  | F  | G  |  H |  J |  K  |  L  |  BKSP |
 *	|     ?|   Sx|   [|   ]|LEFT|HOME|RGHT|V+   |V-   |DLT    |
 *	+------+-----+----+----+----+----+----+-----+-----+-------+
 *	|      |7    |8   |9   |?   |   !|,   |    .|    `|       |
 *	|LFTALT|  Z  | X  | C  | V  |  B |  N |  M  |  $  | ENTER |
 *	|      |   K+|  K-|   °|   <|DOWN|>   |MENU |Vx   |       |
 *	+------+-----+----+----+----+----+----+-----+-----+-------+
 *	|            |0   |TAO                |     |             |
 *	| LEFT_SHIFT | ~  |       SPACE       |RTALT| RIGHT_SHIFT |
 *	|            |  Kx|                  &|     |             |
 *	+------------+----+-------------------+-----+-------------+
 *
 * Notes:
 * Most Important to know:
 * To present a character as mentioned above a key in the above layout, use LFTALT + Key.
 * To present a character as mentioned below a key in the above layout, use RTALT + Key.
 *
 * Changes from arturo182's layout, if you are used to that, it's good to know these changes.
 * 1. Sym Key (Scancode 0x1D) on Keyboard is mapped to RTALT.
 * 2. Note "|" above Enter Key as per original keyboard layout is removed and added under "A"
 * 3. The external buttons on the Keyboard Featherwing have been changed as below:
 *__3.1 Leftmost Button changed from Menu Key to Left Ctrl Key.
 *__3.2 Innet Left Button changed from Left Ctrl Key to Page Up Key.
 *__3.3 Inner Right Button changed from Back Key to Page Down Key.
 *__3.4 Outer Right Button changed from Left Shift Key to Menu Key.
 *__3.5 Center Key of 5-way Button changed from Enter Key to Home Key.
 */


#define NUM_KEYCODES	256

static unsigned short keycodes[NUM_KEYCODES] = {
	

	[0xA1] = KEY_LEFTALT,
	[0xA2] = KEY_LEFTSHIFT,
	[0xA3] = KEY_RIGHTSHIFT,
	[0xA5] = KEY_LEFTCTRL,

	['a'] = KEY_A,
	['b'] = KEY_B,
	['c'] = KEY_C,
	['d'] = KEY_D,
	['e'] = KEY_E,
	['f'] = KEY_F,
	['g'] = KEY_G,
	['h'] = KEY_H,
	['i'] = KEY_I,
	['j'] = KEY_J,
	['k'] = KEY_K,
	['l'] = KEY_L,
	['m'] = KEY_M,
	['n'] = KEY_N,
	['o'] = KEY_O,
	['p'] = KEY_P,
	['q'] = KEY_Q,
	['r'] = KEY_R,
	['s'] = KEY_S,
	['t'] = KEY_T,
	['u'] = KEY_U,
	['v'] = KEY_V,
	['w'] = KEY_W,
	['x'] = KEY_X,
	['y'] = KEY_Y,
	['z'] = KEY_Z,

	['A'] = KEY_A,
	['B'] = KEY_B,
	['C'] = KEY_C,
	['D'] = KEY_D,
	['E'] = KEY_E,
	['F'] = KEY_F,
	['G'] = KEY_G,
	['H'] = KEY_H,
	['I'] = KEY_I,
	['J'] = KEY_J,
	['K'] = KEY_K,
	['L'] = KEY_L,
	['M'] = KEY_M,
	['N'] = KEY_N,
	['O'] = KEY_O,
	['P'] = KEY_P,
	['Q'] = KEY_Q,
	['R'] = KEY_R,
	['S'] = KEY_S,
	['T'] = KEY_T,
	['U'] = KEY_U,
	['V'] = KEY_V,
	['W'] = KEY_W,
	['X'] = KEY_X,
	['Y'] = KEY_Y,
	['Z'] = KEY_Z,

	[' '] = KEY_SPACE,
	['~'] = KEY_0,
	['$'] = KEY_4,

	['\b'] = KEY_BACKSPACE,
	['\n'] = KEY_ENTER,
	/*
	 * As per the kernel, a keyboard needs to indicate, in advance, which key values it can report.
	 * In order to that, it should have unique scancodes pointing those scancode-keycode pairs.
	 * With the configuration set for now, the keyboard never outputs lower case letters, numbers, and equal to sign.
	 * We can use these as bogus scancodes, and map the keys we want the keyboard to say its pressed when modifier keys are used.
	 * This can change however, in case future software versions of the keyboard micrcontroller itself changes to output other stuff.
	 */
	['0'] = KEY_0,
	['1'] = KEY_1,
	['2'] = KEY_2,
	['3'] = KEY_3,
	['4'] = KEY_4,
	['5'] = KEY_5,
	['6'] = KEY_6,
	['7'] = KEY_7,
	['8'] = KEY_8,
	['9'] = KEY_9,

	[0x81] = KEY_F1,
	[0x82] = KEY_F2,
	[0x83] = KEY_F3,
	[0x84] = KEY_F4,
	[0x85] = KEY_F5,
	[0x86] = KEY_F6,
	[0x87] = KEY_F7,
	[0x88] = KEY_F8,
	[0x89] = KEY_F9,
	[0x90] = KEY_F10,

	['#'] = KEY_3,
	['@'] = KEY_2,
	[0x08] = KEY_BACKSPACE,
	[0xD4] = KEY_DELETE,
	[0xD5] = KEY_END,
	[0xC1] = KEY_CAPSLOCK,
	[0x09] = KEY_TAB,
	[0xD2] = KEY_HOME,
	[0xB1] = KEY_ESC,
	[0xd0] = KEY_BREAK,
	[0xd0] = KEY_PAUSE,
	['='] = KEY_EQUAL,
	['+'] = KEY_EQUAL,
	['-'] = KEY_MINUS,
	['_'] = KEY_MINUS,
	['\\'] = KEY_BACKSLASH,
	['|'] = KEY_BACKSLASH,
	['!'] = KEY_1,
	[0xD1] = KEY_INSERT,
	['*'] = KEY_8,
	['&'] = KEY_7,
	['^'] = KEY_6,
	['%'] = KEY_5,

	['.'] = KEY_DOT,
	['>'] = KEY_DOT,

	[';'] = KEY_SEMICOLON,
	[':'] = KEY_SEMICOLON,

	[','] = KEY_COMMA,
	['<'] = KEY_COMMA,

	['`'] = KEY_GRAVE,
	['~'] = KEY_GRAVE,

	['"'] = KEY_APOSTROPHE,
	['\''] = KEY_APOSTROPHE,

	['?'] = KEY_SLASH,
	['/'] = KEY_SLASH,

	[')'] = KEY_0,
	['('] = KEY_9,

	[']'] = KEY_RIGHTBRACE,
	['}'] = KEY_RIGHTBRACE,

	['['] = KEY_LEFTBRACE,
	['{'] = KEY_LEFTBRACE,

	[0xb7] = KEY_RIGHT,
	[0xb5] = KEY_UP,
	[0xb6] = KEY_DOWN,
	[0xb4] = KEY_LEFT,
	[0xd6] = KEY_PAGEUP,
	[0xd7] = KEY_PAGEDOWN,
};


#endif
