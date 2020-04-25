#include <napi.h>
#include <include/core/SkSurface.h>
#include "utils.h"

class NapiSkSurface : public SkObjectWrap<NapiSkSurface, sk_sp<SkSurface>> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    static Napi::Value MakeRasterN32Premul(const Napi::CallbackInfo &info);
    NapiSkSurface(const Napi::CallbackInfo &info);
    ~NapiSkSurface();

    void setCanvasObject(const Napi::Object &canvas);
};
