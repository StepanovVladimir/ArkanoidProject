#include "bonuses.h"

constexpr float BONUS_RADIUS = 10;
constexpr float BONUS_SPEED = 275;

void initializeBonus(std::vector<Bonus>& bonuses, Block& block)
{
    Bonus bonus;
    bonuses.push_back(bonus);
    size_t i = bonuses.size() - 1;
    bonuses[i].shape.setPosition({block.shape.getPosition()});
    bonuses[i].shape.setRadius(BONUS_RADIUS);
    bonuses[i].shape.setOrigin({BONUS_RADIUS, BONUS_RADIUS});
    bonuses[i].shape.setOutlineColor(sf::Color(0, 0, 0));
    bonuses[i].shape.setOutlineThickness(1.5);
    if (block.direction == DirectionBlocks::BONUS_LIVE)
    {
        bonuses[i].direction = DirectionBonuses::LIVE;
        bonuses[i].shape.setFillColor(BONUS_LIVE_COLOR);
    }
    if (block.direction == DirectionBlocks::BONUS_EXTENSION)
    {
        bonuses[i].direction = DirectionBonuses::EXTENSION;
        bonuses[i].shape.setFillColor(BONUS_EXTENSION_COLOR);
    }
    if (block.direction == DirectionBlocks::BONUS_SLOWING)
    {
        bonuses[i].direction = DirectionBonuses::SLOWING;
        bonuses[i].shape.setFillColor(BONUS_SLOWING_COLOR);
    }
}

void checkClash(Bonus& bonus, sf::Vector2f& position, Platform& platform, Ball& ball)
{
    if ((position.x - BONUS_RADIUS <= platform.shape.getPosition().x + platform.shape.getOrigin().x) &&
        (position.x + BONUS_RADIUS >= platform.shape.getPosition().x - platform.shape.getOrigin().x) &&
        (position.y - BONUS_RADIUS <= platform.shape.getPosition().y + platform.shape.getSize().y) &&
        (position.y + BONUS_RADIUS >= platform.shape.getPosition().y))
    {
        bonus.destroyed = true;
        if (bonus.direction == DirectionBonuses::LIVE)
        {
            ball.live++;
        }
        if (bonus.direction == DirectionBonuses::EXTENSION)
        {
            platform.shape.setSize({PLATFORM_WIDTH * 1.5, PLATFORM_HEIGHT});
            platform.shape.setOrigin({PLATFORM_WIDTH * 0.75, 0});
        }
        if ((bonus.direction == DirectionBonuses::SLOWING) && !ball.slowed)
        {
            ball.speed = ball.speed / 1.25f;
            ball.speedModule = ball.speedModule / 1.25;
            ball.slowed = true;
        }
    }
    if (position.y - BONUS_RADIUS >= WINDOW_HEIGHT)
    {
        bonus.destroyed = true;
    }
}

bool isBonusDestroyed(Bonus bonus)
{
    return (bonus.destroyed);
}

void removeDeathBonuses(std::vector<Bonus>& bonuses)
{
    auto newEnd = std::remove_if(bonuses.begin(), bonuses.end(), isBonusDestroyed);
    bonuses.erase(newEnd, bonuses.end());
}

void updateBonuses(std::vector<Bonus>& bonuses, float elapsedTime, Platform& platform, Ball& ball)
{
    for(auto& bonus : bonuses)
    {
        sf::Vector2f position = bonus.shape.getPosition();
        position.y += BONUS_SPEED * elapsedTime;
        checkClash(bonus, position, platform, ball);
        bonus.shape.setPosition(position);
    }
}