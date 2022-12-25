#ifndef AI_BASE_H
#define AI_BASE_H

#include "cocos2d.h"
#include "CharacterBase.h"

USING_NS_CC;

class AIBase : public CharacterBase
{
public:

	bool init(int tag, MapBase* map);

	virtual void initBody();

	void update(float dt) override;

	void MoveEvent();

	void ShotEvent();
	void reset();

	int find_thisStep();

	bool opponentReadytodie();

	void jumpTofloor(int, int);//斜跳跃至上下层的第step个台阶

	int findCloestStep(int floor);//寻找到floor层的最近step

	//void getColsePackage(PackageBase*);//捡起最近的包裹

protected:
	bool shotLasttime;
};

#endif