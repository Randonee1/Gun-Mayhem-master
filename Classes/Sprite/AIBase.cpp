#include "AIBase.h"

bool AIBase::init(MapBase* map)
{
    if (!CharacterBase::init(map))
        return false;

    initBody();
    
    return true;
}

void AIBase::initBody()
{
    return;
}

void AIBase::update(float dt)
{
    MoveEvent();
    ShotEvent();
    CharacterBase::update(dt);
}

void AIBase::MoveEvent()
{
    if (opponent->getPosition().x - this->getPosition().x > 400) {
        keyMap["left"] = false;
        keyMap["right"] = true;
    }
    else if (opponent->getPosition().x - this->getPosition().x < -400) {
        keyMap["right"] = false;
        keyMap["left"] = true;
    }
    else {
        keyMap["right"] = false;
        keyMap["left"] = false;
    }

    if (this->floor == opponent->floor && opponent->gun->fire && !this->inTheAir) {
        keyMap["up"] = true;
    }

    if (this->inTheAir && this->getPositionX() < this->map->Floor[floor][0]) {
        keyMap["left"] = false;
        keyMap["right"] = true;
        keyMap["up"] = true;
    }
    else if (this->inTheAir && this->getPositionX() > this->map->Floor[floor][1]) {
        keyMap["right"] = false;
        keyMap["left"] = true;
        keyMap["up"] = true;
    }

    if (!opponent->inTheAir && opponent->floor > this->floor && !this->inTheAir) {
        keyMap["up"] = true;
    }
    else if (!opponent->inTheAir && opponent->floor < this->floor) {
        keyMap["down"] = true;
    }
    
}

void AIBase::ShotEvent()
{
    if ((opponent->floor != map->Floor.size() - 1 || !opponent->inTheAir)  && this->valid )
    {
        if (opponent->getPosition().x - this->getPosition().x < 0 && this->floor == opponent->floor) {
            this->Flip(true);
            keyMap["shot"] = true;
        }
        else if (opponent->getPosition().x - this->getPosition().x > 0 && this->floor == opponent->floor) {
            this->Flip(false);
            keyMap["shot"] = true;
        }
        else {
            keyMap["shot"] = false;
        }
    }
    if (std::abs(opponent->getPositionY() - this->getPositionY())>100) {
        keyMap["shot"] = false;
    }
}


