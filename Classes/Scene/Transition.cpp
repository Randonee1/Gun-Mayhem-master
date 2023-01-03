#include "Transition.h"

Transition::Transition()
{
}

Transition::~Transition()
{
}

void Transition::onEnter()
{
    TransitionScene::onEnter();
    _inScene->setVisible(false);
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto transition = Sprite::create("jetpack.png");
    transition->setScaleX(visibleSize.width / transition->getContentSize().width);
    transition->setAnchorPoint(Vec2(0.5, 0.5));
    transition->setPosition(Vec2(-visibleSize.width*5 / 2, visibleSize.height / 2));
    this->addChild(transition, 1);

    transition->runAction(Sequence::create(
        CallFunc::create([&]() {_inScene->setVisible(true); _outScene->setVisible(false); }),
        MoveBy::create(_duration/2, Vec2(visibleSize.width * 2, 0)),
        CallFunc::create([&]() {TransitionScene::finish(); }),
        nullptr
    ));

}

Transition* Transition::create(float t, Scene* scene)
{
    Transition* pScene = new Transition();
    if (pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}
