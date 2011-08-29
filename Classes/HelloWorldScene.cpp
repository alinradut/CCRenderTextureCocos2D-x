//
//  HelloWorldScene.cpp
//  CCRenderTextureCocos2D-x
//
//  Created by Clawoo on 8/29/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::~HelloWorld()
{
}

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	this->genBackground();
	this->setIsTouchEnabled(true);
	
	return true;
}

cocos2d::CCSprite* HelloWorld::spriteWithColor(ccColor4F bgColor, float textureSize)
{
	// 1: Create new CCRenderTexture
	CCRenderTexture *rt = CCRenderTexture::renderTextureWithWidthAndHeight(textureSize, textureSize);
	
	// 2: Call CCRenderTexture:begin
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	
	// 3: Draw into the texture
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	float gradientAlpha = 0.7;    
	CCPoint vertices[4];
	ccColor4F colors[4];
	int nVertices = 0;
	
	vertices[nVertices] = CCPointMake(0, 0);
	colors[nVertices++] = (ccColor4F){0, 0, 0, 0 };
	vertices[nVertices] = CCPointMake(textureSize, 0);
	colors[nVertices++] = (ccColor4F){0, 0, 0, 0};
	vertices[nVertices] = CCPointMake(0, textureSize);
	colors[nVertices++] = (ccColor4F){0, 0, 0, gradientAlpha};
	vertices[nVertices] = CCPointMake(textureSize, textureSize);
	colors[nVertices++] = (ccColor4F){0, 0, 0, gradientAlpha};
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	
	CCSprite *noise = CCSprite::spriteWithFile("Noise.png");
	noise->setBlendFunc((ccBlendFunc){GL_DST_COLOR, GL_ZERO});
	noise->setPosition(ccp(textureSize/2, textureSize/2));
	noise->visit();
	
	// 4: Call CCRenderTexture:end
	rt->end();
	
	// 5: Create a new Sprite from the texture
	return CCSprite::spriteWithTexture(rt->getSprite()->getTexture());
}

cocos2d::ccColor4F HelloWorld::randomBrightColor()
{
	while (true) {
		float requiredBrightness = 192;
		
		ccColor4B randomColor = 
			ccc4(arc4random() % 255,
				 arc4random() % 255,
				 arc4random() % 255,
				 255);
		if (randomColor.r > requiredBrightness || 
            randomColor.g > requiredBrightness ||
            randomColor.b > requiredBrightness) {
            return ccc4FFromccc4B(randomColor);
        }
	}
}

void HelloWorld::genBackground()
{
	if (_background != NULL)
	{
		_background->removeFromParentAndCleanup(true);
	}
	
	ccColor4F bgColor = this->randomBrightColor();
	_background = this->spriteWithColor(bgColor, 512);
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_background->setPosition(ccp(winSize.width/2, winSize.height/2));
	
	this->addChild(_background, -1);
}

bool HelloWorld::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	this->genBackground();
	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
