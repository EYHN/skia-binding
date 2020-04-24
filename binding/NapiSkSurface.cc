#include "NapiSkSurface.h"
#include "NapiSkCanvas.h"
#include "NapiSkImage.h"

Napi::Object NapiSkSurface::makeConstructor(Napi::Env env) {

  Napi::Function func = DefineClass(env, "SkSurface", {
    SkObjectWrapInstanceMethod("height", [](sk_sp<SkSurface> &self, const Napi::CallbackInfo &info) -> Napi::Value {
      return Napi::Number::New(info.Env(), self->height());
    }),
    SkObjectWrapInstanceMethod("width", [](sk_sp<SkSurface> &self, const Napi::CallbackInfo &info) -> Napi::Value {
      return Napi::Number::New(info.Env(), self->width());
    }),
    SkObjectWrapInstanceMethod("getCanvas", [](sk_sp<SkSurface> &self, const Napi::CallbackInfo &info) -> Napi::Value {
      return info.This().As<Napi::Object>().Get("_canvas");
    }),
    SkObjectWrapInstanceMethod("makeImageSnapshot", [](sk_sp<SkSurface> &self, const Napi::CallbackInfo &info) -> Napi::Value {
      sk_sp<SkImage> img(self->makeImageSnapshot());
      Napi::MemoryManagement::AdjustExternalMemory(info.Env(), img->imageInfo().computeMinByteSize());
      
      return NapiSkImage::constructor.New({Napi::External<sk_sp<SkImage>>::New(
          info.Env(),
          &img,
          [img](Napi::Env env /*env*/, sk_sp<SkImage>* data) { }
      )});
    }),
    StaticMethod("MakeRasterN32Premul", &NapiSkSurface::MakeRasterN32Premul)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  return func;
}

Napi::Value NapiSkSurface::MakeRasterN32Premul(const Napi::CallbackInfo &info) {
  Napi::Number width = info[0].As<Napi::Number>();
  Napi::Number height = info[1].As<Napi::Number>();

  sk_sp<SkSurface> rasterSurface =
          SkSurface::MakeRasterN32Premul(width.Int32Value(), height.Int32Value());

  Napi::MemoryManagement::AdjustExternalMemory(info.Env(), rasterSurface->imageInfo().computeMinByteSize());

  Napi::Object sksurfacejs = constructor.New({Napi::External<sk_sp<SkSurface>>::New(
    info.Env(), 
    &rasterSurface,
    [rasterSurface](Napi::Env env /*env*/, sk_sp<SkSurface>* data) {}
  )});

  Napi::Object skcanvasjs = NapiSkCanvas::constructor.New({
    Napi::External<SkCanvas>::New(info.Env(), rasterSurface->getCanvas()),
    sksurfacejs
  });

  sksurfacejs.Set("_canvas", skcanvasjs);

  return sksurfacejs;
}

NapiSkSurface::NapiSkSurface(const Napi::CallbackInfo &info) : SkObjectWrap<NapiSkSurface, sk_sp<SkSurface>>(info) {
  self = sk_sp<SkSurface>(*info[0].As<Napi::External<sk_sp<SkSurface>>>().Data());
}

NapiSkSurface::~NapiSkSurface() {
}

Napi::FunctionReference NapiSkSurface::constructor;
