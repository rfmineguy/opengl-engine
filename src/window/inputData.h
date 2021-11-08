#pragma once
struct InputData {
  bool keys[300];
  bool mouse[20];
  int mouseX, mouseY;
  int lastMouseX, lastMouseY;
  int mouseOffsetX, mouseOffsetY;
  bool mouseCaptured = false;

   double scrollXOffset, scrollYOffset;
};

extern InputData Input;
