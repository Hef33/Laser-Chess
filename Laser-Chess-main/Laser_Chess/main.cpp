#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "board.h"
#include "piece.h"
#include "laser.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 640), "Laser Chess");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Texture pawn_left_blue_texture, pawn_right_blue_texture, defender_blue_texture, king_blue_texture;
    sf::Texture pawn_left_red_texture, pawn_right_red_texture, defender_red_texture, king_red_texture;

    pawn_left_blue_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/pawn_left_blue.png");
    pawn_right_blue_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/pawn_right_blue.png");
    defender_blue_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/defender_blue.png");
    king_blue_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/king_blue.png");

    pawn_left_red_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/pawn_left_red.png");
    pawn_right_red_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/pawn_right_red.png");
    defender_red_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/defender_red.png");
    king_red_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/king_red.png");

    sf::Texture laser_texture;
    laser_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/laser.png");

    sf::Texture laser_beam_texture;
    laser_beam_texture.loadFromFile("C:/Laser-Chess-main/Laser_Chess/laser_beam.png");

    std::vector<Piece> pieces;
    int turn = 0;
    Board board;

    pieces.emplace_back(3, 1, Direction::South, pawn_right_red_texture, 1, PieceType::PawnRight);
    pieces.emplace_back(2, 0, Direction::South, pawn_right_red_texture, 1, PieceType::PawnRight);
    pieces.emplace_back(6, 0, Direction::South, pawn_left_red_texture, 1, PieceType::PawnLeft);
    pieces.emplace_back(5, 1, Direction::South, pawn_left_red_texture, 1, PieceType::PawnLeft);
    pieces.emplace_back(3, 0, Direction::South, defender_red_texture, 1, PieceType::Defender);
    pieces.emplace_back(5, 0, Direction::South, defender_red_texture, 1, PieceType::Defender);
    pieces.emplace_back(4, 0, Direction::South, king_red_texture, 1, PieceType::King);

    pieces.emplace_back(3, 7, Direction::North, king_blue_texture, 0, PieceType::King);
    pieces.emplace_back(1, 7, Direction::North, pawn_left_blue_texture, 0, PieceType::PawnLeft);
    pieces.emplace_back(5, 7, Direction::North, pawn_right_blue_texture, 0, PieceType::PawnRight);
    pieces.emplace_back(4, 6, Direction::North, pawn_right_blue_texture, 0, PieceType::PawnRight);
    pieces.emplace_back(2, 7, Direction::North, defender_blue_texture, 0, PieceType::Defender);
    pieces.emplace_back(4, 7, Direction::North, defender_blue_texture, 0, PieceType::Defender);
    pieces.emplace_back(2, 6, Direction::North, pawn_left_blue_texture, 0, PieceType::PawnLeft);

    Laser laserBlue(0, 7, Direction::North, laser_texture, laser_beam_texture);
    Laser laserRed(7, 0, Direction::South, laser_texture, laser_beam_texture);

    laserBlue.fire(pieces);

    while (window.isOpen()) {
        sf::Event event;
        bool turn_ended = false;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            for (Piece& p : pieces) {
                if (p.alive && p.team == turn) {
                    if (p.handle_event(event, pieces)) {
                        turn_ended = true;
                    }
                }
            }
        }
        if (turn_ended) {
            if (turn == 0) {
                laserRed.clear_path();
                laserBlue.king_destroyed = false;
                laserBlue.fire(pieces);

                if (laserBlue.king_destroyed) {
                    std::cout << "KONIEC GRY! Niebieski wygrywa!" << std::endl;
                }
                turn = 1;
            } else {
                laserBlue.clear_path();
                laserRed.king_destroyed = false;
                laserRed.fire(pieces);

                if (laserRed.king_destroyed) {
                    std::cout << "KONIEC GRY! Czerwony wygrywa!" << std::endl;
                }
                turn = 0;
            }
        }

        window.clear();
        board.draw(window);

        for (Piece& p : pieces) {
            if (p.alive) p.draw(window);
        }

        laserBlue.draw(window);
        laserRed.draw(window);

        window.display();
    }

    return 0;
}