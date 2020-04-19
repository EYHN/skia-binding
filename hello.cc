// hello.c
#include <node_api.h>
#include "skia_binding.h"

NAPI_MODULE_INIT() {
  return create_addon(env);
}