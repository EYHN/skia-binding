#include "NapiSkCanvas.h"
#include "NapiSkPaint.h"
#include "NapiSkPath.h"

Napi::Object NapiSkCanvas::makeConstructor(Napi::Env env) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SkCanvas", {
      SkObjectWrapInstanceMethod("getSurface", [](SkCanvas& self, const Napi::CallbackInfo& info) -> Napi::Value {
        return info.This().As<Napi::Object>().Get("_surface");
      }),
      SkObjectWrapInstanceMethod("clear", [](SkCanvas& self, const Napi::CallbackInfo& info) {
        self.clear(info[0].As<Napi::Number>().Uint32Value());
      }),
      SkObjectWrapInstanceMethod("translate", [](SkCanvas& self, const Napi::CallbackInfo& info) {
        self.translate(info[0].As<Napi::Number>().FloatValue(),
        info[1].As<Napi::Number>().FloatValue());
      }),
      SkObjectWrapInstanceMethod("drawPath", [](SkCanvas& self, const Napi::CallbackInfo& info) {
        self.drawPath(*(NapiSkPath::Unwrap(info[0].As<Napi::Object>())->self.get()),
          NapiSkPaint::Unwrap(info[1].As<Napi::Object>())->self);
      })
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return func;
}

NapiSkCanvas::NapiSkCanvas(const Napi::CallbackInfo &info) : SkObjectWrap<NapiSkCanvas, SkCanvas>(info) {
  info.This().As<Napi::Object>().Set("_surface", info[1]);
}

NapiSkCanvas::~NapiSkCanvas() {
  printf("~NapiSkCanvas");
}

Napi::FunctionReference NapiSkCanvas::constructor;
