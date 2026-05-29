#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>


class Board {
private:
    sf::RectangleShape tiles[8][8];

    void setupTiles();

public:
    Board();
    void draw(sf::RenderWindow& window);
};

#endif // BOARD_H