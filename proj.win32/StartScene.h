#ifndef __START_SCENE_H_
#define __START_SCENE_H_

#include"cocos2d.h"

class StartScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();				//createScene()
	virtual bool init();								//加载一个菜单

	void createMenuList();					//创建菜单

	void menuStartCallBack(cocos2d::Ref* sender);			//Play
	void menuSettingsCallBack(cocos2d::Ref* pSender);		//Settings
	void menuHelpCallBack(cocos2d::Ref* pSender);			//Help
	void menuCloseCallBack(cocos2d::Ref * pSender);			//Quit		Done

	CREATE_FUNC(StartScene);							//create()
};
#endif // !__START_SCENE_H_
