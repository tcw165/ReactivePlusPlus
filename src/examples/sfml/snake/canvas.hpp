#pragma once

#include "snake.hpp"

#include <SFML/Graphics.hpp>

sf::RectangleShape get_rectangle_at(Coordinates location, sf::Color color);
sf::Vector2u get_window_size(size_t rows_count, size_t cols_count);