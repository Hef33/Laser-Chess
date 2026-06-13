#include "laser.h"
#include "piece.h"
#include <iostream>

Laser::Laser(int x, int y, Direction direct, sf::Texture& emitter_tex, sf::Texture& beam_tex)
    : gridX(x), gridY(y), faceing_direction(direct), laser_texture(emitter_tex), laser_beam(beam_tex)
{
    emitter_sprite.setTexture(laser_texture);
    float texture_width = emitter_sprite.getGlobalBounds().width;
    float texture_hight = emitter_sprite.getGlobalBounds().height;
    emitter_sprite.setScale(TILE_SIZE / texture_width, TILE_SIZE / texture_hight);
    emitter_sprite.setOrigin(texture_width / 2.0f, texture_hight / 2.0f);
    update_sprite();
}

void Laser::update_sprite() {
    float centerX = (gridX * TILE_SIZE) + (TILE_SIZE / 2.0f);
    float centerY = (gridY * TILE_SIZE) + (TILE_SIZE / 2.0f);
    emitter_sprite.setPosition(centerX, centerY);
    float rotationDegrees = static_cast<int>(faceing_direction) * 90.0f;
    emitter_sprite.setRotation(rotationDegrees);
}

void Laser::fire(std::vector<Piece>& all_pieces) {
    current_path.clear();

    int cx = gridX;
    int cy = gridY;
    Direction dir = faceing_direction;

    current_path.push_back({cx, cy, dir, false});

    int max_steps = 64;

    while (max_steps-- > 0) {
        switch (dir) {
        case Direction::North: cy -= 1; break;
        case Direction::East:  cx += 1; break;
        case Direction::South: cy += 1; break;
        case Direction::West:  cx -= 1; break;
        }

        if (cx < 0 || cx > 7 || cy < 0 || cy > 7) {
            break;
        }

        Piece* hit_piece = nullptr;
        for (size_t i = 0; i < all_pieces.size(); ++i) {
            if (all_pieces[i].alive && all_pieces[i].gridX == cx && all_pieces[i].gridY == cy) {
                hit_piece = &all_pieces[i];
                break;
            }
        }
        if (hit_piece == nullptr) {
            current_path.push_back({cx, cy, dir, false});
            continue;
        }

        if (hit_piece->type == PieceType::King) {
            current_path.push_back({cx, cy, dir, false});
            hit_piece->alive = false;
            king_destroyed = true;
            std::cout << "Krol druzyny " << hit_piece->team << " zostal zniszczony!" << std::endl;
            break;
        }
        else if (hit_piece->type == PieceType::Defender) {
            current_path.push_back({cx, cy, dir, false});
            Direction p_dir = hit_piece->faceing_direction;
            bool blocked = false;

            if (dir == Direction::South && p_dir == Direction::North) blocked = true;
            if (dir == Direction::North && p_dir == Direction::South) blocked = true;
            if (dir == Direction::East  && p_dir == Direction::West)  blocked = true;
            if (dir == Direction::West  && p_dir == Direction::East)  blocked = true;

            if (!blocked) hit_piece->alive = false;
            break;
        }

        else if (hit_piece->type == PieceType::PawnLeft || hit_piece->type == PieceType::PawnRight) {
            bool safe_reflection = false;
            Direction next_dir = dir;
            int rotated_dir_int = (static_cast<int>(hit_piece->faceing_direction) + 1) % 4;
            Direction p_dir = static_cast<Direction>(rotated_dir_int);

            if (hit_piece->type == PieceType::PawnLeft) {
                if (p_dir == Direction::North || p_dir == Direction::South) {
                    if (dir == Direction::South) { next_dir = Direction::East;  safe_reflection = true; }
                    if (dir == Direction::West)  { next_dir = Direction::North; safe_reflection = true; }
                    if (dir == Direction::North) { next_dir = Direction::West;  safe_reflection = true; }
                    if (dir == Direction::East)  { next_dir = Direction::South; safe_reflection = true; }
                } else {
                    if (dir == Direction::South) { next_dir = Direction::West;  safe_reflection = true; }
                    if (dir == Direction::East)  { next_dir = Direction::North; safe_reflection = true; }
                    if (dir == Direction::North) { next_dir = Direction::East;  safe_reflection = true; }
                    if (dir == Direction::West)  { next_dir = Direction::South; safe_reflection = true; }
                }
            }
            else if (hit_piece->type == PieceType::PawnRight) {
                if (p_dir == Direction::North || p_dir == Direction::South) {
                    if (dir == Direction::South) { next_dir = Direction::West;  safe_reflection = true; }
                    if (dir == Direction::East)  { next_dir = Direction::North; safe_reflection = true; }
                    if (dir == Direction::North) { next_dir = Direction::East;  safe_reflection = true; }
                    if (dir == Direction::West)  { next_dir = Direction::South; safe_reflection = true; }
                } else {
                    if (dir == Direction::South) { next_dir = Direction::East;  safe_reflection = true; }
                    if (dir == Direction::West)  { next_dir = Direction::North; safe_reflection = true; }
                    if (dir == Direction::North) { next_dir = Direction::West;  safe_reflection = true; }
                    if (dir == Direction::East)  { next_dir = Direction::South; safe_reflection = true; }
                }
            }

            if (safe_reflection) {
                current_path.push_back({cx, cy, dir, true});
                dir = next_dir;
                continue;
            } else {
                current_path.push_back({cx, cy, dir, false});
                hit_piece->alive = false;
                std::cout << "zniszczone przez uderzenie w zla sciane" << std::endl;
                break;
            }
        }
    }
}

void Laser::draw(sf::RenderWindow& window) const {
    window.draw(emitter_sprite);

    if (current_path.empty()) return;

    sf::Sprite segment_sprite;
    segment_sprite.setTexture(laser_beam);

    float tex_w = segment_sprite.getGlobalBounds().width;
    float tex_h = segment_sprite.getGlobalBounds().height;

    if (tex_w > 0 && tex_h > 0) {
        segment_sprite.setOrigin(tex_w / 2.0f, tex_h / 2.0f);
        segment_sprite.setScale(TILE_SIZE / tex_w, TILE_SIZE / tex_h);

        for (const auto& segment : current_path) {
            float centerX = (segment.gridX * TILE_SIZE) + (TILE_SIZE / 2.0f);
            float centerY = (segment.gridY * TILE_SIZE) + (TILE_SIZE / 2.0f);
            segment_sprite.setPosition(centerX, centerY);

            float angle = static_cast<int>(segment.dir) * 90.0f;
            segment_sprite.setRotation(angle);

            window.draw(segment_sprite);
        }
    }
}