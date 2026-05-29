#include <SFML/Graphics.hpp>
#include "board.h"
#include "piece.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Laser Chess");
    window.setFramerateLimit(60);

    //wczytanie tekstur pionka (tymczasowe)
    sf::Texture pieceTexture;
    if (!pieceTexture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/king_blue.png"))
    {
        std::cerr << "Nie znaleziono pliku pionek.png!" << std::endl;
    }

    Board board;
    Piece piece(3, 3, pieceTexture);//tworzenie pionka (tymczasowe do czasu wprowadznia wielu pionków)
    //renderowanie okna i gry
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //zamknięcie okna
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if (piece.is_alive())
                {
                // Ruch
                if(event.key.code == sf::Keyboard::Up) piece.move(Direction::North);
                if(event.key.code == sf::Keyboard::Right) piece.move(Direction::East);
                if(event.key.code == sf::Keyboard::Down) piece.move(Direction::South);
                if(event.key.code == sf::Keyboard::Left) piece.move(Direction::West);

                // Obracanie
                if(event.key.code == sf::Keyboard::E) piece.rotate_right(); // Naciśnij 'E'
                if(event.key.code == sf::Keyboard::Q) piece.rotate_left();  // Naciśnij 'Q'

                //destrukcja pionka(eksperymentalne

                //zabicie pionka
                if (event.key.code == sf::Keyboard::D) piece.destroy();
                }
            }
        }

        window.clear();

        //rysowanie planszy
        board.draw(window);
        if(piece.is_alive())
        piece.draw(window);
        window.display();
    }

    return 0;
}