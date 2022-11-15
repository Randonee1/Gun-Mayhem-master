#ifndef CAMPAIGN_CHOISE_H
#define CAMPAIGN_CHOISE_H

#include "cocos2d.h"
USING_NS_CC;

class CampaignChoise : public Layer
{
public:

	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(CampaignChoise);
};

#endif