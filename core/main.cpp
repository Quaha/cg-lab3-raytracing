#include <iostream>
#include <time.h>

#include "SceneManager.hpp"

int main() {

    SceneManager scene(1920, 1080);
    scene.loadScene(0, "balls");
    scene.render();
    scene.clearScene();

    std::cout << "Rendering Time (ms): " << std::clock() << "\n";

    return 0;
}