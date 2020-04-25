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
  NapiSkSurface& sksurfacejs = New(rasterSurface, info.Env());
  
  auto ptr = std::shared_ptr<SkCanvas>(rasterSurface->getCanvas(), [](auto p) {/* don't delete canvas */});
  NapiSkCanvas& skcanvasjs =  NapiSkCanvas::New(ptr, info.Env());

  skcanvasjs.setSurfaceObject(sksurfacejs.Value());
  sksurfacejs.setCanvasObject(skcanvasjs.Value());

  return sksurfacejs.Value();
}

NapiSkSurface::NapiSkSurface(const Napi::CallbackInfo &info) : SkObjectWrap<NapiSkSurface, sk_sp<SkSurface>>(info) {
}

NapiSkSurface::~NapiSkSurface() {
}

void NapiSkSurface::setCanvasObject(const Napi::Object &surface) {
  this->Value().Set("_canvas", surface);
}
