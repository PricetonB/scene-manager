#include <iostream>
#include <memory>
#include <string>
#include <limits>

// Abstract base Scene class
class Scene {
public:
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual std::string nextScene() = 0;
};


//---------------------------------------------------
// MenuScene class
class MenuScene : public Scene {
    bool _sceneChangeNeeded = false;
    std::string _sceneToChangeTo = "";

    void _changeScene(std::string sceneName) {
	    _sceneChangeNeeded = true;
	    _sceneToChangeTo = sceneName;
    }
	
public:
    void update() override {
        std::cout << "what scene do you want to go to, play or multiplayer\n";
	std::string nextScene;
        std::cin >> nextScene;
	if (nextScene != "play" && nextScene != "multiplayer") {
		std::cout << "scene not recognized \n";
	} else {
	_changeScene(nextScene);
	}
    }


    std::string nextScene() override {
        return _sceneChangeNeeded ? _sceneToChangeTo : "";
    }
};

//---------------------------------------------------
// PlayScene class
class PlayScene : public Scene {
    bool _sceneChangeNeeded = false;
public:
    void update() override {
        std::cout << "Play Scene: Press Enter to Return to Menu...\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        _sceneChangeNeeded = true;

    }

    std::string nextScene() override {
        return _sceneChangeNeeded ? "menu" : "";
    }
};


//---------------------------------------------------
// multiPlayerScene class
class MultiplayerScene : public Scene {
    bool _sceneChangeNeeded = false;
public:
    void update() override {
        std::cout << "multiplayer Scene: Press Enter to Return to Menu...\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        _sceneChangeNeeded = true;

    }

    std::string nextScene() override {
        return _sceneChangeNeeded ? "menu" : "";
    }
};
//---------------------------------------------------
// Game class
class Game {
    std::unique_ptr<Scene> currentScene;

    std::unique_ptr<Scene> createScene(const std::string& name) {
        if (name == "menu") return std::make_unique<MenuScene>();
        if (name == "play") return std::make_unique<PlayScene>();
	if (name == "multiplayer") return std::make_unique<MultiplayerScene>();
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

