#include "GunPackage.h"

GunPackage* GunPackage::createWithGun(MapBase* map)
{
    auto Gun = new GunPackage();
    if (Gun && Gun->initWithGun(map)) {
        Gun->autorelease();
        return Gun;
    }
    CC_SAFE_DELETE(Gun);
    return NULL;
}

bool GunPackage::initWithGun(MapBase* map)
{
    if (!PackageBase::init(map))
        return false;

    gun = Gun_MG_P90::create();
    package = Sprite::create("gun_bubble.png");
    auto Gun = gun->ThrowGun();
    Gun->setPosition(package->getContentSize().width / 2, package->getContentSize().height /2);
    package->addChild(Gun, -1);
    this->addChild(package, 0);

    return true;
}

void GunPackage::GetPackage(CharacterBase* player)
{
    player->GunChange(gun->clone());
}

void GunPackage::update(float dt) 
{
    PackageBase::update(dt);
    
}