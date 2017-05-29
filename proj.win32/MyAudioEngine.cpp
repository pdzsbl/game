#include"MyAudioEngine.h"

#include"AudioEngine.h"
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
	
	_audioID = AudioEngine::INVALID_AUDIO_ID;
	_loopEnabled = false;
	_volume = 1.0f;
	_duration = AudioEngine::TIME_UNKNOWN;
	_timeRatio = 0.0f;
	_isStopped = false;

	std::string fontFilePath = "fonts/impact.ttf";

//	auto & layerSize = this->getContentSize();
	auto & layerSize = Director::getInstance()->getVisibleSize();

	auto playItem = TextButton::create("play", [&](TextButton* button) {
		if (_audioID == AudioEngine::INVALID_AUDIO_ID) {
			_audioID = AudioEngine::play2d("background.mp3", _loopEnabled, _volume);

			if (_audioID != AudioEngine::INVALID_AUDIO_ID) {
				_isStopped = false;

				button->setEnabled(false);
				AudioEngine::setFinishCallback(_audioID, [&](int id, const std::string & filePath) {
					log("_audioID(%d), _isStopped:(%d), played over!!!", _audioID, _isStopped);

					assert(!_isStopped); // Stop audio should not trigger finshed callback
					_audioID = AudioEngine::INVALID_AUDIO_ID;
					((TextButton*)_playItem)->setEnabled(true);
				});
			}
		}
	});
	_playItem = playItem;
	playItem->setPosition(layerSize.width * 0.25f, layerSize.height * 0.8f);
	addChild(playItem);

	auto stopItem = TextButton::create("stop", [&](TextButton* button) {
		if (_audioID != AudioEngine::INVALID_AUDIO_ID) {
			_isStopped = true;
			AudioEngine::stop(_audioID);

			_audioID = AudioEngine::INVALID_AUDIO_ID;
			((TextButton*)_playItem)->setEnabled(true);
		}
	});
	stopItem->setPosition(layerSize.width * 0.5f, layerSize.height * 0.8f);
	addChild(stopItem);

	auto pauseItem = TextButton::create("pause", [&](TextButton* button) {
		if (_audioID != AudioEngine::INVALID_AUDIO_ID) {
			AudioEngine::pause(_audioID);
		}
	});
	pauseItem->setPosition(layerSize.width * 0.75f, layerSize.height * 0.8f);
	addChild(pauseItem);

	auto volumeSlider = SliderEx::create();
	volumeSlider->setPercent(100);
	volumeSlider->addEventListener([&](Ref* sender, Slider::EventType event) {
		SliderEx *slider = dynamic_cast<SliderEx *>(sender);
		_volume = slider->getRatio();
		if (_audioID != AudioEngine::INVALID_AUDIO_ID) {
			AudioEngine::setVolume(_audioID, _volume);
		}
	});
	volumeSlider->setPosition(Vec2(layerSize.width * 0.5f, layerSize.height * 0.35f));
	addChild(volumeSlider);

	auto & volumeSliderPos = volumeSlider->getPosition();
	auto & sliderSize = volumeSlider->getContentSize();
	auto volumeLabel = Label::createWithTTF("volume:  ", fontFilePath, 32);
	volumeLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	volumeLabel->setPosition(volumeSliderPos.x - sliderSize.width / 2, volumeSliderPos.y);
	addChild(volumeLabel);

	this->schedule(CC_CALLBACK_1(AudioControl::update, this), 0.1f, "update_key");

	return ret;
}

void AudioControl::update(float dt)
{
	if (_audioID != AudioEngine::INVALID_AUDIO_ID) {
		if (_duration == AudioEngine::TIME_UNKNOWN) {
			_duration = AudioEngine::getDuration(_audioID);
		}
	}
}

AudioControl::~AudioControl()
{
}

