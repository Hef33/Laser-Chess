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

    int turn = 0;

    Board board;

    //tworzenie pionkow
    pieces.emplace_back(1,0, Direction::South, pawn_left_red_texture, 1);
    pieces.emplace_back(2,0, Direction::South, pawn_left_red_texture, 1);
    pieces.emplace_back(6,0, Direction::South, pawn_right_red_texture, 1);
    pieces.emplace_back(7,0, Direction::South, pawn_right_red_texture, 1);
    pieces.emplace_back(3,0, Direction::South, defender_red_texture, 1);
    pieces.emplace_back(5,0, Direction::South, defender_red_texture, 1);
    pieces.emplace_back(4,0, Direction::South, king_red_texture, 1);
    pieces.emplace_back(3,7, Direction::North, king_blue_texture, 0);
    pieces.emplace_back(0,7, Direction::North, pawn_left_blue_texture, 0);
    pieces.emplace_back(1,7, Direction::North, pawn_left_blue_texture, 0);
    pieces.emplace_back(5,7, Direction::North, pawn_right_blue_texture, 0);
    pieces.emplace_back(6,7, Direction::North, pawn_right_blue_texture, 0);
    pieces.emplace_back(2,7, Direction::North, defender_blue_texture, 0);
    pieces.emplace_back(4,7, Direction::North, defender_blue_texture, 0);


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

            bool turn_ended = false;

            //wybieranie pionka i ruch
            for(Piece& p:pieces)
            {
                if(p.team == turn)
                {
                if(p.handle_event(event, pieces))
                    {
                        turn_ended = true;
                }
                }}
            if(turn_ended)
            {
                turn = (turn ==0)? 1:0;
            }

            window.clear();

            //rysowanie planszy
            board.draw(window);
            //rysowanie pionkow
            for(Piece& p:pieces)
            {
                if(p.is_alive()) p.draw(window);
            }

            window.display();

        }}

    return 0;
}