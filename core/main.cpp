#include "SceneManager.hpp"

int main() {

    SceneManager scene(1920, 1080);
    scene.loadScene(0, "balls");
    scene.render();
    scene.clearScene();

    return 0;
}