#include "Transition.h"

Transition::Transition()
{
    m_FinishCnt = 0;
}

Transition::~Transition()
{
}

void Transition::onEnter()
{
	//要切入的场景
	_inScene->setVisible(false);
	TransitionScene::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point stLeftBegin, stLeftEnd, stRightBegin, stRightEnd;

	stLeftBegin.setPoint(0, visibleSize.height / 2.0f);
	stLeftEnd.setPoint(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	stRightBegin.setPoint(visibleSize.width, visibleSize.height / 2.0f);
	stRightEnd.setPoint(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	auto pLeft = Sprite::create("black.png");
	pLeft->setScaleX(visibleSize.width / pLeft->getContentSize().width);
	
	pLeft->setAnchorPoint(Point(1, 0.5));

	addChild(pLeft, 1);

	pLeft->setPosition(stLeftBegin);

	auto pActionLeft = MoveBy::create(_duration / 2, Vec2(visibleSize.width,0));//
	auto pActionLeft2 = MoveBy::create(_duration / 2, Vec2(visibleSize.width, 0));//

	pLeft->runAction(Sequence::create(
		pActionLeft,
		CallFuncN::create(CC_CALLBACK_0(Transition::OnSencondActionFinish, this)),
		DelayTime::create(0.2),
		pActionLeft2,
		CallFuncN::create(CC_CALLBACK_0(Transition::LRFinish, this)),
		NULL));
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

void Transition::LRFinish(void)
{
	TransitionScene::finish();
}

void Transition::OnSencondActionFinish(void)
{
	
	_inScene->setVisible(true);
	_outScene->setVisible(false);
}
