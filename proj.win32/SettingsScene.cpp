#include"SettingsScene.h"

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


	return true;
}