#include "text.h"
#include "backgraund.h"

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow& window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Arkanoid Game Clone", sf::Style::Default, settings);
    window.setFramerateLimit(MAX_FPS);
}

void handlePause(const sf::Event::KeyEvent& event, bool& pause)
{
    switch (event.code)
    {
    case sf::Keyboard::Escape:
        if (pause)
        {
            pause = false;
        }
        else
        {
            pause = true;
        }
        break;
    }
}

void handleEvents(sf::RenderWindow& window, Platform& platform, bool& pause)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            handlePlatformKeyPress(event.key, platform);
            handlePause(event.key, pause);  
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            handlePlatformKeyRelease(event.key, platform);
        }
    }
}

void update(sf::Clock& clock, Platform& platform, Ball& ball, std::vector<Block>& blocks,
    sf::Text (&texts)[TEXT_COUNT], bool& pause)
{
    const float elapsedTime = clock.restart().asSeconds();
    if (!ball.gameOver && (blocks.size() > 0) && !pause)
    {
        updatePlatform(platform, elapsedTime);
        updateBall(ball, elapsedTime, platform, blocks);
        removeDeathBlocks(blocks);
        updateText(texts, ball);
    }
}

void render(sf::RenderWindow& window, Backgraund& backgraund, Platform& platform, Ball& ball,
    std::vector<Block>& blocks, sf::Text (&texts)[TEXT_COUNT], bool& pause)
{
    window.clear();
    window.draw(backgraund.sprite);
    window.draw(platform.shape);
    window.draw(ball.shape);
    for (auto& block : blocks)
    {
        window.draw(block.shape);
    }
    if (ball.gameOver)
    {
        window.draw(texts[LOSE]);
    }
    else if (blocks.size() == 0)
    {
        window.draw(texts[WIN]);
    }
    else if (pause)
    {
        window.draw(texts[PAUSE]);
    }
    window.draw(texts[SCORE]);
    window.draw(texts[LIVES]);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);
    Backgraund backgraund;
    Platform platform;
    Ball ball;
    std::vector<Block> blocks;
    sf::Font font;
    sf::Text texts[TEXT_COUNT];
    initializeBackgraund(backgraund);
    initializePlatform(platform);
    initializeBall(ball);
    initializeBlocks(blocks);
    initializeText(font, texts);
    sf::Clock clock;
    bool pause = false;
    while (window.isOpen())
    {
        handleEvents(window, platform, pause);
        update(clock, platform, ball, blocks, texts, pause);
        render(window, backgraund, platform, ball, blocks, texts, pause);
    }
    return 0;
}