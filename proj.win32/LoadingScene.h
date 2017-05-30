#ifndef __LOADING_SCENE_H_
#define __LOADING_SCENE_H_

#include"cocos2d.h"

class LoadingScene :public cocos2d::Layer {
public:
	static cocos2d::Scene * createScene();		//createScene()
	virtual bool init();						//创建一个加载的进度条
	virtual void update(float dt);				//update()
	virtual void onEnterTransitionDidFinish();	//节点加载后的回调

	CREATE_FUNC(LoadingScene);					//create()

private:
	void createProgressTimer();		//创建进度条
	void progressTimerUpdate();		//更新进度条进度

	void loadSpriteFrame();			//加载精灵帧
	void loadMusicAndEffect();		//加载音乐音效

	cocos2d::ProgressTimer * _progressTimer;	//进度条
	float _progressUpdate;						//进度条更新次数
	int _sourceToLoad;					//加载的资源数
};
#endif // !__LOADING_SCENE_H_
