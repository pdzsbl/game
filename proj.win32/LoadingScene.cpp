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
	
	//�������������Ҹ��£���ʼλ����Ϊ����е�
	_progressTimer->setMidpoint(Point(0.0f, 0.5f));
	_progressTimer->setBarChangeRate(Point(1.0f, 0.f));

	//���ν�����
	_progressTimer->setType(ProgressTimer::Type::BAR);

	_progressTimer->setPosition(visibleSize / 2);
	this->addChild(_progressTimer);
}

void LoadingScene::progressTimerUpdate()
{
	//ÿ����һ����Դ�ͽ���һ�ν������ĸ��£�ͬʱ�Լ�Ҫ���ص���Դ��
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
	//���������´���=100/��Ҫ���ص���Դ����
	_progressUpdate = 100 / static_cast<float>(_sourceToLoad);

}

