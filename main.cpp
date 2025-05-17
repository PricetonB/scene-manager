#include <iostream>
#include <memory>
#include <string>

// Abstract base Scene class
class Scene {
public:
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual std::string nextScene() = 0;
};

// MenuScene class
class MenuScene : public Scene {
    bool goToPlay = false;
public:
    void update() override {
        std::cout << "Menu Scene: Press Enter to Start Game...\n";
        std::cin.get();
        goToPlay = true;
    }

    std::string nextScene() override {
        return goToPlay ? "play" : "";
    }
};

// PlayScene class
class PlayScene : public Scene {
    bool goToMenu = false;
public:
    void update() override {
        std::cout << "Play Scene: Press Enter to Return to Menu...\n";
        std::cin.get();
        goToMenu = true;
    }

    std::string nextScene() override {
        return goToMenu ? "menu" : "";
    }
};

// Game class
class Game {
    std::unique_ptr<Scene> currentScene;

    std::unique_ptr<Scene> createScene(const std::string& name) {
        if (name == "menu") return std::make_unique<MenuScene>();
        if (name == "play") return std::make_unique<PlayScene>();
        return nullptr;
    }

public:
    Game() {
        currentScene = createScene("menu");
    }

    void run() {
        while (currentScene) {
            currentScene->update();
            std::string next = currentScene->nextScene();
            if (!next.empty()) {
                currentScene = createScene(next);
            }
        }
    }
};

// Main function
int main() {
    Game game;
    game.run();
    return 0;
}

