#pragma once
struct WindowData {
    float deltaTime;
    float spf;   //milliseconds per frame
    float fps;   //frames per second
    float lastFrameTime, frameTime;
    int windowWidth, windowHeight;
    bool resized;
};

extern WindowData WinData;
