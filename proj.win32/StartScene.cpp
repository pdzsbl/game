#include"StartScene.h"

#include"SimpleAudioEngine.h"
#include"SettingsScene.h"
#include"HelpScene.h"

USING_NS_CC;

Scene * StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto backGround = Sprite::create("StartScene/StartSceneBG.png");
	backGround->setScale(1.6f);
	backGround->setPosition(visibleSize / 2);
	this->addChild(backGround, 0);

	this->createMenuList();

	CocosDenshion::SimpleAudioEngine::getInstance()->
		playBackgroundMusic("BackGround/Village.mp3", true);

	return true;
}

void StartScene::createMenuList()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	std::string UiNames[] = {
		"CrazyArcade",
		"Start",
		"Settings",
		"Help",
		"Quit" };
	ccMenuCallback Uifuncs[] = { 
		nullptr,
		CC_CALLBACK_1(StartScene::menuStartCallBack, this), 
		CC_CALLBACK_1(StartScene::menuSettingsCallBack,this),
		CC_CALLBACK_1(StartScene::menuHelpCallBack, this),
		CC_CALLBACK_1(StartScene::menuCloseCallBack, this) };
	Vector<MenuItem *> buttons;

	auto frameCache = SpriteFrameCache::getInstance();

	for (int i = 0; i < 5; ++i) {
		auto normal =Sprite::createWithSpriteFrame(
			frameCache->getSpriteFrameByName(UiNames[i] + "Normal.png"));
		auto selected = Sprite::createWithSpriteFrame(
			frameCache->getSpriteFrameByName(UiNames[i] + "Selected.png"));
		auto menuItem = MenuItemSprite::create(normal, selected, Uifuncs[i]);
		//i==0 Crazy Arcade 最大的那个标题
		if (i == 0) {
			menuItem->setScale(1.25f);
		}
		//i!=0 其他MenuItem
		else {
			menuItem->setScale(0.25f);
		}

		buttons.pushBack(menuItem);
	}

	auto menu = Menu::createWithArray(buttons);
	menu->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.6f));
	menu->alignItemsVertically();
	this->addChild(menu, 1);
}

void StartScene::menuStartCallBack(Ref * pSender)
{
}
void StartScene::menuSettingsCallBack(Ref * pSender)
{
	this->addChild(SettingsScene::create(), 9999);
}
void StartScene::menuHelpCallBack(Ref * pSender)
{
	this->addChild(HelpScene::create(), 9999);
	
}
void StartScene::menuCloseCallBack(Ref * pSender)
{
	Director::getInstance()->end();
}
