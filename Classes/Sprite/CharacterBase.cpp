#include "CharacterBase.h"

bool CharacterBase::init()
{
    if (!Sprite::init())
        return false;

    accelerate = 0;
    x_speed = 0;
    y_speed = 0;
    isDoubleJump = false;
    inTheAir = false;

    this->scheduleUpdate();

	return true;
}

void CharacterBase::update(float dt)
{
	Sprite::update(dt);

    if (!inTheAir) {
        isDoubleJump = false;
        if (keyMap["up"]) {
            inTheAir = true;
            y_speed = status->y_maxSpeed;
            MoveDelay(true, false);
            keyMap["up"] = false;
        }
        else
            y_speed = 0;
    }
    else {
        //跳起暂停走路动作
        StopWork();

        if (std::abs(y_speed) <= std::abs(status->gravitation * dt))
            MoveDelay(false, false);
        if (!isDoubleJump && keyMap["up"]) {
            y_speed = status->y_maxSpeed / 1.2;
            MoveDelay(true, false);
            isDoubleJump = true;
        }
        y_speed += status->gravitation* dt;
        keyMap["up"] = false;
    }
    if (getPositionY() + y_speed * dt < floor) {
        MoveDelay(true, true);
        inTheAir = false;
        y_speed = 0;

        this->setPositionY(floor);
    }
    else
        this->setPositionY(getPositionY() + y_speed * dt);


    if ((keyMap["left"] ^ keyMap["right"])) {

        if (keyMap["left"])
            Flip(true);
        else
            Flip(false);

        accelerate = keyMap["right"] ? status->acceleration: -status->acceleration;
        if (!inTheAir) {

            feet1->Work(false);
            feet2->Work(true);
            hand1->Work(true);
            hand2->Work(false);

        }
        x_speed += accelerate * dt;
        if (std::abs(x_speed) > status->x_maxSpeed)
            x_speed -= accelerate * dt;
    }
    else {
        accelerate = x_speed > 0 ? -status->resistance : status->resistance;
        if (std::abs(accelerate * dt) > std::abs(x_speed))
            x_speed = 0;
        else
            x_speed += accelerate * dt;
    }
    this->setPositionX(getPositionX() + x_speed * dt);

    if (keyMap["shot"]) {
        hand1->RaiseHandToShoot(this->getParent());
        this->_flippedX ? x_speed += status->recoil_speed : x_speed -= status->recoil_speed;
        if (std::abs(x_speed) > status->x_maxSpeed)
            this->_flippedX ? x_speed = status->x_maxSpeed : x_speed = -status->x_maxSpeed;
    }
}

void CharacterBase::MoveDelay(bool up, bool floor)
{
    for (int i = 2; i < organs.size(); i++)
        organs[i]->MoveDelay(up, floor);
}

void CharacterBase::Flip(bool direction)
{
    this->setFlippedX(direction);
    for (auto organ : organs)
        organ->setFlippedX(direction);
}

void CharacterBase::StopWork()
{
    feet1->organ->stopActionByTag(10);
    feet2->organ->stopActionByTag(10);
    feet1->actionState = false;
    feet2->actionState = false;
    hand1->organ->stopActionByTag(10);
    hand2->organ->stopActionByTag(10);
    hand1->actionState = false;
    hand2->actionState = false;
}
