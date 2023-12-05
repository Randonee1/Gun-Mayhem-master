#include "Shake.h"
#include "cocos2d.h"
USING_NS_CC;

Shake::Shake() : m_strength_x(0), m_strength_y(0)
{
}

Shake* Shake::create(float d, float strength)
{
	return createWithStrength(d, strength, strength);
}

Shake* Shake::createWithStrength(float duration, float strength_x, float strength_y)
{
	Shake* pRet = new Shake();

	if (pRet && pRet->initWithDuration(duration, strength_x, strength_y))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}


	return pRet;
}

bool Shake::initWithDuration(float duration, float strength_x, float strength_y)
{
	if (ActionInterval::initWithDuration(duration))
	{
		m_strength_x = strength_x;
		m_strength_y = strength_y;

		return true;
	}

	return false;
}


static float fgRangeRand(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return rnd * (max - min) + min;
}

void Shake::update(float dt)
{
	float randx = fgRangeRand(-m_strength_x, m_strength_x) * dt;
	float randy = fgRangeRand(-m_strength_y, m_strength_y) * dt;
	
	_target->setPosition(m_StartPosition + Vec2(randx, randy));
}

void Shake::startWithTarget(Node* pTarget)
{
	ActionInterval::startWithTarget(pTarget);

	
	m_StartPosition = pTarget->getPosition();
}

void Shake::stop(void)
{
	
	this->getTarget()->setPosition(m_StartPosition);

	ActionInterval::stop();
}