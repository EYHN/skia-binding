#include "NapiSkCanvas.h"
#include "NapiSkPaint.h"
#include "NapiSkPath.h"

Napi::Object NapiSkCanvas::makeConstructor(Napi::Env env) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SkCanvas", {
		SkObjectWrapInstanceMethod("getSurface", [](SkCanvas*& self, const Napi::CallbackInfo& info) -> Napi::Value {
			return info.This().As<Napi::Object>().Get("_surface");
		}),
		SkObjectWrapInstanceMethod("clear", [](SkCanvas*& self, const Napi::CallbackInfo& info) -> Napi::Value {
			self->clear(info[0].As<Napi::Number>().Uint32Value());
		}),
		SkObjectWrapInstanceMethod("translate", [](SkCanvas*& self, const Napi::CallbackInfo& info) -> Napi::Value {
			self->translate(info[0].As<Napi::Number>().FloatValue(),
				info[1].As<Napi::Number>().FloatValue());
		}),
		SkObjectWrapInstanceMethod("drawPath", [](SkCanvas*& self, const Napi::CallbackInfo& info) -> Napi::Value {
			self->drawPath(NapiSkPath::Unwrap(info[0].As<Napi::Object>())->self,
				NapiSkPaint::Unwrap(info[1].As<Napi::Object>())->self);
		})
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return func;
}

NapiSkCanvas::NapiSkCanvas(const Napi::CallbackInfo &info) : SkObjectWrap<NapiSkCanvas, SkCanvas>(info) {
    self = info[0].As<Napi::External<SkCanvas>>().Data();
    info.This().As<Napi::Object>().Set("_surface", info[1]);
}

Napi::FunctionReference NapiSkCanvas::constructor;