#include "Board.h"
#include "Global_Values.h"


Board::Board()
{
    setupTiles();
}

void Board::setupTiles()
{
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            tiles[x][y].setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tiles[x][y].setPosition(x * TILE_SIZE, y * TILE_SIZE);

            //Szachownica
            if ((x + y) % 2 == 0)
            {
                tiles[x][y].setFillColor(sf::Color(240, 217, 181)); //Jasne pole
            } else {
                tiles[x][y].setFillColor(sf::Color(181, 136, 99));  //Ciemne pole
            }
        }
    }
}

void Board::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            window.draw(tiles[x][y]);
        }
    }
}