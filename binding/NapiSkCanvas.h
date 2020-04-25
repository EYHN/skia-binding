#include <napi.h>
#include <include/core/SkCanvas.h>
#include "utils.h"

class NapiSkCanvas : public SkObjectWrap<NapiSkCanvas, SkCanvas> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    static Napi::FunctionReference constructor;
    NapiSkCanvas(const Napi::CallbackInfo &info);
    ~NapiSkCanvas();
};
