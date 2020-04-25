const { SkSurface, SkPath, SkPaint } = require('./build/Release/hello.node');

setInterval(() => {
  console.time('total');
  const surface = SkSurface.MakeRasterN32Premul(256,256);
  const canvas = surface.getCanvas();
  
  console.time('draw');
  const scale = 256.0;
  const R = 0.45 * scale;
  const TAU = 6.2831853;
  
  const path = new SkPath();
  // path.moveTo(R, 0.0);
  // for (let i = 1; i < 7; ++i) {
  //   const theta = 3 * i * TAU / 7;
  //   path.lineTo(R * Math.cos(theta), R * Math.sin(theta));
  // }
  // path.close();
  
  
  path.addPoly([
    {x: 1, y:1},
    {x: 20, y:20},
    {x: 10, y:30},
  ], true);
  
  const paint = new SkPaint();
  paint.setAntiAlias(true);
  
  
  canvas.clear(0xFFFFFFFF);
  
  // canvas.translate(0.5 * scale, 0.5 * scale);
  canvas.drawPath(path, paint);
  console.timeEnd('draw');
  
  console.time('save');
  const image = surface.makeImageSnapshot();
  image.savePNG('./out.png');
  console.timeEnd('save');
  
  console.timeEnd('total');
  console.log(process.memoryUsage().rss);
}, 1000)