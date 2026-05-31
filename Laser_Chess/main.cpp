#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


#include "board.h"
#include "piece.h"
#include "textures.cpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Laser Chess");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    //wczytanie tekstur pionka
    sf::Texture pawn_left_blue_texture;
    if (!pawn_left_blue_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/pawn_left_blue.png"))
    {
        std::cerr << "Blad wczytania niebieskiego pionka" << std::endl;
    }
    sf::Texture pawn_right_blue_texture;
    if (!pawn_right_blue_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/pawn_right_blue.png"))
    {
        std::cerr << "Blad wczytania niebieskiego pionka" << std::endl;
    }
    sf::Texture defender_blue_texture;
    if (!defender_blue_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/defender_blue.png"))
    {
        std::cerr << "Blad wczytania niebieskiego pionka" << std::endl;
    }
    sf::Texture king_blue_texture;
    if (!king_blue_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/king_blue.png"))
    {
        std::cerr << "Blad wczytania niebieskiego pionka" << std::endl;
    }
    sf::Texture pawn_left_red_texture;
    if (!pawn_left_red_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/pawn_left_red.png"))
    {
        std::cerr << "Blad wczytania czerwonego pionka" << std::endl;
    }
    sf::Texture pawn_right_red_texture;
    if (!pawn_right_red_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/pawn_right_red.png"))
    {
        std::cerr << "Blad wczytania czerwonego pionka" << std::endl;
    }
    sf::Texture defender_red_texture;
    if (!defender_red_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/defender_red.png"))
    {
        std::cerr << "Blad wczytania nczerwonego pionka" << std::endl;
    }
    sf::Texture king_red_texture;
    if (!king_red_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/king_red.png"))
    {
        std::cerr << "Blad wczytania czerwonego pionka" << std::endl;
    }

    std::vector<Piece> pieces;

    Board board;

    pieces.emplace_back(1, 0, pawn_left_red_texture);//tworzenie pionka (tymczasowe do czasu wprowadznia wielu pionków)
    pieces.emplace_back(2,0, pawn_left_red_texture);
    pieces.emplace_back(6,0, pawn_right_red_texture);
    pieces.emplace_back(7,0, pawn_right_red_texture);
    pieces.emplace_back(3,0,defender_red_texture);
    pieces.emplace_back(5,0,defender_red_texture);
    pieces.emplace_back(4,0,king_red_texture);
    pieces.emplace_back(3,7,king_blue_texture);
    pieces.emplace_back(0, 7, pawn_left_blue_texture);
    pieces.emplace_back(1,7, pawn_left_blue_texture);
    pieces.emplace_back(5,7, pawn_right_blue_texture);
    pieces.emplace_back(6,7, pawn_right_blue_texture);
    pieces.emplace_back(2,7,defender_blue_texture);
    pieces.emplace_back(4,7,defender_blue_texture);
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
            for(Piece& p:pieces)
            {
                p.handle_event(event, pieces);
            }
        }

        window.clear();

        //rysowanie planszy
        board.draw(window);

        for(Piece& p:pieces)
        {
            p.draw(window);
        }

        window.display();

    }

    return 0;
}