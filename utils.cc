#include "utils.hpp"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <cstdio>

#define error(msg) fprintf(stderr, "[X11] %s\n", msg);

namespace utils {
   static ::Display* g_X11Display = nullptr;
   
   bool initialize() {
      g_X11Display = ::XOpenDisplay(nullptr);
      if(!g_X11Display) {
         error("Failed to open X11Display");
         return false;
      }

      return true;
   }

   void deinitialize() {
      if(g_X11Display)
         ::XCloseDisplay(g_X11Display);
   }

   KeySym x11_keysym_to_scancode(const KeyCode scancode) {
      switch (scancode) {
      case kKeyBackspace:
         return XK_BackSpace;
      case kKeyTab:
         return XK_Tab;
      case kKeyEnter:
         return XK_Return;
      case kKeyPause:
         return XK_Pause;
      case kKeyScrLock:
         return XK_Scroll_Lock;
      case kKeyEsc:
         return XK_Escape;
      case kKeyDel:
         return XK_Delete;
      case kKeyHome:
         return XK_Home;
      case kKeyLeft:
         return XK_Left;
      case kKeyUp:
         return XK_Up;
      case kKeyRight:
         return XK_Right;
      case kKeyDown:
         return XK_Down;
      case kKeyPageUp:
         return XK_Page_Up;
      case kKeyPageDown:
         return XK_Page_Down;
      case kKeyEnd:
         return XK_End;
      case kKeyPrtscr:
         return XK_Print;
      case kKeyInsert:
         return XK_Insert;
      case kKeyMenu:
         return XK_Menu;
      case kKeyNumLock:
         return XK_Num_Lock;
      case kKeyEnterPad:
         return XK_KP_Enter;
      case kKey0Pad:
         return XK_KP_0;
      case kKey1Pad:
         return XK_KP_1;
      case kKey2Pad:
         return XK_KP_2;
      case kKey3Pad:
         return XK_KP_3;
      case kKey4Pad:
         return XK_KP_4;
      case kKey5Pad:
         return XK_KP_5;
      case kKey6Pad:
         return XK_KP_6;
      case kKey7Pad:
         return XK_KP_7;
      case kKey8Pad:
         return XK_KP_8;
      case kKey9Pad:
         return XK_KP_9;
      case kKeyDelPad:
         return XK_KP_Delete;
      case kKeyEqualsPad:
         return XK_KP_Equal;
      case kKeyAsterisk:
         return XK_KP_Multiply;
      case kKeyPlusPad:
         return XK_KP_Add;
      case kKeyMinusPad:
         return XK_KP_Subtract;
      case kKeySlashPad:
         return XK_KP_Divide;
      case kKeyF1:
         return XK_F1;
      case kKeyF2:
         return XK_F2;
      case kKeyF3:
         return XK_F3;
      case kKeyF4:
         return XK_F4;
      case kKeyF5:
         return XK_F5;
      case kKeyF6:
         return XK_F6;
      case kKeyF7:
         return XK_F7;
      case kKeyF8:
         return XK_F8;
      case kKeyF9:
         return XK_F9;
      case kKeyF10:
         return XK_F10;
      case kKeyF11:
         return XK_F11;
      case kKeyF12:
         return XK_F12;
      case kKeyLShift:
         return XK_Shift_L;
      case kKeyRShift:
         return XK_Shift_R;
      case kKeyLControl:
         return XK_Control_L;
      case kKeyRControl:
         return XK_Control_R;
      case kKeyCapsLock:
         return XK_Caps_Lock;
      case kKeyAlt:
         return XK_Alt_L;
      case kKeyAltGr:
         return XK_Alt_R;
      case kKeyLWin:
         return XK_Super_L;
      case kKeyRWin:
         return XK_Super_R;
      case kKeySpace:
         return XK_space;
      case kKeyQuote:
         return XK_apostrophe;
      case kKeyComma:
         return XK_comma;
      case kKeyMinus:
         return XK_minus;
      case kKeyStop:
         return XK_period;
      case kKeySlash:
         return XK_slash;
      case kKey0:
         return XK_0;
      case kKey1:
         return XK_1;
      case kKey2:
         return XK_2;
      case kKey3:
         return XK_3;
      case kKey4:
         return XK_4;
      case kKey5:
         return XK_5;
      case kKey6:
         return XK_6;
      case kKey7:
         return XK_7;
      case kKey8:
         return XK_8;
      case kKey9:
         return XK_9;
      case kKeyColon:
         return XK_semicolon;
      case kKeyBackslash2:
         return XK_less;
      case kKeyOpenbrace:
         return XK_bracketleft;
      case kKeyBackslash:
         return XK_backslash;
      case kKeyClosebrace:
         return XK_bracketright;
      case kKeyTilde:
         return XK_grave;
      case kKeyA:
         return XK_a;
      case kKeyB:
         return XK_b;
      case kKeyC:
         return XK_c;
      case kKeyD:
         return XK_d;
      case kKeyE:
         return XK_e;
      case kKeyF:
         return XK_f;
      case kKeyG:
         return XK_g;
      case kKeyH:
         return XK_h;
      case kKeyI:
         return XK_i;
      case kKeyJ:
         return XK_j;
      case kKeyK:
         return XK_k;
      case kKeyL:
         return XK_l;
      case kKeyM:
         return XK_m;
      case kKeyN:
         return XK_n;
      case kKeyO:
         return XK_o;
      case kKeyP:
         return XK_p;
      case kKeyQ:
         return XK_q;
      case kKeyR:
         return XK_r;
      case kKeyS:
         return XK_s;
      case kKeyT:
         return XK_t;
      case kKeyU:
         return XK_u;
      case kKeyV:
         return XK_v;
      case kKeyW:
         return XK_w;
      case kKeyX:
         return XK_x;
      case kKeyY:
         return XK_y;
      case kKeyZ:
         return XK_z;
      }
      return 0;
   }

   bool is_key_press_by_keycode(KeyCode scancode) {
      return is_key_press_by_vk(x11_keysym_to_scancode(scancode));
   }

   bool is_key_press_by_vk(unsigned vk) {
      const ::KeyCode keycode = XKeysymToKeycode(g_X11Display, vk);
      if(keycode == NoSymbol)
         return false;
      
      char keys[32];
      XQueryKeymap(g_X11Display, keys);

      return (keys[keycode/8] & (1 << (keycode%8)) ? true : false);
   }
} // namespace utils