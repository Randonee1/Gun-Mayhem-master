#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

#include "cocos2d.h"
#include "Organ/Body.h"
#include "Organ/Face.h"
#include "Organ/Foot.h"
#include "Organ/Hand.h"
#include "Organ/Head.h"
#include "Organ/OrganBase.h"
#include "Weapons/Gun/GunBase.h"
#include "Map/MapBase.h"

USING_NS_CC;

typedef struct _Status {
	float acceleration;
    float resistance;
    float gravitation;
    float x_maxSpeed;
    float y_maxSpeed;
    float recoil_speed;
}Status;

class CharacterBase : public Sprite
{
public:

    bool init(MapBase* map);

    void update(float dt) override;

    void MoveDelay(bool up, bool floor);

    void Flip(bool direction);

    void StopWalk();

    void DrawHalo();

    void GetOpponent(CharacterBase* opponent);

    std::vector<OrganBase*> organs;
    std::map<std::string, bool> keyMap;

    CharacterBase* opponent;

    Body* body;
    Head* head;
    Face* face;
    Foot* feet1;
    Foot* feet2;
    Hand* hand1;
    Hand* hand2;
    GunBase* gun;
    MapBase* map;

    Status* status = new Status();

    float accelerate;
    float x_speed;
    float y_speed;
    int floor;

    bool isDoubleJump;
    bool inTheAir = true;
    bool valid = true;   
    bool hit = false;
};

#endif