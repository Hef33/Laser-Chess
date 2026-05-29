#include "piece.h"


//aktualizacja sprite'a pionka
void Piece::update_sprite()
{
    float centerX = (gridX * TILE_SIZE) + (TILE_SIZE / 2.0f);
    float centerY = (gridY * TILE_SIZE) + (TILE_SIZE / 2.0f);
    piece_sprite.setPosition(centerX, centerY);
    float rotationDegrees = static_cast<int>(faceing_direction) * 90.0f;
    piece_sprite.setRotation(rotationDegrees);
}

void Piece::move(Direction dir)
{
    switch(dir)
    {
        case Direction::North: gridY -= 1;if (gridY <  0){gridY = 0;}break;
        case Direction::East: gridX += 1;if (gridX > 7){gridX = 7;}break;
        case Direction::South: gridY += 1;if (gridY > 7){gridY = 7;}break;
        case Direction::West: gridX -= 1;if (gridX < 0){gridX = 0;}break;
    }
    update_sprite();
}

void Piece::rotate_right()
{
    int curent_direction = static_cast<int>(faceing_direction);
    curent_direction = (curent_direction+1)%4;
    faceing_direction = static_cast<Direction>(curent_direction);

    update_sprite();
}
void Piece::rotate_left()
{
    int curent_direction = static_cast<int>(faceing_direction);
    curent_direction = (curent_direction+3)%4;
    faceing_direction = static_cast<Direction>(curent_direction);

    update_sprite();
}

void Piece::draw(sf::RenderWindow& window) const {
    window.draw(piece_sprite);
}