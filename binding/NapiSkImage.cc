#include "NapiSkImage.h"

Napi::Object NapiSkImage::makeConstructor(Napi::Env env) {
    Napi::Function func = DefineClass(env, "SkImage", {
      InstanceMethod("savePNG", &NapiSkImage::savePNG)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    return func;
}

NapiSkImage::NapiSkImage(const Napi::CallbackInfo &info) : Napi::ObjectWrap<NapiSkImage>(info) {
  self = sk_sp<SkImage>(*info[0].As<Napi::External<sk_sp<SkImage>>>().Data());
}

Napi::FunctionReference NapiSkImage::constructor;

void NapiSkImage::savePNG(const Napi::CallbackInfo &info) {
  std::string(info[0].As<Napi::String>());
  sk_sp<SkData> png(self->encodeToData());
  if (!png) { return; }
  SkFILEWStream out("./out.png");
  (void)out.write(png->data(), png->size());
}