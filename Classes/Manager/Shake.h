#ifndef SHAKE_H
#define SHAKE_H

#include "cocos2d.h"
USING_NS_CC;


class Shake : public cocos2d::ActionInterval
{
public:
	Shake();

	// Create the action with a time and a strength (same in x and y)
	static Shake* create(float d, float strength);
	// Create the action with a time and strengths (different in x and y)
	static Shake* createWithStrength(float d, float strength_x, float strength_y);
	bool initWithDuration(float d, float strength_x, float strength_y);

protected:

	void startWithTarget(cocos2d::Node* pTarget);
	void update(float time);
	void stop(void);

	Point m_StartPosition;


	// Strength of the action
	float m_strength_x, m_strength_y;
};

#endif //__SHAKE_H__