#include"HelpScene.h"

USING_NS_CC;

bool HelpScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = Sprite::create("HelpScene/HelpSceneBG.png");
	backGround->setScale(1.6f);
	backGround->setPosition(visibleSize / 2);
	backGround->setOpacity(255);
	this->addChild(backGround, 0);

	auto backItem = MenuItemImage::create(
		"HelpScene/BackNormal.png",
		"HelpScene/BackSelected.png",
		CC_CALLBACK_1(HelpScene::menuBackCallBack, this));
	backItem->setScale(0.5f);
	auto menu = Menu::createWithItem(backItem);
	menu->setPosition(
		Point(visibleSize.width*0.5f, visibleSize.height*0.2f));
	this->addChild(menu);

	this->createParagraph();

	return true;
}

void HelpScene::createParagraph()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	std::string helps[] = {
		"You must have seen this game before.",
		"Use arrow keys to move your character.",
		"Use space to place some bubbles.",
		"ENJOY YOURSELF!" };
	Vector<MenuItem *> menuItems;

	auto num = sizeof(helps) / sizeof(helps[0]);
	for (int i = 0; i < num; i++) {
		auto label = Label::create(helps[i], "Impact", 50);
		label->setColor(Color3B::ORANGE);
		auto menuItem = MenuItemLabel::create(label);

		if (i == 0) {
			menuItem->setScale(1.25f);
		}
		if (i == num - 1) {
			menuItem->setScale(2.0f);
		}
		menuItems.pushBack(menuItem);
	}

	auto menu = Menu::createWithArray(menuItems);
	menu->alignItemsVertically();
	menu->setAnchorPoint(Point::ANCHOR_MIDDLE);
	menu->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.6f));
	this->addChild(menu, 1);
}

void HelpScene::menuBackCallBack(Ref * pSender)
{
	this->removeFromParentAndCleanup(true);
}