#include"LoadingScene.h"
#include"StartScene.h"

USING_NS_CC;

Scene * LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	this->createProgressTimer();
	this->scheduleUpdate();

	return true;
}

void LoadingScene::createProgressTimer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto barSprite = Sprite::create("LoadingScene/LoadingBar.png");
	_progressTimer = ProgressTimer::create(barSprite);
	_progressTimer->setScale(2.0f);
	_progressTimer->setPercentage(0.0f);
	
	//进度条从左向右更新，起始位置设为左侧中点
	_progressTimer->setMidpoint(Point(0.0f, 0.5f));
	_progressTimer->setBarChangeRate(Point(1.0f, 0.f));

	//条形进度条
	_progressTimer->setType(ProgressTimer::Type::BAR);

	_progressTimer->setPosition(visibleSize / 2);
	this->addChild(_progressTimer);
}

void LoadingScene::progressTimerUpdate()
{
	//每加载一次资源就进行一次进度条的更新，同时自减要加载的资源数
	if (--_sourceToLoad) {
		_progressTimer->setPercentage(100.0f - (_progressUpdate * _sourceToLoad));
	}
	else {
		auto pft = ProgressFromTo::create(0.5f, _progressTimer->getPercentage(), 100);

		auto callFunc = CallFunc::create([=] 
		{
			auto delayTime = DelayTime::create(1.0f);
			auto callFunc = CallFunc::create([] 
			{
				Director::getInstance()->replaceScene(StartScene::createScene());
			}
			);
			auto action = Sequence::create(delayTime, callFunc, nullptr);
			this->runAction(action);
		}
		);

		auto action = Sequence::create(pft, callFunc, nullptr);

		_progressTimer->runAction(action);
	}
}

void LoadingScene::update(float dt)
{
	this->progressTimerUpdate();
}

void LoadingScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	_sourceToLoad = 100;
	//进度条更新次数=100/需要加载的资源数量
	_progressUpdate = 100 / static_cast<float>(_sourceToLoad);

}

