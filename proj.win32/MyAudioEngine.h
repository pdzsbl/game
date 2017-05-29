#ifndef __MY_AUDIO_ENGINE_H_
#define __MY_AUDIO_ENGINE_H_

#include"cocos2d.h"

class MyAudioEngine :public cocos2d::Node {
public:
	MyAudioEngine();

	virtual void onExit() override;
protected:
	std::shared_ptr<bool> _isDestroyed;
};

class AudioControl : public MyAudioEngine
{
public:
	virtual ~AudioControl();

	virtual bool init() override;
	virtual void update(float dt) override;

	CREATE_FUNC(AudioControl);
private:
	int _audioID;
	bool _loopEnabled;
	float _volume;
	float _duration;
	float _timeRatio;

	void * _playItem;
//	bool _updateTimeSlider;
	bool _isStopped;
};

#endif // !__MY_AUDIO_ENGINE_H_
