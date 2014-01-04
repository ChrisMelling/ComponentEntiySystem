//STD
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>

//3RD
#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Entity Component System");

    // Records amount of time it took to process one game loop(frame)
    sf::Clock prevFrameTime;

    // Used to calculate the amount of time it took for each function in main to complete
    sf::Clock funcCompTime;

    // Stores the amount of seconds it took to process the previous game loop
    double dt = 0;

    while (window.isOpen())
    {
        //accurate seconds
        dt = prevFrameTime.restart().asMicroseconds() / 1000000.f;

        funcCompTime.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(sf::Color(40, 40, 40));

        window.display();

        std::cout << std::floor(1.f / dt) << " FPS\n\n";
    }

    return 0;
}
