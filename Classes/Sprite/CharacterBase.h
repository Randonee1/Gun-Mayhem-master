#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

#include "cocos2d.h"
#include "Organ/Body.h"
#include "Organ/Face.h"
#include "Organ/Foot.h"
#include "Organ/Hand.h"
#include "Organ/Head.h"
#include "Organ/Hat.h"
#include "Organ/OrganBase.h"
#include "Weapons/Gun/GunBase.h"
#include "Stuff/Dust.h"
//#include "Stuff/Package/SkillPackage.h"

USING_NS_CC;

class SkillBase;
class MapBase;

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

    bool init(int tag, MapBase* map);

    Sprite* clone();

    bool InTheBoundary(std::vector<float>& floor, float x) const;

    void update(float dt) override;

    void MoveDelay(bool up, bool floor);

    void Flip(bool direction);

    void StopWalk();

    void DrawHalo();

    void GunChange(GunBase* change);

    void Death();

    void GetOpponent(CharacterBase* opponent);

    void DustUpdate();

    std::vector<OrganBase*> organs;
    std::vector<Dust*> dusts;
    std::map<std::string, bool> keyMap;

    //SkillPackage* skill;

    CharacterBase* opponent;

    Body* body;
    Head* head;
    Face* face;
    Hat* hat;
    Foot* feet1;
    Foot* feet2;
    Hand* hand1;
    Hand* hand2;
    GunBase* gun;
    GunBase* initGun;
    GunBase* throwGun;
    MapBase* map;
    Label* playerName;

    Status* status = new Status();

    //SkillBase* skill;
    std::vector<SkillBase*>skills;

    float accelerate;
    float x_speed;
    float y_speed;
    int floor;
    int floor_actual;

    bool isDoubleJump;
    bool inTheAir = true;
    bool valid = true;   
    bool hit = false;
    bool defense;
    bool firstLand = true;
    bool isDoppelganger = false;

    int shotCount = 0;
    int hitCount = 0;

    int Live;

    int tag;
};

#endif