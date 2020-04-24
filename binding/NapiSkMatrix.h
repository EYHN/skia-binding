#include <napi.h>
#include <include/core/SkMatrix.h>
#include "utils.h"

class NapiSkMatrix : public SkObjectWrap<NapiSkMatrix, SkMatrix> {
  public:
    static Napi::Object makeConstructor(Napi::Env env);
    static Napi::FunctionReference constructor;
    NapiSkMatrix(const Napi::CallbackInfo &info);
};

inline SkMatrix Napi_val_as_SkMatrix(Napi::Value val) {
  NapiSkMatrix* matrix = NapiSkMatrix::Unwrap(val.As<Napi::Object>());
  return matrix->self;
}