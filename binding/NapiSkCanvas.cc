#include "NapiSkCanvas.h"
#include "NapiSkPaint.h"
#include "NapiSkPath.h"

Napi::Object NapiSkCanvas::makeConstructor(Napi::Env env) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SkCanvas", {
        InstanceMethod("getSurface", &NapiSkCanvas::getSurface),
        InstanceMethod("clear", &NapiSkCanvas::clear),
        InstanceMethod("translate", &NapiSkCanvas::translate),
        InstanceMethod("drawPath", &NapiSkCanvas::drawPath)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return func;
}

NapiSkCanvas::NapiSkCanvas(const Napi::CallbackInfo &info) : Napi::ObjectWrap<NapiSkCanvas>(info) {
    self = info[0].As<Napi::External<SkCanvas>>().Data();
    info.This().As<Napi::Object>().Set("_surface", info[1]);
}

Napi::FunctionReference NapiSkCanvas::constructor;


Napi::Value NapiSkCanvas::getSurface(const Napi::CallbackInfo &info) {
    return info.This().As<Napi::Object>().Get("_surface");
}

void NapiSkCanvas::clear(const Napi::CallbackInfo &info){
    self->clear(info[0].As<Napi::Number>().Uint32Value());
}

void NapiSkCanvas::translate(const Napi::CallbackInfo &info){
    self->translate(info[0].As<Napi::Number>().FloatValue(),
        info[1].As<Napi::Number>().FloatValue());
}

void NapiSkCanvas::drawPath(const Napi::CallbackInfo &info){
    self->drawPath(NapiSkPath::Unwrap(info[0].As<Napi::Object>())->self,
        NapiSkPaint::Unwrap(info[1].As<Napi::Object>())->self);
}
