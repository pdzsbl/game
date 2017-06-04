#include"MyAudioEngine.h"

#include"SimpleAudioEngine.h"
#include"ui/UISlider.h"

USING_NS_CC;

using namespace cocos2d::experimental;
using namespace cocos2d::ui;

namespace {
	class TextButton : public cocos2d::Label{
	public:
		static TextButton * create(
			const std::string & text, const std::function<void(TextButton*)> & onTriggered)
		{
			auto ret = new (std::nothrow) TextButton();

			TTFConfig ttfconfig("fonts/impact.ttf", 25);
			if (ret && ret->setTTFConfig(ttfconfig)) {
				ret->setString(text);
				ret->_onTriggered = onTriggered;

				ret->autorelease();

				return ret;
			}

			delete ret;
			ret = nullptr;
			return nullptr;
		}

		void setEnabled(bool enabled)
		{
			_enabled = enabled;
			if (_enabled) {
				this->setColor(Color3B::WHITE);
			}
			else {
				this->setColor(Color3B::GRAY);
			}
		}

	private:
		TextButton()
			: _onTriggered(nullptr), _enabled(true)
		{
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);

			listener->onTouchBegan = CC_CALLBACK_2(TextButton::onTouchBegan, this);
			listener->onTouchEnded = CC_CALLBACK_2(TextButton::onTouchEnded, this);
			listener->onTouchCancelled = CC_CALLBACK_2(TextButton::onTouchCancelled, this);

			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		}

		bool touchHits(Touch * touch)
		{
			auto hitPos = this->convertToNodeSpace(touch->getLocation());
			if (hitPos.x >= 0 && hitPos.y >= 0 &&
				hitPos.x <= _contentSize.width && hitPos.y <= _contentSize.height) {
				return true;
			}
			return false;
		}

		bool onTouchBegan(Touch * touch, Event * event)
		{
			auto hits = touchHits(touch);
			if (hits) {
				scaleButtonTo(0.95f);
			}
			return hits;
		}

		void onTouchEnded(Touch * touch, Event * event)
		{
			if (_enabled) {
				auto hits = touchHits(touch);
				if (hits && _onTriggered) {
					_onTriggered(this);
				}
			}

			scaleButtonTo(1);
		}

		void onTouchCancelled(Touch * touch, Event * event)
		{
			scaleButtonTo(1);
		}

		void scaleButtonTo(float scale)
		{
			auto action = ScaleTo::create(0.05f, scale);
			action->setTag(10000);
			stopActionByTag(10000);
			runAction(action);
		}

		std::function<void(TextButton*)> _onTriggered;

		bool _enabled;
	};

	class SliderEx : public Slider
	{
	public:
		static SliderEx* create() {
			auto ret = new (std::nothrow) SliderEx();
			if (ret && ret->init())
			{
				ret->loadBarTexture("MyAudioEngine/sliderTrack.png");
				ret->loadSlidBallTextures(
					"MyAudioEngine/sliderThumb.png", "MyAudioEngine/sliderThumb.png", "");
				ret->loadProgressBarTexture("MyAudioEngine/sliderProgress.png");
				ret->setTouchEnabled(true);

				ret->autorelease();

				return ret;
			}
			CC_SAFE_DELETE(ret);
			return ret;
		}

		void setRatio(float ratio) {
			ratio = clampf(ratio, 0.0f, 1.0f);

			_ratio = ratio;
			setPercent(100 * _ratio);
		}

		float getRatio() {
			_ratio = 1.0f * _percent / _maxPercent;
			return _ratio;
		}

	private:
		float _ratio;
	};
}

MyAudioEngine::MyAudioEngine()
	: _isDestroyed(std::make_shared<bool>(false))
{
}

void MyAudioEngine::onExit()
{
	*_isDestroyed = true;
	
	Node::onExit();
}

bool AudioControl::init()
{
	auto ret = MyAudioEngine::init();
	
	this->createLabel(std::string("BackGround Music"));
	this->createLabel(std::string("Sound Effect"));

	return ret;
}

void AudioControl::createLabel(std::string & labelName)
{
	_volume = 1.0f;

	std::string fontFilePath = "fonts/impact.ttf";

	auto layerSize = Director::getInstance()->getVisibleSize();

	auto volumeSlider = SliderEx::create();
	volumeSlider->setPercent(100);
	volumeSlider->addEventListener([=](Ref* sender, Slider::EventType event) {
		SliderEx *slider = dynamic_cast<SliderEx *>(sender);
		_volume = slider->getRatio();

		if (labelName == "BackGround Music") {
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_volume);
		}
		else if (labelName == "Sound Effect") {
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(_volume);
		}
	});
	if (labelName == "BackGround Music") {
		volumeSlider->setPosition(Point(layerSize.width*0.5f, layerSize.height*0.33f));
	}
	else if (labelName == "Sound Effect") {
		volumeSlider->setPosition(Point(layerSize.width*0.5f, layerSize.height*0.67f));
	}
	addChild(volumeSlider);

	auto & volumeSliderPos = volumeSlider->getPosition();
	auto & sliderSize = volumeSlider->getContentSize();
	auto volumeLabel = Label::createWithTTF("volume:", fontFilePath, 48);
	volumeLabel->setColor(Color3B(255, 192, 168));
	volumeLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	volumeLabel->setPosition(volumeSliderPos.x - sliderSize.width / 2, volumeSliderPos.y);
	addChild(volumeLabel);

	auto backGroundLabel = Label::createWithTTF(labelName, fontFilePath, 48);
	backGroundLabel->setColor(Color3B(255, 192, 168));
	backGroundLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	backGroundLabel->setPosition(volumeSliderPos.x, volumeSliderPos.y + sliderSize.height / 2);
	addChild(backGroundLabel);
}