#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Global_Values.h"

enum class PieceType {
    King,
    Defender,
    PawnLeft,
    PawnRight
};

class Piece {
public:
    int gridX, gridY;
    bool alive;
    bool selected = false;
    int team;
    Direction faceing_direction;
    sf::Sprite piece_sprite;
    PieceType type;

    Piece(int x, int y, Direction direct, sf::Texture& texture, int t, PieceType pType)
        : gridX(x), gridY(y), faceing_direction(direct), team(t), alive(true), type(pType)
    {
        piece_sprite.setTexture(texture);
        float texture_width = piece_sprite.getGlobalBounds().width;
        float texture_hight = piece_sprite.getGlobalBounds().height;
        piece_sprite.setScale(TILE_SIZE / texture_width, TILE_SIZE / texture_hight);
        piece_sprite.setOrigin(texture_width/2.0f, texture_hight/2.0f);
        update_sprite();
    }

    virtual ~Piece() = default;

    void destroy() { alive = false; }
    bool is_alive() const { return alive; }
    bool is_selected() const { return selected; }
    PieceType get_type() const { return type; }
    Direction get_direction() const { return faceing_direction; }

    void check_click(float mouseX, float mouseY) {
        if (piece_sprite.getGlobalBounds().contains(mouseX, mouseY))
            selected = !selected;
    }

    bool handle_event(const sf::Event& event, const std::vector<Piece>& all_pieces);
    void update_sprite();
    bool move(Direction dir, const std::vector<Piece>& all_pieces);
    void rotate_right();
    void rotate_left();
    void draw(sf::RenderWindow& window) const;
};

#endif