#ifndef __SWALLOW_TOUCH_H_
#define __SWALLOW_TOUCH_H_

#include"cocos2d.h"

class SwallowTouch :public cocos2d::Layer {
public:
	virtual bool init();

	void menuCallBack(cocos2d::Ref * pSender);

	CREATE_FUNC(SwallowTouch);
};
#endif // !__SWALLOW_TOUCH_H_
