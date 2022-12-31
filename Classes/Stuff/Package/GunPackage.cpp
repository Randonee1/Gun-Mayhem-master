#include "GunPackage.h"

float GunPackage::updatetime = 8;

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

    switch (rand() % 10)
    {
    case 0:
        gun = Gun_MG_P90::create();
        break;
    case 1:
        gun = Gun_MG_MP5::create();
        break;
    case 2:
        gun = Gun_Gatling::create();
        break;
    case 3:
        gun = Gun_MG_MP7::create();
        break;
    case 4:
        gun = Gun_MG_Uzi::create();
        break;  
    case 5:
        gun = Gun_Modern_Sniper::create();
        break;
    case 6:
        gun = Gun_Revolver::create();
        break;
    case 7:
        gun = Gun_Double::create();
        break;
    case 8:
        gun = Sanurai_Sword::create();
        break;
    case 9:
        gun = BaseBall_Bat::create();
        break;
    }

    //gun = Gun_MG_P90::create();
    //gun = Gun_MG_MP5::create();
    //gun = Gun_Gatling::create();
    //gun = Gun_MG_MP7::create();
    //gun = Gun_MG_Uzi::create();
    //gun = Gun_Modern_Sniper::create();
    //gun = Gun_Revolver::create();
    //gun = Gun_Double::create();
    //gun = Sanurai_Sword::create();
    //gun = BaseBall_Bat::create();

    package = Sprite::create("gun_bubble.png");
    auto Gun = gun->RightGun();
    Gun->setAnchorPoint(Vec2(0.5, 0.5));
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