#include <nan.h>
#include <v8.h>

using namespace std;
using namespace Nan;
using namespace v8;

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

HWND workerHwnd = NULL;

BOOL CALLBACK FindWorkerWindow(HWND hwnd, LPARAM param) {
  HWND defViewHwnd = FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);

  if (defViewHwnd != NULL) {
    workerHwnd = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
  }

  return TRUE;
}

NAN_METHOD(renderAsWallpaper)
{
  if (info.Length() >= 2) {
    return Nan::ThrowError("electron-window-as-wallpaper: Invalid number of arguments. Should be 1");
  }

  v8::Local<v8::Object> bufferObj;

  if (info[0]->IsArrayBufferView() && info[0]->IsObject() && info[0]->IsTypedArray() && info[0]->IsUint8Array()) {
      bufferObj = info[0].As<v8::Object>();
  } else {
    Nan::ThrowTypeError("\n\nArgument must be a HWND handle!\nPlease use \"yourBrowserWindow.getNativeWindowHandle();\"\nhttps://electronjs.org/docs/api/browser-window#wingetnativewindowhandle\n");
    info.GetReturnValue().Set(Nan::False());
    return;
  }

  unsigned char *bufferData = (unsigned char *)node::Buffer::Data(bufferObj);
  unsigned long handle = *reinterpret_cast<unsigned long *>(bufferData);

  HWND hwnd = (HWND)handle;

  bool ok = false;

  HWND progman = FindWindowEx(NULL, NULL, "Progman", NULL);
  SendMessageA(progman, 0x052C, 0xD, 0);
  SendMessageA(progman, 0x052C, 0xD, 1);

  EnumWindows(FindWorkerWindow, NULL);

  if (workerHwnd) {
    if (SetParent(hwnd, workerHwnd)) {
      ok = true;
    }
  }

  info.GetReturnValue().Set(ok ? Nan::True() : Nan::False());
}

NAN_MODULE_INIT(Initialize)
{
  NAN_EXPORT(target, renderAsWallpaper);
}

NODE_MODULE(addon, Initialize);
