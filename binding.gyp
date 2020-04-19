{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "skia_binding.cc" ],
      'include_dirs': ['./skia/'],
      "libraries": [ "<(module_root_dir)/skia/out/release/libskia.a" ]
    }
  ]
}