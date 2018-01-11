#include "text.h"
#include "backgraund.h"
#include "bonuses.h"

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

void handlePause(const sf::Event::KeyEvent& event, bool& pause, Ball& ball, bool& homeScreen)
{
    switch (event.code)
    {
    case sf::Keyboard::Escape:
        if (pause)
        {
            pause = false;
        }
        else if (!ball.lose && !ball.win && !homeScreen)
        {
            pause = true;
        }
        break;
    }
}

void handleStart(const sf::Event::KeyEvent& event, Ball& ball, bool& start, bool& homeScreen)
{
    switch (event.code)
    {
    case sf::Keyboard::Return:
        if (ball.lose || ball.win || homeScreen)
        {
            start = true;
            homeScreen = false;
        }
        break;
    }
}

void handleEvents(sf::RenderWindow& window, Platform& platform, Ball& ball, bool& pause,
    bool& start, bool& homeScreen)
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
            handlePause(event.key, pause, ball, homeScreen);
            handleStart(event.key, ball, start, homeScreen);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            handlePlatformKeyRelease(event.key, platform);
        }
    }
}

void removeObject(std::vector<Block>& blocks, std::vector<Bonus>& bonuses)
{
    for (auto& block : blocks)
    {
        block.destroyed = true;
    }
    for(auto& bonus : bonuses)
    {
        bonus.destroyed = true;
    }
    removeDeathBlocks(blocks);
    removeDeathBonuses(bonuses);
}

void initializeObject(Platform& platform, Ball& ball, std::vector<Block>& blocks)
{
    initializePlatform(platform);
    initializeBall(ball);
    initializeBlocks(blocks);
}

void update(sf::Clock& clock, Platform& platform, Ball& ball, std::vector<Block>& blocks,
    std::vector<Bonus>& bonuses, sf::Text (&texts)[TEXT_COUNT], bool& pause, bool& start,
    bool& homeScreen)
{
    if (start)
    {
        removeObject(blocks, bonuses);
        initializeObject(platform, ball, blocks);
        start = false;
    }
    const float elapsedTime = clock.restart().asSeconds();
    if (!ball.lose && !ball.win && !pause && !homeScreen)
    {
        updatePlatform(platform, elapsedTime);
        updateBall(ball, elapsedTime, platform, blocks);
        for (auto& block : blocks)
        {
            if (block.destroyed && ((block.direction == DirectionBlocks::BONUS_LIVE) ||
                (block.direction == DirectionBlocks::BONUS_EXTENSION) ||
                (block.direction == DirectionBlocks::BONUS_SLOWING)))
            {
                initializeBonus(bonuses, block);
            }
        }
        removeDeathBlocks(blocks);
        updateBonuses(bonuses, elapsedTime, platform, ball);
        removeDeathBonuses(bonuses);
        if (blocks.size() == 0)
        {
            ball.win = true;
        }
        updateText(texts, ball);
    }
}

void render(sf::RenderWindow& window, Backgraund& backgraund, Platform& platform, Ball& ball,
    std::vector<Block>& blocks, std::vector<Bonus>& bonuses, sf::Text (&texts)[TEXT_COUNT],
    bool& pause, bool& homeScreen)
{
    window.clear();
    window.draw(backgraund.sprite);
    window.draw(platform.shape);
    window.draw(ball.shape);
    for (auto& block : blocks)
    {
        window.draw(block.shape);
    }
    for (auto& bonus : bonuses)
    {
        window.draw(bonus.shape);
    }
    if (homeScreen)
    {
        window.draw(texts[HOME]);
    }
    else if (ball.lose)
    {
        window.draw(texts[LOSE]);
    }
    else if (ball.win)
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
    std::vector<Bonus> bonuses;
    sf::Font font;
    sf::Text texts[TEXT_COUNT];
    initializeBackgraund(backgraund);
    initializeText(font, texts);
    sf::Clock clock;
    bool pause = false;
    bool start = false;
    bool homeScreen = true;
    while (window.isOpen())
    {
        handleEvents(window, platform, ball, pause, start, homeScreen);
        update(clock, platform, ball, blocks, bonuses, texts, pause, start, homeScreen);
        render(window, backgraund, platform, ball, blocks, bonuses, texts, pause, homeScreen);
    }
    return 0;
}