#pragma once

// Keycodes from glfw3.h

/* The unknown key */
#define IBX_KEY_UNKNOWN            -1

/* Printable keys */
#define IBX_KEY_SPACE              32
#define IBX_KEY_APOSTROPHE         39 // 39 is the ASCII value of '''
#define IBX_KEY_COMMA              44 // 44 is the ASCII value of ','
#define IBX_KEY_MINUS              45 // 45 is the ASCII value of '-'
#define IBX_KEY_PERIOD             46 // 46 is the ASCII value of '.'
#define IBX_KEY_SLASH              47 // 47 is the ASCII value of '/'
#define IBX_KEY_0                  48 // 48 is the ASCII value of '0'
#define IBX_KEY_1                  49 // 49 is the ASCII value of '1'
#define IBX_KEY_2                  50 // 50 is the ASCII value of '2'
#define IBX_KEY_3                  51 // 51 is the ASCII value of '3'
#define IBX_KEY_4                  52 // 52 is the ASCII value of '4'
#define IBX_KEY_5                  53 // 53 is the ASCII value of '5'
#define IBX_KEY_6                  54 // 54 is the ASCII value of '6'
#define IBX_KEY_7                  55 // 55 is the ASCII value of '7'
#define IBX_KEY_8                  56 // 56 is the ASCII value of '8'
#define IBX_KEY_9                  57 // 57 is the ASCII value of '9'
#define IBX_KEY_SEMICOLON          59 // 59 is the ASCII value of ';'
#define IBX_KEY_EQUAL              61 // 61 is the ASCII value of '='
#define IBX_KEY_A                  65 // 65 is the ASCII value of 'A'
#define IBX_KEY_B                  66 // 66 is the ASCII value of 'B'
#define IBX_KEY_C                  67 // 67 is the ASCII value of 'C'
#define IBX_KEY_D                  68 // 68 is the ASCII value of 'D'
#define IBX_KEY_E                  69 // 69 is the ASCII value of 'E'
#define IBX_KEY_F                  70 // 70 is the ASCII value of 'F'
#define IBX_KEY_G                  71 // 71 is the ASCII value of 'G'
#define IBX_KEY_H                  72 // 72 is the ASCII value of 'H'
#define IBX_KEY_I                  73 // 73 is the ASCII value of 'I'
#define IBX_KEY_J                  74 // 74 is the ASCII value of 'J'
#define IBX_KEY_K                  75 // 75 is the ASCII value of 'K'
#define IBX_KEY_L                  76 // 76 is the ASCII value of 'L'
#define IBX_KEY_M                  77 // 77 is the ASCII value of 'M'
#define IBX_KEY_N                  78 // 78 is the ASCII value of 'N'
#define IBX_KEY_O                  79 // 79 is the ASCII value of 'O'
#define IBX_KEY_P                  80 // 80 is the ASCII value of 'P'
#define IBX_KEY_Q                  81 // 81 is the ASCII value of 'Q'
#define IBX_KEY_R                  82 // 82 is the ASCII value of 'R'
#define IBX_KEY_S                  83 // 83 is the ASCII value of 'S'
#define IBX_KEY_T                  84 // 84 is the ASCII value of 'T'
#define IBX_KEY_U                  85 // 85 is the ASCII value of 'U'
#define IBX_KEY_V                  86 // 86 is the ASCII value of 'V'
#define IBX_KEY_W                  87 // 87 is the ASCII value of 'W'
#define IBX_KEY_X                  88 // 88 is the ASCII value of 'X'
#define IBX_KEY_Y                  89 // 89 is the ASCII value of 'Y'
#define IBX_KEY_Z                  90 // 90 is the ASCII value of 'Z'
#define IBX_KEY_LEFT_BRACKET       91 // 91 is the ASCII value of '['
#define IBX_KEY_BACKSLASH          92 // 92 is the ASCII value of '\'
#define IBX_KEY_RIGHT_BRACKET      93 // 93 is the ASCII value of ']'
#define IBX_KEY_GRAVE_ACCENT       96 // 96 is the ASCII value of '`'
#define IBX_KEY_WORLD_1            161 /* non-US #1 */
#define IBX_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define IBX_KEY_ESCAPE             256
#define IBX_KEY_ENTER              257
#define IBX_KEY_TAB                258
#define IBX_KEY_BACKSPACE          259
#define IBX_KEY_INSERT             260
#define IBX_KEY_DELETE             261
#define IBX_KEY_RIGHT              262
#define IBX_KEY_LEFT               263
#define IBX_KEY_DOWN               264
#define IBX_KEY_UP                 265
#define IBX_KEY_PAGE_UP            266
#define IBX_KEY_PAGE_DOWN          267
#define IBX_KEY_HOME               268
#define IBX_KEY_END                269
#define IBX_KEY_CAPS_LOCK          280
#define IBX_KEY_SCROLL_LOCK        281
#define IBX_KEY_NUM_LOCK           282
#define IBX_KEY_PRINT_SCREEN       283
#define IBX_KEY_PAUSE              284
#define IBX_KEY_F1                 290
#define IBX_KEY_F2                 291
#define IBX_KEY_F3                 292
#define IBX_KEY_F4                 293
#define IBX_KEY_F5                 294
#define IBX_KEY_F6                 295
#define IBX_KEY_F7                 296
#define IBX_KEY_F8                 297
#define IBX_KEY_F9                 298
#define IBX_KEY_F10                299
#define IBX_KEY_F11                300
#define IBX_KEY_F12                301
#define IBX_KEY_F13                302
#define IBX_KEY_F14                303
#define IBX_KEY_F15                304
#define IBX_KEY_F16                305
#define IBX_KEY_F17                306
#define IBX_KEY_F18                307
#define IBX_KEY_F19                308
#define IBX_KEY_F20                309
#define IBX_KEY_F21                310
#define IBX_KEY_F22                311
#define IBX_KEY_F23                312
#define IBX_KEY_F24                313
#define IBX_KEY_F25                314
#define IBX_KEY_KP_0               320
#define IBX_KEY_KP_1               321
#define IBX_KEY_KP_2               322
#define IBX_KEY_KP_3               323
#define IBX_KEY_KP_4               324
#define IBX_KEY_KP_5               325
#define IBX_KEY_KP_6               326
#define IBX_KEY_KP_7               327
#define IBX_KEY_KP_8               328
#define IBX_KEY_KP_9               329
#define IBX_KEY_KP_DECIMAL         330
#define IBX_KEY_KP_DIVIDE          331
#define IBX_KEY_KP_MULTIPLY        332
#define IBX_KEY_KP_SUBTRACT        333
#define IBX_KEY_KP_ADD             334
#define IBX_KEY_KP_ENTER           335
#define IBX_KEY_KP_EQUAL           336
#define IBX_KEY_LEFT_SHIFT         340
#define IBX_KEY_LEFT_CONTROL       341
#define IBX_KEY_LEFT_ALT           342
#define IBX_KEY_LEFT_SUPER         343
#define IBX_KEY_RIGHT_SHIFT        344
#define IBX_KEY_RIGHT_CONTROL      345
#define IBX_KEY_RIGHT_ALT          346
#define IBX_KEY_RIGHT_SUPER        347
#define IBX_KEY_MENU               348