#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

CC_CONSTRUCTOR_ACCESS:
	virtual ~HelloWorld();

protected:

	void addNewModel(const cocos2d::Vec2 &pos);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void cleanAll(cocos2d::Ref *ref);
	void switchSkinOpt(cocos2d::Ref *ref);

protected:

	cocos2d::Camera *_camera;
	cocos2d::Layer *_models;
	cocos2d::Label *_countLabel;
	cocos2d::Label *_skinoptLabel;
	int _count;
	bool _skinopt;
};

#endif // __HELLOWORLD_SCENE_H__
