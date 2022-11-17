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

    bool init(Sprite* background);

    void update(float dt) override;

    void MoveDelay(bool up, bool floor);

    void Flip(bool direction);

    void StopWork();

protected:
    std::vector<OrganBase*> organs;
    std::map<std::string, bool> keyMap;

    Body* body;
    Head* head;
    Face* face;
    Foot* feet1;
    Foot* feet2;
    Hand* hand1;
    Hand* hand2;
    GunBase* gun;
    Sprite* background;

    Status* status = new Status();

    float accelerate;
    float x_speed;
    float y_speed;
    int floor;
    float floor_base;
    float floor_height;

    bool isDoubleJump;
    bool inTheAir;

    Vec2 initPosition;
    std::vector<std::vector<float>> Floor;
    
};

#endif