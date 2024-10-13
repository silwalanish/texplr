#include <texplr/texplr.h>

#include <game/game.h>

#include <iostream>

int main(int argc, char const* argv[])
{
    texplr::ApplicationSpecification appSpecs = texplr::AppLoader::loadSpecs("./assets/game.yml");
    appSpecs.appVersion = GAME_VERSION;
    appSpecs.engineVersion = ENGINE_VERSION;

    texplr::Application app(appSpecs);
    app.init();
    app.run();
    app.destroy();

    return 0;
}
