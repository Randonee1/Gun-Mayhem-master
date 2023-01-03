#ifndef TRANSITION_H
#define TRANSITION_H

#include "cocos2d.h"
USING_NS_CC;

class Transition : public TransitionScene
{
public:
	Transition();
	virtual ~Transition();

	void onEnter() override;
	
	static Transition* create(float t, Scene* scene);

private:
};

#endif