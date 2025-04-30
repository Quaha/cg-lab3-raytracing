#include <iostream>
#include <time.h>

#include "SceneManager.hpp"

#include "Window.hpp"

int main() {
    
    SceneManager scene;
    scene.loadScene(0, "balls");

    Window window(1920, 1080, "RayTracer");
    window.renderScene(scene);

    // scene.renderPhotos(1920, 1080);
    scene.clearScene();

    return 0;
}