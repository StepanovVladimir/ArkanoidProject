#include "blocks.h"

constexpr float BLOCK_WIDTH = 60;
constexpr float BLOCK_HEIGHT = 20;
const sf::Color BLOCK_COLOR = sf::Color(255, 255, 0);
constexpr int COUNT_BLOCKS_X = 8;
constexpr int COUNT_BLOCKS_Y = 8;

void initializeBlocks(std::vector<Block>& blocks)
{
    for (int iX = 0; iX < COUNT_BLOCKS_X; ++iX)
    {
        for (int iY = 0; iY < COUNT_BLOCKS_Y; ++iY)
        {
            Block block;
            blocks.push_back(block);
            size_t i = blocks.size() - 1;
            float positionX = (iX + 1) * (BLOCK_WIDTH + 3) + 16.5;
            float positionY = (iY + 2) * (BLOCK_HEIGHT + 3);
            blocks[i].shape.setPosition({positionX, positionY});
            blocks[i].shape.setSize({BLOCK_WIDTH, BLOCK_HEIGHT});
            blocks[i].shape.setFillColor(BLOCK_COLOR);
            blocks[i].shape.setOrigin({BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2});
        }
    }
}

bool isBlockDestroyed(Block block)
{
    return (block.destroyed);
}

void removeDeathBlocks(std::vector<Block>& blocks)
{
    auto newEnd = std::remove_if(blocks.begin(), blocks.end(), isBlockDestroyed);
    blocks.erase(newEnd, blocks.end());
}