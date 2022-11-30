#include "SkillPackage.h"

float SkillPackage::updatetime = 10;

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

    package = Sprite::createWithSpriteFrameName("speedup.png");
    this->addChild(package, 0);

    return true;
}

void SkillPackage::GetPackage(CharacterBase* player)
{
    if (player->skill)
        delete player->skill;
    player->skill = new SpeedUp(player);
}

void SkillPackage::update(float dt)
{
    PackageBase::update(dt);
}
