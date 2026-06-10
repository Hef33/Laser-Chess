#include <SFML/Graphics.hpp>
#include <iostream>


void set_red_textures()
{
sf::Texture pawn_left_red_texture;
if (!pawn_left_red_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/pawn_left_red.png"))
{
    std::cerr << "Blad wczytania czerwonego pionka" << std::endl;
}

}

void set_blue_textures()
{
sf::Texture pawn_left_blue_texture;
if (!pawn_left_blue_texture.loadFromFile("C:/Users/asiaa/Documents/Laser_Chess/pawn_left_blue.png"))
{
    std::cerr << "Blad wczytania niebieskiego pionka" << std::endl;
}
}