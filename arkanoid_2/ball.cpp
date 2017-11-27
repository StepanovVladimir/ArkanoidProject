#include "ball.h"
#include "platform.h"

constexpr float BALL_RADIUS = 10;
const sf::Color BALL_COLOR = sf::Color(255, 255, 255);
static const sf::Vector2f BALL_INITIAL_POSITION = {300, 540};

void initializeBall(Ball& ball)
{
    ball.shape.setRadius(BALL_RADIUS);
    ball.shape.setOrigin({BALL_RADIUS, BALL_RADIUS});
    ball.shape.setFillColor(BALL_COLOR);
    ball.shape.setPosition(BALL_INITIAL_POSITION);
    ball.speed = {-300, -300};
}

void checkBallClashPlatform(sf::Vector2f& position, Ball& ball, Platform& platform)
{
    if ((position.x - BALL_RADIUS <= platform.shape.getPosition().x + platform.shape.getOrigin().x) &&
    (position.x + BALL_RADIUS >= platform.shape.getPosition().x - platform.shape.getOrigin().x) &&
    (position.y + BALL_RADIUS >= platform.shape.getPosition().y))
    {
        float distanceFromCenter = std::abs(position.x - platform.shape.getPosition().x);
        float part = distanceFromCenter / platform.shape.getOrigin().x;
        float angle = 0;
        if (position.x < platform.shape.getPosition().x)
        {
            angle = 90.f + 50.f * part;
        }
        else
        {
            angle = 90.f - 50.f * part;
        }
        ball.speed.x = 424 * std::cos(angle * M_PI / 180);
        ball.speed.y = -424 * std::sin(angle * M_PI / 180);
    }    
}

void updateBall(Ball& ball, float elapsedTime, Platform& platform)
{
    sf::Vector2f position = ball.shape.getPosition();
    position += ball.speed * elapsedTime;
    if ((position.x + BALL_RADIUS >= 600) && (ball.speed.x > 0))
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
    checkBallClashPlatform(position, ball, platform);   
    ball.shape.setPosition(position);
}