#include "backgraund.h"

void initializeBackgraund(Backgraund& backgraund)
{
    backgraund.texture.loadFromFile("res/backgraund.jpg");
    backgraund.sprite.setTexture(backgraund.texture);
    backgraund.sprite.setPosition({0, 0});
}