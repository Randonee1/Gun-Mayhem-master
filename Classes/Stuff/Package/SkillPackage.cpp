#include "SkillPackage.h"
#include "Skill/Defense.h"
#include "Skill/SpeedUp.h"
#include "Skill/SuperJump.h"
#include "Skill/Jetpack.h"
#include "Skill/ExtraLife.h"
#include "Skill/DoubleTeam.h"

float SkillPackage::updatetime = 4;

SkillPackage* SkillPackage::createWithSkill(MapBase* map)
{
    auto Skill = new SkillPackage();
    if (Skill && Skill->initWithGun(map)) {
        Skill->autorelease();
        return Skill;
    }
    CC_SAFE_DELETE(Skill);
    return NULL;
}

bool SkillPackage::initWithGun(MapBase* map)
{
    if (!PackageBase::init(map))
        return false;

    switch (rand() % 5) 
    {
    case 0:
        skill = DEFENSE;
        package = Sprite::createWithSpriteFrameName("shieldPack.png");
        break;
    case 1:
        skill = SPEED_UP;
        package = Sprite::createWithSpriteFrameName("speedup.png");
        break;
    case 2:
        skill = DOUBLE_TEAM;
        package = Sprite::createWithSpriteFrameName("doubleTeam.png");
        break;
    case 3:
        skill = JETPACK;
        package = Sprite::createWithSpriteFrameName("jetPack.png");
        break;
    case 4:
        skill = EXTRA_LIFE;
        package = Sprite::createWithSpriteFrameName("extraLife.png");
        break;
    case 5:
        skill = SUPER_JUMP;
        package = Sprite::createWithSpriteFrameName("superJump.png");
        break;
    }

    /*skill = SPEED_UP;
    package = Sprite::createWithSpriteFrameName("speedup.png");*/
    /*skill = SUPER_JUMP;
    package = Sprite::create("super_jump.png");*/
    /*skill = JETPACK;
    package = Sprite::createWithSpriteFrameName("jetPack.png");*/
    /*skill = EXTRA_LIFE;
    package = Sprite::createWithSpriteFrameName("extraLife.png");*/
    /*skill = DOUBLE_TEAM;
    package = Sprite::createWithSpriteFrameName("doubleTeam.png");*/

    this->addChild(package, 0);

    return true;
}

void SkillPackage::GetPackage(CharacterBase* player)
{
    for (auto sk : player->skills) {
        if (skill == sk->skillTpye)
            return;
    }

    switch (skill) {
    case DEFENSE:
        player->skills.push_back(new Defense(player));
        break;
    case SPEED_UP:
        player->skills.push_back(new SpeedUp(player));
        break;
    case SUPER_JUMP:
        player->skills.push_back(new SuperJump(player));
        break;
    case JETPACK:
        player->skills.push_back(new Jetpack(player));
        break;
    case EXTRA_LIFE:
        player->skills.push_back(new ExtraLife(player));
        break;
    case DOUBLE_TEAM:
        player->skills.push_back(new DoubleTeam(player));
        break;
    }
    
}

void SkillPackage::update(float dt)
{
    PackageBase::update(dt);
}
