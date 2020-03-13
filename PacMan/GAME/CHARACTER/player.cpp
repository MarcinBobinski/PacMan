#include "player.h"

Player::Player(Board *map) : GameCharacter(map)
{

}

int Player::imageState()
{
    switch (this->direction) {
    case 1:
        return 0;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 2;
        break;
    case 4:
        return 3;
        break;
    default:
        return 1;
        break;
    }
}