// copypasta.cc
#include <node.h>


#ifdef _WIN32
  #define WINVER 0x0500
  #include <windows.h>
  #define IS_WINDOWS
#elif __APPLE__
  #include <ApplicationServices/ApplicationServices.h>
  #include <Carbon/Carbon.h>
  #import <IOKit/hidsystem/IOHIDLib.h>
  #import <IOKit/hidsystem/ev_keymap.h>
  #define IS_APPLE
#elif __linux__
  #define IS_LINUX
#endif

namespace copypasta {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  
#if defined(IS_WINDOWS)
  INPUT ip;
  ip.type = INPUT_KEYBOARD;
  ip.ki.wScan = 0;
  ip.ki.time = 0;
  ip.ki.dwExtraInfo = 0;

  ip.ki.wVk = VK_CONTROL;
  ip.ki.dwFlags = 0; // 0 for key press
  SendInput(1, &ip, sizeof(INPUT));

  // Press the "V" key
  ip.ki.wVk = 'V';
  ip.ki.dwFlags = 0; // 0 for key press
  SendInput(1, &ip, sizeof(INPUT));

  // Release the "V" key
  ip.ki.wVk = 'V';
  ip.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &ip, sizeof(INPUT));

  // Release the "Ctrl" key
  ip.ki.wVk = VK_CONTROL;
  ip.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &ip, sizeof(INPUT));

#elif defined(IS_APPLE)
  CGEventRef keyEvent = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)kVK_ANSI_V, true);

        CGEventSetType(keyEvent, kCGEventKeyDown);
        CGEventSetFlags(keyEvent, kCGEventFlagMaskCommand);
        CGEventPost(kCGSessionEventTap, keyEvent);
        CFRelease(keyEvent);
  // CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

  // CGEventRef cmdd = CGEventCreateKeyboardEvent(src, 0x38, true);
  // CGEventRef cmdu = CGEventCreateKeyboardEvent(src, 0x38, false);
  // CGEventRef spcd = CGEventCreateKeyboardEvent(src, 0x31, true);
  // CGEventRef spcu = CGEventCreateKeyboardEvent(src, 0x31, false);

  // CGEventSetFlags(spcd, kCGEventFlagMaskCommand);
  // CGEventSetFlags(spcu, kCGEventFlagMaskCommand);

  // CGEventTapLocation loc = kCGHIDEventTap; // kCGSessionEventTap also works
  // CGEventPost(loc, cmdd);
  // CGEventPost(loc, spcd);
  // CGEventPost(loc, spcu);
  // CGEventPost(loc, cmdu);

  // CFRelease(cmdd);
  // CFRelease(cmdu);
  // CFRelease(spcd);
  // CFRelease(spcu);
  // CFRelease(src);  
#elif defined(IS_LINUX)

#endif

}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "paste", Method);
}

NODE_MODULE(copypasta, init)

}  // namespace demo