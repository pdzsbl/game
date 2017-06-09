#ifndef __SETTINGS_SCENE_H
#define __SETTINGS_SCENE_H_

#include"cocos2d.h"

class SettingsScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();

	virtual bool init();

	void createSliders();

	void menuSaveCallBack(cocos2d::Ref * pSender);

	CREATE_FUNC(SettingsScene);
private:
};
#endif // !__SETTINGS_SCENE_H
