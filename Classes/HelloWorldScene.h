//
//  HelloWorldScene.h
//  CCRenderTextureCocos2D-x
//
//  Created by Clawoo on 8/29/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
protected:
	cocos2d::CCSprite *_background;

public:
	// initialize the _background variable
	HelloWorld() : _background(NULL) {};
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	~HelloWorld();

	cocos2d::CCSprite* spriteWithColor(cocos2d::ccColor4F bgColor, float textureSize);
	cocos2d::CCSprite* stripedSpriteWithColor1Color2(cocos2d::ccColor4F c1, cocos2d::ccColor4F c2, float textureSize, int nStripes);
	cocos2d::ccColor4F randomBrightColor();
	void genBackground();
	bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);


	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
