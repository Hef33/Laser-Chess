#include "laser.h"

void Laser::update_sprite()
{
    float centerX = (gridX * TILE_SIZE) + (TILE_SIZE / 2.0f);
    float centerY = (gridY * TILE_SIZE) + (TILE_SIZE / 2.0f);
    laser_sprite.setPosition(centerX, centerY);
    float rotationDegrees = static_cast<int>(faceing_direction) * 90.0f;
    laser_sprite.setRotation(rotationDegrees);
}

void Laser::draw(sf::RenderWindow& window) const
{
    window.draw(laser_sprite);
}
