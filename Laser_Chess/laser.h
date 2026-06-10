#ifndef LASER_H
#define LASER_H


#include <SFML/Graphics.hpp>
#include "Global_Values.h"

class Laser
{
public:
    int gridX, gridY; //położenie
    const sf::RenderWindow* window;
    Direction faceing_direction;
    sf::Sprite laser_sprite;
    Laser(int x, int y, Direction direct, sf::Texture& texture):gridX(x),gridY(y), faceing_direction(direct)
    {
        laser_sprite.setTexture(texture);
        float texture_width = laser_sprite.getGlobalBounds().width;
        float texture_hight = laser_sprite.getGlobalBounds().height;

        laser_sprite.setScale(TILE_SIZE / texture_width, TILE_SIZE / texture_hight);
        laser_sprite.setOrigin(texture_width/2.0f,texture_hight/2.0f);
        update_sprite();
    }
    void update_sprite();
    void draw(sf::RenderWindow& window) const;
};

#endif // LASER_H
