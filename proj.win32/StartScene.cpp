#include"StartScene.h"

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

	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(
			"StartScene/StartSceneSprites.plist", "StartScene/StartSceneSprites.png");

	auto backGround = Sprite::create("StartScene/StartSceneBG.png");
	backGround->setScale(1.6f);
	backGround->setPosition(visibleSize / 2);
	this->addChild(backGround, 0);

	_menus = this->createMenuList();
	this->addChild(_menus, 1);

	return true;
}

Menu * StartScene::createMenuList()
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
		CC_CALLBACK_1(StartScene::callBackStart, this), 
		CC_CALLBACK_1(StartScene::callBackSettings,this),
		CC_CALLBACK_1(StartScene::callBackHelp, this),
		CC_CALLBACK_1(StartScene::callBackClose, this) };
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

	_menus = Menu::createWithArray(buttons);
	_menus->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.6f));
	_menus->alignItemsVertically();

	return _menus;
}

void StartScene::callBackStart(Ref * pSender)
{
}
void StartScene::callBackSettings(Ref * pSender)
{
}
void StartScene::callBackHelp(Ref * pSender)
{
	Director::getInstance()->pushScene(HelpScene::createScene());
//	Director::getInstance()->replaceScene(HelpScene::createScene());
}
void StartScene::callBackClose(Ref * pSender)
{
	Director::getInstance()->end();
}
