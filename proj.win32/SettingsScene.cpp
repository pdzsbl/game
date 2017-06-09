#include"SettingsScene.h"

#include"SimpleAudioEngine.h"
#include"StartScene.h"
#include"ui/CocosGUI.h"
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

	auto backGround = Sprite::create("SettingsScene/SettingsSceneBG.png");
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
	
//	this->addChild(AudioControl::create());
	this->createSliders();

	return true;
}

void SettingsScene::createSliders()
{
	using namespace ui;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto music_text = Text::create("BackgroundMusic", "Impact", 48);
	music_text->setColor(Color3B::ORANGE);
	music_text->setPosition(Point(visibleSize.width*0.2f, visibleSize.height*0.75f));
	this->addChild(music_text);

	// 创建一个滑动条
	auto music_slider = Slider::create();
	// 设置滑动条的纹理
	music_slider->loadBarTexture("SettingsScene/sliderTrack.png");
	// 设置滑动条的滚轮纹理
	music_slider->loadSlidBallTextures("SettingsScene/sliderThumb.png", "SettingsScene/sliderThumb.png", "");
	// 设置处理滑动条的进度条纹理
	music_slider->loadProgressBarTexture("SettingsScene/sliderProgress.png");
	// 获取之前设置的背景音乐音量
	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");
	// 如果是第一次进入设置场景，设置背景音乐滑动条默认初始值为100
	if (musicPercent == 0.0f) {
		musicPercent = 100.0f;
	}
	// 设置背景音乐滑动条的初始值
	music_slider->setPercent(musicPercent);
	music_slider->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.75f));
	// 添加事件监听器,调整背景音乐音量
	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		// 当滑块的百分比发生变化时
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			// 获得滑动条百分比
			int percent = music_slider->getPercent();
			// 设置背景音乐值为滑动条百分比/100，因为Slider的百分比是1-100，而MusicVolume的取值是0.0-1.0
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent) / 100);
			//Volume = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
			// 存储设置的背景音乐值
			UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
		}
	});
	this->addChild(music_slider);

	auto sound_text = Text::create("SoundEffect", "Impact", 48);
	sound_text->setColor(Color3B::ORANGE);
	sound_text->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.5));
	this->addChild(sound_text);

	// 创建一个滑动条
	auto effects_slider = Slider::create();
	// 设置滑动条的纹理
	effects_slider->loadBarTexture("SettingsScene/sliderTrack.png");
	// 设置滑动条的滚轮纹理
	effects_slider->loadSlidBallTextures("SettingsScene/sliderThumb.png", "SettingsScene/sliderThumb.png", "");
	// 设置处理滑动条的进度条纹理
	effects_slider->loadProgressBarTexture("SettingsScene/sliderProgress.png");
	// 获取之前设置的音效音量
	float effectPercent = UserDefault::getInstance()->getFloatForKey("effectPercent");
	// 如果是第一次进入设置场景，设置音效滑动条默认初始值为100
	if (effectPercent == 0.0f) {
		effectPercent = 100.0f;
	}
	// 设置音效滑动条的初始值
	effects_slider->setPercent(effectPercent);
	effects_slider->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.5));
	// 添加事件监听器,调整音效音量
	effects_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		// 当滑块的百分比发生变化时
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			// 获得滑动条百分比
			int percent = effects_slider->getPercent();
			// 设置背景音效值
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(float(percent) / 100);
			// 存储设置的背景音乐值
			UserDefault::getInstance()->setFloatForKey("effectPercent", percent);
		}
	});
	this->addChild(effects_slider);
}

void SettingsScene::menuSaveCallBack(Ref * pSender)
{
	this->removeFromParentAndCleanup(true);
}