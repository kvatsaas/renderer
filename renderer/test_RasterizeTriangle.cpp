#include "Framebuffer.h"
#include "Triangle.h"

using namespace renderer;

void testImage1()
{
  Framebuffer fb(230, 250);
  fb.clearToColor(Vector3D(1.0, 0.0, 0.0));

  Vector3D tColor(0.8, 0.4, 0.25);
  Triangle t(Vector3D(20, 40, 0), Vector3D(120, 80, 0), Vector3D(200, 200, 0), tColor, tColor, tColor);

  t.rasterize2D(fb);
  fb.exportAsPNG("output\\rasterize_triangle_test1.png");
}

void testImage2()
{
  Framebuffer fb(500, 250);
  fb.clearToColor(Vector3D(1.0, 0.25, 1.0));

  Vector3D tColor(0.2, 1.0, 0.25);
  Triangle t(Vector3D(50, 5, 0),
    Vector3D(95, 5, 0),
    Vector3D(95, 95, 0),
    tColor,
    tColor,
    tColor);

  t.rasterize2D(fb);
  fb.exportAsPNG("output\\rasterize_triangle_test2.png");
}

void testMultiple()
{
  Framebuffer fb(2000, 2000);
  fb.clearToColor(Vector3D(0.5, 0.5, 0.5));

  float intensity;
  Vector3D a_col, b_col, c_col;
  auto triangles = std::vector<Triangle>();
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      intensity = 1 - (x + 10.0 * y) / 99.0;
      a_col = Vector3D(intensity, 0, 0);
      b_col = Vector3D(0, intensity, 0);
      c_col = Vector3D(0, 0, intensity);
      triangles.push_back(Triangle(
        Vector3D(100 + 200 * x, 190 + 200 * y, 0),
        Vector3D(10 + 200 * x, 10 + 200 * y, 0),
        Vector3D(190 + 200 * x, 10 + 200 * y, 0),
        a_col,
        b_col,
        c_col));
    }
  }

  for (int i = 0; i < triangles.size(); i++) {
    triangles[i].rasterize2D(fb);
  }

  fb.exportAsPNG("output\\rasterize_triangle_multitest.png");
}

int main(int argc, char *argv[])
{
  //testImage1();
  //testImage2();
  testMultiple();
}
