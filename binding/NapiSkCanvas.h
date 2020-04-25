#include <napi.h>
#include <include/core/SkCanvas.h>
#include "utils.h"

class NapiSkCanvas : public SkObjectWrap<NapiSkCanvas, SkCanvas> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    NapiSkCanvas(const Napi::CallbackInfo &info);
    ~NapiSkCanvas();

    void setSurfaceObject(const Napi::Object &surface);
};
