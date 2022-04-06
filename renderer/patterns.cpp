#include <iostream>
#include <cmath>

#include "Framebuffer.h"

using namespace renderer;
using namespace std;

string input, filepath = "patterns\\pattern.png";
int scale = 1, width = 100, height;
double x_val, y_val;
Framebuffer fb;
Vector3D bgColor, patternColor;

void setupPrompts()
{
  string input;

  cout << "Enter output filepath, or leave blank for default (" << filepath << "): " << endl;
  getline(cin, input);
  if (input != "") {
    filepath = input;
  }

  cout << "Enter canvas width, or leave blank for default (100):" << endl;
  getline(cin, input);
  if (input != "") {
    width = stoi(input);
  }

  cout << "Enter canvas height, or leave blank to set equal to width:" << endl;
  getline(cin, input);
  if (input != "") {
    height = stoi(input);
  } else {
    height = width;
  }

  cout << "Enter scale, or leave blank for default (1):" << endl;
  getline(cin, input);
  if (input != "") {
    scale = stoi(input);
  }

  cout << "Enter background color, or leave blank for default (black):" << endl;
  getline(cin, input);
  if (input != "") {
    bgColor = Vector3D(input);
  } else {
    bgColor = Vector3D();
  }

  cout << "Enter pattern color, or leave blank for default (white):" << endl;
  getline(cin, input);
  if (input != "") {
    patternColor = Vector3D(input);
  } else {
    patternColor = Vector3D(1, 1, 1);
  }
}

void stepPrompts()
{
  string input;

  cout << "Enter x value:" << endl;
  getline(cin, input);
  if (input != "") {
    x_val = stod(input);
  }

  cout << "Enter y value, or leave blank to set equal to x value:" << endl;
  getline(cin, input);
  if (input != "") {
    y_val = stod(input);
  } else {
    y_val = x_val;
  }
}

void executeStep()
{
  Vector3D toggle;
  int blockLocation_x, blockLocation_y;
  for (double x = x_val - 1; x < width; x += x_val) {
    for (double y = y_val - 1; y < height; y += y_val) {

      blockLocation_x = floor(x) * scale;
      blockLocation_y = floor(y) * scale;

      if (fb.getPixelColor(blockLocation_x, blockLocation_y) == bgColor) {
        toggle = patternColor;
      } else {
        toggle = bgColor;
      }
      
      for (int block_x = 0; block_x < scale; block_x++) {
        for (int block_y = 0; block_y < scale; block_y++) {
          fb.setPixelColor(blockLocation_x + block_x, blockLocation_y + block_y, toggle);
        }
      }

    }
  }
}

int main(int argc, char *argv[])
{
  setupPrompts();
  fb = Framebuffer(width * scale, height * scale, bgColor);

  while (true) {
    stepPrompts();
    executeStep();
    fb.exportAsPNG(filepath);
    cout << "Step complete and output to " << filepath << ". Press enter to continue or x to quit." << endl;
    getline(cin, input);
    if (input == "x") {
      break;
    }
  }
}
