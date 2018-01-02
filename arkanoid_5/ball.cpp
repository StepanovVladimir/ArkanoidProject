#include "ball.h"

constexpr float BALL_RADIUS = 7;
const sf::Color BALL_COLOR = sf::Color(255, 255, 255);
static const sf::Vector2f BALL_INITIAL_POSITION = {275, 568};

void initializeBall(Ball& ball)
{
    ball.shape.setRadius(BALL_RADIUS);
    ball.shape.setOrigin({BALL_RADIUS, BALL_RADIUS});
    ball.shape.setFillColor(BALL_COLOR);
    ball.shape.setPosition(BALL_INITIAL_POSITION);
    ball.shape.setOutlineColor(sf::Color(0, 0, 0));
    ball.shape.setOutlineThickness(1.5);
    ball.speedModule = 500;
    ball.live = 1;
    ball.score = 0;
    ball.ended = false;
    ball.win = false;
    ball.slowed - false;
}

void checkBallClashPlatform(sf::Vector2f& position, Ball& ball, Platform& platform)
{
    if ((position.x - BALL_RADIUS <= platform.shape.getPosition().x + platform.shape.getOrigin().x) &&
        (position.x + BALL_RADIUS >= platform.shape.getPosition().x - platform.shape.getOrigin().x) &&
        (position.y - BALL_RADIUS <= platform.shape.getPosition().y + platform.shape.getSize().y) &&
        (position.y + BALL_RADIUS >= platform.shape.getPosition().y))
    {
        float distanceFromCenter = std::abs(position.x - platform.shape.getPosition().x);
        float relativeDistance = distanceFromCenter / platform.shape.getOrigin().x;
        float angle = 0;
        if (position.x < platform.shape.getPosition().x)
        {
            angle = 90 + 50 * relativeDistance;
        }
        else
        {
            angle = 90 - 50 * relativeDistance;
        }
        ball.speed.x = ball.speedModule * std::cos(angle * M_PI / 180);
        ball.speed.y = -ball.speedModule * std::sin(angle * M_PI / 180);
    }    
}

void checkBallClashBlocks(sf::Vector2f& position, Ball& ball, Block& block)
{
    if ((position.x - BALL_RADIUS <= block.shape.getPosition().x + block.shape.getOrigin().x) &&
        (position.x + BALL_RADIUS >= block.shape.getPosition().x - block.shape.getOrigin().x) &&
        (position.y + BALL_RADIUS >= block.shape.getPosition().y - block.shape.getOrigin().y) &&
        (position.y - BALL_RADIUS <= block.shape.getPosition().y + block.shape.getOrigin().y))
    {
        if (block.direction == DirectionBlocks::STRONG)
        {
            block.direction = DirectionBlocks::NONE;
            block.shape.setFillColor(BLOCK_COLOR);
        }
        else
        {
            block.destroyed = true;
            ball.score++;
        }   
        float overlapLeft = std::abs((position.x + BALL_RADIUS) - (block.shape.getPosition().x - block.shape.getOrigin().x));
        float overlapRight = std::abs((block.shape.getPosition().x + block.shape.getOrigin().x) - (position.x - BALL_RADIUS));
        float overlapTop = std::abs((position.y + BALL_RADIUS) - (block.shape.getPosition().y - block.shape.getOrigin().y));
        float overlapButtom = std::abs((block.shape.getPosition().y + block.shape.getOrigin().y) - (position.y - BALL_RADIUS));
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapButtom);
        if (minOverlapX < minOverlapY)
        {
            if ((overlapLeft < overlapRight) && (ball.speed.x > 0))
            {
                ball.speed.x = -ball.speed.x;
            }
            if ((overlapLeft > overlapRight) && (ball.speed.x < 0))
            {
                ball.speed.x = -ball.speed.x;
            }
        }
        else
        {
            if ((overlapTop < overlapButtom) && (ball.speed.y > 0))
            {
                ball.speed.y = -ball.speed.y;
            }
            if ((overlapTop > overlapButtom) && (ball.speed.y < 0))
            {
                ball.speed.y = -ball.speed.y;
            }
        }
    }
}

void updateBall(Ball& ball, float elapsedTime, Platform& platform, std::vector<Block>& blocks)
{
    sf::Vector2f position = ball.shape.getPosition();
    position += ball.speed * elapsedTime;
    if ((position.x + BALL_RADIUS >= WINDOW_WIDTH) && (ball.speed.x > 0))
    {
        ball.speed.x = -ball.speed.x;
    }
    if ((position.x - BALL_RADIUS <= 0) && (ball.speed.x < 0))
    {
        ball.speed.x = -ball.speed.x;
    }
    if ((position.y - BALL_RADIUS <= 0) && (ball.speed.y < 0))
    {
        ball.speed.y = -ball.speed.y;
    }
    if (position.y - BALL_RADIUS >= WINDOW_HEIGHT)
    {
        if (ball.live > 0)
        {
            ball.live -= 1;
            position.x = platform.shape.getPosition().x - platform.shape.getOrigin().x / 2;
            position.y = BALL_INITIAL_POSITION.y;
        }
        else
        {
            ball.ended = true;
        }
    }
    checkBallClashPlatform(position, ball, platform); 
    for (auto& block : blocks)
    {
        checkBallClashBlocks(position, ball, block);
    }
    ball.shape.setPosition(position); 
}