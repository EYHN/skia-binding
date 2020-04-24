{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ 
        "skia_binding.cc",
        "binding/NapiSkSurface.cc",
        "binding/NapiSkCanvas.cc",
        "binding/NapiSkPath.cc",
        "binding/NapiSkPaint.cc",
        "binding/NapiSkImage.cc",
        "binding/NapiSkMatrix.cc"
      ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")",
        './skia/',
        '.'
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'conditions': [
        ['OS=="mac"', {
          "libraries": ["<(module_root_dir)/skia/out/release/libskia.a"]
        }],
        ['OS=="win"', {
          "libraries": ["<(module_root_dir)/skia/out/release/skia.lib"]
        }]
      ]
    }
  ]
}