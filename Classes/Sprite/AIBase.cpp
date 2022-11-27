#include "AIBase.h"
#include <algorithm>
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
    int distance = 100;
    if(opponent->floor>=0 && opponent->floor<this->map->Floor.size()){//玩家在地图中
    //找人
        if (this->floor == opponent->floor) {//同一层，左右移动
            if (opponent->getPosition().x - this->getPosition().x > distance ) {
                keyMap["left"] = false;
                keyMap["right"] = true;
            }
            else if (opponent->getPosition().x - this->getPosition().x < -distance) {
                keyMap["right"] = false;
                keyMap["left"] = true;
            }
            else {
                keyMap["right"] = false;
                keyMap["left"] = false;
            }
        }
        else {//不在同一层，需要上下移动
            int up = 0;
            if (this->floor < opponent->floor) {//up
                 up = 1;
            }
            else {
                 up = -1;//down
            }

            if (this->floor - opponent->floor == 1) {//相差一层的情况:找人
                int i = 0;
                for ( ; i < this->map->Floor[floor + up].size(); i += 2) {
                    if (opponent->getPosition().x > this->map->Floor[floor + up][i] && opponent->getPosition().x < this->map->Floor[floor + up][i + 1]) {//位于上台阶下方，直接跳跃
                        break;
                    }
                }
                if (this->floor == opponent->floor) {//左右移动
                    if (opponent->getPosition().x - this->getPosition().x > 0) {
                        keyMap["left"] = false;
                        keyMap["right"] = true;
                    }
                    else if (opponent->getPosition().x - this->getPosition().x < 0) {
                        keyMap["right"] = false;
                        keyMap["left"] = true;
                    }
                    else {
                        keyMap["right"] = false;
                        keyMap["left"] = false;
                    }
                }
                //上下移动
                if (this->getPosition().x > this->map->Floor[floor + up][i] && this->getPosition().x < this->map->Floor[floor + up][i + 1]) {//位于上台阶下方，直接跳跃
                    if (up == 1) {
                        keyMap["up"] = true;
                    }
                    else {
                        keyMap["down"] = true;
                    }
                }
            }
            else {//相差多层：，找最近上下楼路线
                float min_distance = 99999;
                int step = 0;
                for (int i = 0; i < this->map->Floor[floor + up].size(); i += 2) {
                    if (this->getPosition().x > this->map->Floor[floor + up][i] && this->getPosition().x < this->map->Floor[floor + up][i + 1]) {//位于上台阶下方，直接跳跃
                         if (up == 1) {
                             keyMap["up"] = true;
                          }
                          else {
                              keyMap["down"] = true;
                          }
                            break;
                    }//计算距离最近台阶的距离
                    min_distance = std::min(std::abs(this->getPosition().x- this->map->Floor[floor + up][i]) , min_distance);
                    min_distance = std::min(std::abs(this->getPosition().x - this->map->Floor[floor + up][i+1]), min_distance);
                    step = min_distance == std::abs(this->getPosition().x - this->map->Floor[floor + up][i]) ?  i : step;
                    step = min_distance == std::abs(this->getPosition().x - this->map->Floor[floor + up][i+1]) ? i+1 : step;

                    }
                    //前往最近台阶
                    if(this->getPosition().x > this->map->Floor[floor + up][step]){//
                        keyMap["left"] = true;
                        if (this->getPosition().x - 20 <= this->map->Floor[floor + up][step]) {
                            if (up == 1) {
                                keyMap["up"] = true;
                            }
                            else {
                                keyMap["down"] = true;
                            }
                        }
                    }
                    else if(this->getPosition().x < this->map->Floor[floor + up][step] ){
                        keyMap["right"] = true;
                        if (this->getPosition().x + 20 >= this->map->Floor[floor + up][step]) {
                            if (up == 1) {
                                keyMap["up"] = true;
                            }
                            else {
                                keyMap["down"] = true;
                            }
                        }
                    }
                  
            }
        }
    }
    /*if (opponent->getPosition().x - this->getPosition().x > 400) {
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
    }*/
    
}

void AIBase::ShotEvent()
{
    if ((opponent->floor != map->Floor.size() - 1 || !opponent->inTheAir)  && this->valid )
    {
        if (opponent->getPosition().x - this->getPosition().x < 0 && this->getPosition().y == opponent->getPosition().y/*this->floor == opponent->floor*/) {
            this->Flip(true);
            keyMap["shot"] = true;
        }
        else if (opponent->getPosition().x - this->getPosition().x > 0 && this->getPosition().y == opponent->getPosition().y /* this->floor == opponent->floor*/) {
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


