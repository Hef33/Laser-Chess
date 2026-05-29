#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include "Global_Values.h"

class Piece
{
public:
    int gridX, gridY; //położenie
    Direction faceing_direction; //kierunek patrzenia pionka
    sf::Sprite piece_sprite;
    Piece(int x, int y, sf::Texture& texture):gridX(x),gridY(y), faceing_direction(Direction::North)
    {
        piece_sprite.setTexture(texture);
        float texture_width = piece_sprite.getGlobalBounds().width;
        float texture_hight = piece_sprite.getGlobalBounds().height;

        piece_sprite.setScale(TILE_SIZE / texture_width, TILE_SIZE / texture_hight);
        piece_sprite.setOrigin(texture_width/2.0f,texture_hight/2.0f);
        update_sprite();
    }
    virtual ~Piece() = default;

    //deklaracje funkcji
    void update_sprite();
    void move(Direction dir);
    void rotate_right();
    void rotate_left();

    void draw(sf::RenderWindow& window) const;

};

#endif
