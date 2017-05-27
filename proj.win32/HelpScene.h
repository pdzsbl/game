#ifndef __HELP_SCENE_H_
#define __HELP_SCENE_H_

#include"cocos2d.h"

class HelpScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();		//createScene()
	virtual bool init();						//显示一段话

	void createParagraph();						//生成一段话的Label

	void menuCallBack(cocos2d::Ref * pSender);

	CREATE_FUNC(HelpScene);						//create()
};
#endif // !__HELP_SCENE_H_
