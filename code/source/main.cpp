
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include "../header/Scene.hpp"
#include "../header/Camera.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Time.hpp>

using namespace sf;
using namespace OpenGLRender3D;

int main()
{

    srand(time(NULL));

    Window window(VideoMode(800, 600), "OpenGL Modern + Shaders + textures", Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled(true);

    // Una vez se ha creado el contexto de OpenGL ya se puede inicializar Glew:

    GLenum glew_initialization = glewInit();

    assert(glew_initialization == GLEW_OK);

    // Una vez se ha inicializado GLEW se puede crear una instancia de View:

    Scene myScene(800, 600);

    // Se ejecuta el bucle principal:

    bool running = true;

    sf::Clock clock; // starts the clock

    do
    {
        Event event;     

        running = myScene.manageInput(window);
        myScene.update(clock.getElapsedTime().asSeconds());
        myScene.render();

        window.display();
    } while (running);

    return (EXIT_SUCCESS);
}
