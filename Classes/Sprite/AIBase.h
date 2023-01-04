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

	bool Readytodie(CharacterBase* player);
	bool opponentReadytodie();

	void jumpTofloor(int, int);//斜跳跃至上下层的第step个台阶

	void FindFloor();//不同层之间的寻路

	//void getColsePackage(PackageBase*);//捡起最近的包裹

protected:
	bool shotLasttime;
};

#endif