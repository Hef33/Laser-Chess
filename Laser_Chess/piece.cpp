#include "piece.h"
#include <iostream>


//aktualizacja sprite'a pionka
void Piece::update_sprite()
{
    float centerX = (gridX * TILE_SIZE) + (TILE_SIZE / 2.0f);
    float centerY = (gridY * TILE_SIZE) + (TILE_SIZE / 2.0f);
    piece_sprite.setPosition(centerX, centerY);
    float rotationDegrees = static_cast<int>(faceing_direction) * 90.0f;
    piece_sprite.setRotation(rotationDegrees);
}

void Piece::move(Direction dir, const std::vector<Piece>& all_pieces)
{
    int targetX = gridX; int targetY = gridY;
    switch(dir)
    {
        case Direction::North: targetY -= 1;break;
        case Direction::East: targetX += 1;break;
        case Direction::South: targetY += 1;break;
        case Direction::West: targetX -= 1;break;
    }
    if(targetX<0||targetX>7||targetY<0||targetY>7) return;

    for(const Piece& other : all_pieces)
    {
        if(&other != this && other.is_alive())
        {
            if(other.gridX == targetX && other.gridY == targetY)
                return;
        }
    }
    gridX = targetX;
    gridY = targetY;
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

void Piece::handle_event(const sf::Event& event, const std::vector<Piece>& all_pieces)
{
        if (!is_alive()) return;

            if (event.type == sf::Event::MouseButtonPressed)
                {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    float mouseX = static_cast<float>(event.mouseButton.x);
                    float mouseY = static_cast<float>(event.mouseButton.y);
                    check_click(mouseX, mouseY);
                }
            }

            else if(event.type == sf::Event::KeyPressed)
                {
                    if(is_selected())
                {// Ruch
                if(event.key.code == sf::Keyboard::Up) {move(Direction::North,  all_pieces);selected = !selected;}
                if(event.key.code == sf::Keyboard::Right) {move(Direction::East, all_pieces);selected = !selected;}
                if(event.key.code == sf::Keyboard::Down) {move(Direction::South,all_pieces);selected = !selected;}
                if(event.key.code == sf::Keyboard::Left) {move(Direction::West,all_pieces); selected = !selected;}

                // Obracanie
                if(event.key.code == sf::Keyboard::E) {rotate_right(); selected = !selected;}// Naciśnij 'E'
                if(event.key.code == sf::Keyboard::Q) {rotate_left(); selected = !selected;} // Naciśnij 'Q'

                //zabicie pionka
                if (event.key.code == sf::Keyboard::D) destroy();
                    }}}


void Piece::draw(sf::RenderWindow& window) const {
    window.draw(piece_sprite);
}