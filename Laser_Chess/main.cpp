#include <SFML/Graphics.hpp>
#include <iostream>


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

    Board board;
    Piece red_pawn1(1, 0, pawn_left_red_texture);//tworzenie pionka (tymczasowe do czasu wprowadznia wielu pionków)
    Piece red_pawn2(2,0, pawn_left_red_texture);
    Piece red_pawn3(6,0, pawn_right_red_texture);
    Piece red_pawn4(7,0, pawn_right_red_texture);
    Piece red_defender1(3,0,defender_red_texture);
    Piece red_defender2(5,0,defender_red_texture);
    Piece red_king(4,0,king_red_texture);
    Piece blue_king(3,7,king_blue_texture);
    Piece blue_pawn1(0, 7, pawn_left_blue_texture);
    Piece blue_pawn2(1,7, pawn_left_blue_texture);
    Piece blue_pawn3(5,7, pawn_right_blue_texture);
    Piece blue_pawn4(6,7, pawn_right_blue_texture);
    Piece blue_defender1(2,7,defender_blue_texture);
    Piece blue_defender2(4,7,defender_blue_texture);
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
            red_pawn1.handle_event(event);
            red_pawn2.handle_event(event);
        }

        window.clear();

        //rysowanie planszy
        board.draw(window);
        if(red_pawn1.is_alive())
        red_pawn1.draw(window);
        if(red_pawn2.is_alive())
        red_pawn2.draw(window);
        if(red_pawn3.is_alive())
            red_pawn3.draw(window);
        if(red_pawn4.is_alive())
            red_pawn4.draw(window);
        if(red_defender1.is_alive())
            red_defender1.draw(window);
        if(red_defender2.is_alive())
            red_defender2.draw(window);
        if(red_king.is_alive())
        red_king.draw(window);


        if(blue_pawn1.is_alive())
            blue_pawn1.draw(window);
        if(blue_pawn2.is_alive())
            blue_pawn2.draw(window);
        if(blue_pawn3.is_alive())
            blue_pawn3.draw(window);
        if(blue_pawn4.is_alive())
            blue_pawn4.draw(window);
        if(blue_defender1.is_alive())
            blue_defender1.draw(window);
        if(blue_defender2.is_alive())
            blue_defender2.draw(window);
        if(blue_king.is_alive())
            blue_king.draw(window);


        window.display();

    }

    return 0;
}