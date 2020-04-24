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
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7',
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      },
      'conditions': [
        ['OS=="mac"', {
          "libraries": ["<(module_root_dir)/skia/out/release/libskia.a"],
          'cflags+': ['-fvisibility=hidden'],
          'xcode_settings': {
            'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
          }
        }],
        ['OS=="win"', {
          "libraries": ["<(module_root_dir)/skia/out/release/skia.lib"]
        }]
      ]
    }
  ]
}