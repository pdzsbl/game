#include"SettingsScene.h"

#include"SimpleAudioEngine.h"
#include"StartScene.h"
#include"MyAudioEngine.h"
#include"SwallowTouch.h"

USING_NS_CC;

Scene * SettingsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingsScene::create();

	scene->addChild(layer);

	return scene;
}

bool SettingsScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->addChild(SwallowTouch::create());

	auto backGround = Sprite::create("HelpScene/HelpSceneBG.png");
	backGround->setScale(1.6f);
	backGround->setPosition(visibleSize / 2);
	backGround->setOpacity(255);
	this->addChild(backGround, 0);

	auto saveItem = MenuItemImage::create(
		"SettingsScene/SaveNormal.png",
		"SettingsScene/SaveNormal,png",
		CC_CALLBACK_1(SettingsScene::menuSaveCallBack, this));
	saveItem->setScale(0.5f);
	auto menu = Menu::createWithItem(saveItem);
	menu->setPosition(
		Point(visibleSize.width*0.5f, visibleSize.height*0.2f));
	this->addChild(menu);

	this->createMenuList();
	
	this->addChild(AudioControl::create());
	
	return true;
}

void SettingsScene::createMenuList()
{
	std::string UiNames[] = {
		"BackGroundMusic",
		"SoundEffect" };
	

}

void SettingsScene::menuSaveCallBack(Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->
		playEffect("SoundEffect/lay.wav");
	this->removeFromParentAndCleanup(true);
}