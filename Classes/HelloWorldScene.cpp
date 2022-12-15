/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "HelloWorldScene.h"
#include "Scene/StartScene.h" 
USING_NS_CC;


bool HelloWorld::init()
{
	if (!Scene::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Ìí¼ÓlogoÍ¼Æ¬
	auto sprite = Sprite::create("logo.jpeg");
	if (sprite == nullptr)
	{
		return false;
	}
	else
	{
		sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
		sprite->setTextureRect(Rect(0, 0, 0.85f * sprite->getContentSize().width, sprite->getContentSize().height));
		this->addChild(sprite, 0);
	}
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::SwitchToStartScene), 3.0f);//ÑÓ³ÙÇÐ»»³¡¾°
	return true;
}


void HelloWorld::SwitchToStartScene(float ft)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Start.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Game.mp3");
	Director::getInstance()->replaceScene(TransitionFade::create(1.f, StartScene::create()));
}
