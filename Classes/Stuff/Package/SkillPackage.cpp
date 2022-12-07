#include "SkillPackage.h"

float SkillPackage::updatetime = 1000;

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

    switch (rand() % 4) 
    {
    case 0:
        skill = DEFENSE;
        break;
    case 1:
        skill = SPEED_UP;
        package = Sprite::createWithSpriteFrameName("speedup.png");
        break;
    case 3:
        skill = SUPER_JUMP;
        package = Sprite::createWithSpriteFrameName("tinilize.png");
        break;
    case 4:
        skill = JETPACK;
        package = Sprite::createWithSpriteFrameName("tinilize.png");
        break;
    }

    skill = SPEED_UP;
    package = Sprite::createWithSpriteFrameName("speedup.png");
   /* skill = SUPER_JUMP;
    package = Sprite::create("super_jump.png");*/
   /* skill = JETPACK;
    package = Sprite::createWithSpriteFrameName("tinilize.png");*/
    this->addChild(package, 0);

    return true;
}

void SkillPackage::GetPackage(CharacterBase* player)
{
    if (player->skill)
        delete player->skill;

    switch (skill) {
    case DEFENSE:
        player->skill = new Defense(player);
        break;
    case SPEED_UP:
        player->skill = new SpeedUp(player);
        break;
    case SUPER_JUMP:
        player->skill = new SuperJump(player);
        break;
    case JETPACK:
        player->skill = new Jetpack(player);
        break;
    }
}

void SkillPackage::update(float dt)
{
    PackageBase::update(dt);
}
