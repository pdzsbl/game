#ifndef __HELP_SCENE_H_
#define __HELP_SCENE_H_

#include"cocos2d.h"

class HelpScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();		//createScene()
	virtual bool init();						//��ʾһ�λ�

	void createParagraph();						//����һ�λ���Label

	void menuCallBack(cocos2d::Ref * pSender);

	CREATE_FUNC(HelpScene);						//create()
};
#endif // !__HELP_SCENE_H_
