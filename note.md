bin/g gen out/release --args="is_official_build=true skia_use_system_expat=false skia_use_system_icu=false skia_use_libjpeg_turbo_decode=false skia_use_libjpeg_turbo_encode=false skia_use_system_libpng=false skia_use_system_zlib=false skia_use_libwebp_encode=false skia_use_system_harfbuzz=false skia_use_libwebp_decode=false extra_cflags_cc=[\"-frtti\"]"

bin/gn gen out/release --args="is_official_build=true skia_use_system_expat=false skia_use_system_icu=false skia_use_libjpeg_turbo_decode=false skia_use_libjpeg_turbo_encode=false skia_use_system_libpng=false skia_use_system_zlib=false skia_use_libwebp_encode=false skia_use_system_harfbuzz=false skia_use_libwebp_decode=false"

./depoot_tools/ninja-mac -j2 -C out/release