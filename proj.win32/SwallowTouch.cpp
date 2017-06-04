#include"SwallowTouch.h"

USING_NS_CC;

bool SwallowTouch::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch * touch, Event * event)
	{
		return true;
	};
	listener->setSwallowTouches(true);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void SwallowTouch::menuCallBack(Ref * pSender)
{
	this->removeFromParentAndCleanup(true);
}