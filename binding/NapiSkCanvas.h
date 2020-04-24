#include <napi.h>
#include <include/core/SkCanvas.h>

class NapiSkCanvas : public Napi::ObjectWrap<NapiSkCanvas> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    static Napi::FunctionReference constructor;
    NapiSkCanvas(const Napi::CallbackInfo &info);
    SkCanvas* self;

  private:
    Napi::Value getSurface(const Napi::CallbackInfo &info);
    void clear(const Napi::CallbackInfo &info);
    void translate(const Napi::CallbackInfo &info);
    void drawPath(const Napi::CallbackInfo &info);
};