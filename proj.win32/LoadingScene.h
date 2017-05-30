#ifndef __LOADING_SCENE_H_
#define __LOADING_SCENE_H_

#include"cocos2d.h"

class LoadingScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();		//createScene()
	virtual bool init();						//����һ�����صĽ�����
	virtual void update(float dt);				//update()
	virtual void onEnterTransitionDidFinish();	//�ڵ���غ�Ļص�

	CREATE_FUNC(LoadingScene);					//create()

private:
	void createProgressTimer();		//����������
	void progressTimerUpdate();		//���½���������

	void loadSpriteFrame();			//���ؾ���֡
	void loadMusicAndEffect();		//����������Ч

	cocos2d::ProgressTimer * _progressTimer;	//������
	float _progressUpdate;						//���������´���
	int _sourceToLoad;					//���ص���Դ��
};
#endif // !__LOADING_SCENE_H_
