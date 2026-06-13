#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Global_Values.h"

class Piece;

struct LaserSegment {
    int gridX, gridY;
    Direction dir;
    bool is_reflection;
};

class Laser {
private:
    std::vector<LaserSegment> current_path;
    sf::Texture laser_texture;
    sf::Texture laser_beam;
    Direction get_reflection(Direction laser_dir, const Piece& piece);

public:
    int gridX, gridY;
    Direction faceing_direction;
    sf::Sprite emitter_sprite;

    Laser(int x, int y, Direction direct, sf::Texture& emitter_tex, sf::Texture& beam_tex);

    bool king_destroyed = false;

    void update_sprite();
    void fire(std::vector<Piece>& all_pieces);
    void clear_path() { current_path.clear(); }
    void draw(sf::RenderWindow& window) const;
};

#endif