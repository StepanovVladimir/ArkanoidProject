#pragma once

#include <SFML/Graphics.hpp>
#include "ball.h"

constexpr size_t LOSE = 0;
constexpr size_t WIN = 1;
constexpr size_t PAUSE = 2;
constexpr size_t SCORE = 3;
constexpr size_t LIVES = 4;
constexpr size_t TEXT_COUNT = 5;

void initializeText(sf::Font& font, sf::Text (&texts)[TEXT_COUNT]);
void updateText(sf::Text (&texts)[TEXT_COUNT], Ball& ball);