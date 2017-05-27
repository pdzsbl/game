#ifndef __SETTINGS_SCENE_H
#define __SETTINGS_SCENE_H_

#include"cocos2d.h"

class SettingsScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();
	virtual bool init();

	void createMenuList();

	void callBack();

	CREATE_FUNC(SettingsScene);
};
#endif // !__SETTINGS_SCENE_H
