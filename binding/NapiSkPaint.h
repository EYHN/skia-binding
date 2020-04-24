#include <napi.h>
#include <include/core/SkPaint.h>

class NapiSkPaint : public Napi::ObjectWrap<NapiSkPaint> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    static Napi::FunctionReference constructor;
    NapiSkPaint(const Napi::CallbackInfo &info);
    SkPaint self;

  private:
    void setAntiAlias(const Napi::CallbackInfo &info);
};