#ifndef AI_BASE_H
#define AI_BASE_H


USING_NS_CC;

class AIBase : public Sprite
{
public:

	bool init() override;

	CREATE_FUNC(AIBase);

	void update(float dt) override;
};

#endif