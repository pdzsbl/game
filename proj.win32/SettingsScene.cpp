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

	// ����һ��������
	auto music_slider = Slider::create();
	// ���û�����������
	music_slider->loadBarTexture("SettingsScene/sliderTrack.png");
	// ���û������Ĺ�������
	music_slider->loadSlidBallTextures("SettingsScene/sliderThumb.png", "SettingsScene/sliderThumb.png", "");
	// ���ô��������Ľ���������
	music_slider->loadProgressBarTexture("SettingsScene/sliderProgress.png");
	// ��ȡ֮ǰ���õı�����������
	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");
	// ����ǵ�һ�ν������ó��������ñ������ֻ�����Ĭ�ϳ�ʼֵΪ100
	if (musicPercent == 0.0f) {
		musicPercent = 100.0f;
	}
	// ���ñ������ֻ������ĳ�ʼֵ
	music_slider->setPercent(musicPercent);
	music_slider->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.75f));
	// ����¼�������,����������������
	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		// ������İٷֱȷ����仯ʱ
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			// ��û������ٷֱ�
			int percent = music_slider->getPercent();
			// ���ñ�������ֵΪ�������ٷֱ�/100����ΪSlider�İٷֱ���1-100����MusicVolume��ȡֵ��0.0-1.0
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent) / 100);
			//Volume = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
			// �洢���õı�������ֵ
			UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
		}
	});
	this->addChild(music_slider);

	auto sound_text = Text::create("SoundEffect", "Impact", 48);
	sound_text->setColor(Color3B::ORANGE);
	sound_text->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.5));
	this->addChild(sound_text);

	// ����һ��������
	auto effects_slider = Slider::create();
	// ���û�����������
	effects_slider->loadBarTexture("SettingsScene/sliderTrack.png");
	// ���û������Ĺ�������
	effects_slider->loadSlidBallTextures("SettingsScene/sliderThumb.png", "SettingsScene/sliderThumb.png", "");
	// ���ô��������Ľ���������
	effects_slider->loadProgressBarTexture("SettingsScene/sliderProgress.png");
	// ��ȡ֮ǰ���õ���Ч����
	float effectPercent = UserDefault::getInstance()->getFloatForKey("effectPercent");
	// ����ǵ�һ�ν������ó�����������Ч������Ĭ�ϳ�ʼֵΪ100
	if (effectPercent == 0.0f) {
		effectPercent = 100.0f;
	}
	// ������Ч�������ĳ�ʼֵ
	effects_slider->setPercent(effectPercent);
	effects_slider->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.5));
	// ����¼�������,������Ч����
	effects_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		// ������İٷֱȷ����仯ʱ
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			// ��û������ٷֱ�
			int percent = effects_slider->getPercent();
			// ���ñ�����Чֵ
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(float(percent) / 100);
			// �洢���õı�������ֵ
			UserDefault::getInstance()->setFloatForKey("effectPercent", percent);
		}
	});
	this->addChild(effects_slider);
}

void SettingsScene::menuSaveCallBack(Ref * pSender)
{
	this->removeFromParentAndCleanup(true);
}