#include <stdint.h>

struct KeyboardEvent_t {
    uint8_t type;
    uint8_t keycode;
};

class Keyboard_Class {
    public:
        void Init();
        void update();
        bool NumlockState;
        bool CapslockState;
        bool LSHIFTState;
        bool RSHIFTState;
        bool LCTRLState;
        bool RCTRLState;
        bool LALTState;
        bool ALTGRState;
        KeyboardEvent_t readEvent(bool wait);
        char getKeyChar(uint8_t keycode);
        struct _KEYCODES {
            enum _KEYCODES_ {
                ESC, K1, K2, K3, K4, K5, K6, K7,
                K8, K9, K0, MINUS, EQUAL, BACKSPACE, TAB, Q,
                W, E, R, T, Y, U, I, O,
                P, LBRACKET, RBRACKET, ENTER, LCTRL, A, S, D,
                F, G, H, J, K, L, SEMICOLMUMN, QUOTE,
                BACKTICK, LSHIFT, BACKSLASH, Z, X, C, V, B,
                N, M, COMMA, DOT, FSLASH, RSHIFT, KPMULT, LALT,
                SPACE, CAPSLOCK, F1, F2, F3, F4, F5, F6,
                F7, F8, F9, F10, NUMLOCK, SCRLOCK, KP7, KP8,
                KP9, KPMINUS, KP4, KP5, KP6, KPPLUS, KP1, KP2,
                KP3, KP0, KPDOT, F11, F12, MMPT, MMNT, KPENTER,
                RCTRL, MMMUTE, MMCALC, MMPLAY, MMSTOP, MMVD, MMVU,MMHOME,
                KPSLASH, ALTGR, HOME, UP, PGUP, LEFT, RIGHT, END,
                DOWN, PGDOWN, INSERT, DEL, LGUI, RGUI, APPS, POWER,
                SLEEP, WAKE, WWSEARCH, WWFAVORITE, WWREFRESH, WWSTOP, WWFORWARD, WWBACK,
                MMMY, MMEMAIL, MMSELECT
            };
        } KEYCODES;
        struct _EVENTTYPES {
            enum _EVENTTYPES_ {
                INVALID,
                PRESSED,
                RELEASED
            };
        } EVENTTYPES;
};

extern Keyboard_Class Keyboard;