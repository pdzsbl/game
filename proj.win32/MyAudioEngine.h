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
	virtual bool init() override;

	void createLabel(std::string & labelName);

	CREATE_FUNC(AudioControl);
private:
	float _volume;
};

#endif // !__MY_AUDIO_ENGINE_H_
