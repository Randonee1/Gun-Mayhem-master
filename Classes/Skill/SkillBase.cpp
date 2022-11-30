#include "SkillBase.h"

SkillBase::SkillBase()
{
}

SkillBase::~SkillBase()
{
}

void SkillBase::update(float dt)
{
	duration += dt;
}
