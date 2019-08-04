#ifndef GXO_INPUT_DEFINE
#define GXO_INPUT_DEFINE

#define GXO_RELEASE                0

#define GXO_PRESS                  1

#define GXO_REPEAT                 2


#define GXO_HAT_CENTERED           0
#define GXO_HAT_UP                 1
#define GXO_HAT_RIGHT              2
#define GXO_HAT_DOWN               4
#define GXO_HAT_LEFT               8
#define GXO_HAT_RIGHT_UP           (GXO_HAT_RIGHT | GXO_HAT_UP)
#define GXO_HAT_RIGHT_DOWN         (GXO_HAT_RIGHT | GXO_HAT_DOWN)
#define GXO_HAT_LEFT_UP            (GXO_HAT_LEFT  | GXO_HAT_UP)
#define GXO_HAT_LEFT_DOWN          (GXO_HAT_LEFT  | GXO_HAT_DOWN)


/* The unknown key */
#define GXO_KEY_UNKNOWN            -1

/* Printable keys */
#define GXO_KEY_SPACE              32
#define GXO_KEY_APOSTROPHE         39  /* ' */
#define GXO_KEY_COMMA              44  /* , */
#define GXO_KEY_MINUS              45  /* - */
#define GXO_KEY_PERIOD             46  /* . */
#define GXO_KEY_SLASH              47  /* / */
#define GXO_KEY_0                  48
#define GXO_KEY_1                  49
#define GXO_KEY_2                  50
#define GXO_KEY_3                  51
#define GXO_KEY_4                  52
#define GXO_KEY_5                  53
#define GXO_KEY_6                  54
#define GXO_KEY_7                  55
#define GXO_KEY_8                  56
#define GXO_KEY_9                  57
#define GXO_KEY_SEMICOLON          59  /* ; */
#define GXO_KEY_EQUAL              61  /* = */
#define GXO_KEY_A                  65
#define GXO_KEY_B                  66
#define GXO_KEY_C                  67
#define GXO_KEY_D                  68
#define GXO_KEY_E                  69
#define GXO_KEY_F                  70
#define GXO_KEY_G                  71
#define GXO_KEY_H                  72
#define GXO_KEY_I                  73
#define GXO_KEY_J                  74
#define GXO_KEY_K                  75
#define GXO_KEY_L                  76
#define GXO_KEY_M                  77
#define GXO_KEY_N                  78
#define GXO_KEY_O                  79
#define GXO_KEY_P                  80
#define GXO_KEY_Q                  81
#define GXO_KEY_R                  82
#define GXO_KEY_S                  83
#define GXO_KEY_T                  84
#define GXO_KEY_U                  85
#define GXO_KEY_V                  86
#define GXO_KEY_W                  87
#define GXO_KEY_X                  88
#define GXO_KEY_Y                  89
#define GXO_KEY_Z                  90
#define GXO_KEY_LEFT_BRACKET       91  /* [ */
#define GXO_KEY_BACKSLASH          92  /* \ */
#define GXO_KEY_RIGHT_BRACKET      93  /* ] */
#define GXO_KEY_GRAVE_ACCENT       96  /* ` */
#define GXO_KEY_WORLD_1            161 /* non-US #1 */
#define GXO_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define GXO_KEY_ESCAPE             256
#define GXO_KEY_ENTER              257
#define GXO_KEY_TAB                258
#define GXO_KEY_BACKSPACE          259
#define GXO_KEY_INSERT             260
#define GXO_KEY_DELETE             261
#define GXO_KEY_RIGHT              262
#define GXO_KEY_LEFT               263
#define GXO_KEY_DOWN               264
#define GXO_KEY_UP                 265
#define GXO_KEY_PAGE_UP            266
#define GXO_KEY_PAGE_DOWN          267
#define GXO_KEY_HOME               268
#define GXO_KEY_END                269
#define GXO_KEY_CAPS_LOCK          280
#define GXO_KEY_SCROLL_LOCK        281
#define GXO_KEY_NUM_LOCK           282
#define GXO_KEY_PRINT_SCREEN       283
#define GXO_KEY_PAUSE              284
#define GXO_KEY_F1                 290
#define GXO_KEY_F2                 291
#define GXO_KEY_F3                 292
#define GXO_KEY_F4                 293
#define GXO_KEY_F5                 294
#define GXO_KEY_F6                 295
#define GXO_KEY_F7                 296
#define GXO_KEY_F8                 297
#define GXO_KEY_F9                 298
#define GXO_KEY_F10                299
#define GXO_KEY_F11                300
#define GXO_KEY_F12                301
#define GXO_KEY_F13                302
#define GXO_KEY_F14                303
#define GXO_KEY_F15                304
#define GXO_KEY_F16                305
#define GXO_KEY_F17                306
#define GXO_KEY_F18                307
#define GXO_KEY_F19                308
#define GXO_KEY_F20                309
#define GXO_KEY_F21                310
#define GXO_KEY_F22                311
#define GXO_KEY_F23                312
#define GXO_KEY_F24                313
#define GXO_KEY_F25                314
#define GXO_KEY_KP_0               320
#define GXO_KEY_KP_1               321
#define GXO_KEY_KP_2               322
#define GXO_KEY_KP_3               323
#define GXO_KEY_KP_4               324
#define GXO_KEY_KP_5               325
#define GXO_KEY_KP_6               326
#define GXO_KEY_KP_7               327
#define GXO_KEY_KP_8               328
#define GXO_KEY_KP_9               329
#define GXO_KEY_KP_DECIMAL         330
#define GXO_KEY_KP_DIVIDE          331
#define GXO_KEY_KP_MULTIPLY        332
#define GXO_KEY_KP_SUBTRACT        333
#define GXO_KEY_KP_ADD             334
#define GXO_KEY_KP_ENTER           335
#define GXO_KEY_KP_EQUAL           336
#define GXO_KEY_LEFT_SHIFT         340
#define GXO_KEY_LEFT_CONTROL       341
#define GXO_KEY_LEFT_ALT           342
#define GXO_KEY_LEFT_SUPER         343
#define GXO_KEY_RIGHT_SHIFT        344
#define GXO_KEY_RIGHT_CONTROL      345
#define GXO_KEY_RIGHT_ALT          346
#define GXO_KEY_RIGHT_SUPER        347
#define GXO_KEY_MENU               348

#define GXO_KEY_LAST               GXO_KEY_MENU


#define GXO_MOD_SHIFT           0x0001

#define GXO_MOD_CONTROL         0x0002

#define GXO_MOD_ALT             0x0004

#define GXO_MOD_SUPER           0x0008

#define GXO_MOD_CAPS_LOCK       0x0010

#define GXO_MOD_NUM_LOCK        0x0020

#define GXO_MOUSE_BUTTON_1         0
#define GXO_MOUSE_BUTTON_2         1
#define GXO_MOUSE_BUTTON_3         2
#define GXO_MOUSE_BUTTON_4         3
#define GXO_MOUSE_BUTTON_5         4
#define GXO_MOUSE_BUTTON_6         5
#define GXO_MOUSE_BUTTON_7         6
#define GXO_MOUSE_BUTTON_8         7
#define GXO_MOUSE_BUTTON_LAST      GXO_MOUSE_BUTTON_8
#define GXO_MOUSE_BUTTON_LEFT      GXO_MOUSE_BUTTON_1
#define GXO_MOUSE_BUTTON_RIGHT     GXO_MOUSE_BUTTON_2
#define GXO_MOUSE_BUTTON_MIDDLE    GXO_MOUSE_BUTTON_3

#endif // !GXO_INPUT_DEFINE
