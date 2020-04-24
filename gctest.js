const { SkSurface, SkPath, SkPaint } = require('./build/Release/hello.node');

new SkPath();

global.gc();

surface = SkSurface.MakeRasterN32Premul(256,256);
surface = null;
global.gc();