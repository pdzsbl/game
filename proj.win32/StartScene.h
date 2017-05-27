#ifndef __START_SCENE_H_
#define __START_SCENE_H_

#include"cocos2d.h"

class StartScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();				//createScene()
	virtual bool init();								//加载一个菜单

	cocos2d::Menu * createMenuList();					//创建菜单

	void callBackStart(cocos2d::Ref* sender);			//Play
	void callBackSettings(cocos2d::Ref* pSender);		//Settings
	void callBackHelp(cocos2d::Ref* pSender);			//Help
	void callBackClose(cocos2d::Ref * pSender);			//Quit		Done

	CREATE_FUNC(StartScene);							//create()
private:
	cocos2d::Menu * _menus;
};
#endif // !__START_SCENE_H_
