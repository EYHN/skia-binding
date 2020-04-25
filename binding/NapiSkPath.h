#include <napi.h>
#include <include/core/SkPath.h>
#include "utils.h"

class NapiSkPath : public SkObjectWrap<NapiSkPath, SkPath> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    NapiSkPath(const Napi::CallbackInfo &info);
};
