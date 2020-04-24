#include "NapiSkPaint.h"

Napi::Object NapiSkPaint::makeConstructor(Napi::Env env) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SkPaint", {
        InstanceMethod("setAntiAlias", &NapiSkPaint::setAntiAlias)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return func;
}

NapiSkPaint::NapiSkPaint(const Napi::CallbackInfo &info) : Napi::ObjectWrap<NapiSkPaint>(info) {
}

Napi::FunctionReference NapiSkPaint::constructor;

void NapiSkPaint::setAntiAlias(const Napi::CallbackInfo &info) {
  self.setAntiAlias(info[0].As<Napi::Boolean>().ToBoolean());
}
