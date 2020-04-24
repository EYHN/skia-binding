#include <napi.h>
#include <include/core/SkImage.h>

class NapiSkImage : public Napi::ObjectWrap<NapiSkImage> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    static Napi::FunctionReference constructor;
    NapiSkImage(const Napi::CallbackInfo &info);
    sk_sp<SkImage> self;

  private:
    void savePNG(const Napi::CallbackInfo &info);
};