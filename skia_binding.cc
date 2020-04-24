#include <napi.h>

#include <include/core/SkData.h>
#include <include/core/SkImage.h>
#include <include/core/SkStream.h>
#include <include/core/SkSurface.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkPath.h>

#include "binding/NapiSkSurface.h"
#include "binding/NapiSkPath.h"
#include "binding/NapiSkPaint.h"
#include "binding/NapiSkCanvas.h"
#include "binding/NapiSkImage.h"
#include "binding/NapiSkMatrix.h"

// void draw(SkCanvas* canvas) {
//     const SkScalar scale = 256.0f;
//     const SkScalar R = 0.45f * scale;
//     const SkScalar TAU = 6.2831853f;
//     SkPath path;
//     path.moveTo(R, 0.0f);
//     for (int i = 1; i < 7; ++i) {
//         SkScalar theta = 3 * i * TAU / 7;
//         path.lineTo(R * cos(theta), R * sin(theta));
//     }
//     path.close();
//     SkPaint p;
//     p.setAntiAlias(true);
//     canvas->clear(SK_ColorWHITE);
//     canvas->translate(0.5f * scale, 0.5f * scale);
//     canvas->drawPath(path, p);
// }

// Napi::String Method(const Napi::CallbackInfo& info) {
//   sk_sp<SkSurface> rasterSurface =
//           SkSurface::MakeRasterN32Premul(256, 256);
//   SkCanvas* rasterCanvas = rasterSurface->getCanvas();
//   draw(rasterCanvas);
//   sk_sp<SkImage> img(rasterSurface->makeImageSnapshot());
//   if (!img) { return; }
//   sk_sp<SkData> png(img->encodeToData());
//   if (!png) { return; }
//   SkFILEWStream out("./out.png");
//   (void)out.write(png->data(), png->size());

//   Napi::Env env = info.Env();
//   return Napi::String::New(env, "world");
// }

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "SkSurface"),
              NapiSkSurface::makeConstructor(env));
  exports.Set(Napi::String::New(env, "SkCanvas"),
              NapiSkCanvas::makeConstructor(env));
  exports.Set(Napi::String::New(env, "SkPath"),
              NapiSkPath::makeConstructor(env));
  exports.Set(Napi::String::New(env, "SkPaint"),
              NapiSkPaint::makeConstructor(env));
  exports.Set(Napi::String::New(env, "SkImage"),
              NapiSkImage::makeConstructor(env));
  exports.Set(Napi::String::New(env, "SkMatrix"),
              NapiSkMatrix::makeConstructor(env));
  return exports;
}

NODE_API_MODULE(hello, Init)