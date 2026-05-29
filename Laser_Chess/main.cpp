#include <SFML/Graphics.hpp>
#include "Board.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(640, 640), "Laser Chess");
    window.setFramerateLimit(60);

    Board board;
    //renderowanie okna i gry
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //zamknięcie okna
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        //rysowanie planszy
        board.draw(window);

        window.display();
    }

    return 0;
}