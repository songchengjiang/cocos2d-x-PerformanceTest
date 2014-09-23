#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	_count = 0;

	_camera =Camera::createPerspective(60, (GLfloat)visibleSize.width/visibleSize.height, 1, 1000);
	_camera->setCameraFlag(CameraFlag::USER1);
	_camera->setPosition3D(Vec3(0.0f, 0.0f, -100.0f));
	_camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	_camera->retain();
	addChild(_camera);

	TTFConfig config("fonts/tahoma.ttf",24);
	_countLabel = Label::createWithTTF(config,"Model Count : ");
	_countLabel->setPosition(Vec2(visibleSize.width - 100.0f, visibleSize.height - 50.0f));
	_countLabel->retain();
	this->addChild(_countLabel, 10);

	auto label = Label::createWithTTF(config,"clean all");
	auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(HelloWorld::cleanAll,this));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	menuItem->setPosition(Vec2(50.0f, visibleSize.height - 50.0f));
	addChild(menu, 10);

	_models = Layer::create();
	_models->retain();
	addChild(_models);
	addNewModel(Vec2(0.0f, 0.0f));

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::addNewModel( const Vec2 &pos )
{
	auto sprite = Sprite3D::create("orc.c3b");
	sprite->setPosition(pos);
	auto animation = Animation3D::create("orc.c3b");
	if (animation)
	{
		auto animate = Animate3D::create(animation);
		sprite->runAction(RepeatForever::create(animate));
	}
	_models->addChild(sprite);
	sprite->setCameraMask(2);

	//auto sprite = Sprite::create("Icon.png");
	//sprite->setPosition(pos);
	//_models->addChild(sprite);
	_count++;
	char str[32];
	sprintf(str, "Model Count : %d", _count);
	_countLabel->setString(str);
}

void HelloWorld::onTouchesEnded( const std::vector<Touch*>& touches, Event* event )
{
	for (auto touch: touches)
	{
		auto location = touch->getLocationInView();
		Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
		auto size = Director::getInstance()->getWinSize();
		_camera->unproject(size, &nearP, &nearP);
		_camera->unproject(size, &farP, &farP);
		Vec3 dir(farP - nearP);
		float dist=0.0f;
		float ndd = Vec3::dot(Vec3(0,0,1),dir);
		if(ndd == 0)
			dist=0.0f;
		float ndo = Vec3::dot(Vec3(0,0,1),nearP);
		dist= (0 - ndo) / ndd;
		Vec3 p =   nearP + dist *  dir;
		addNewModel( Vec2(p.x, p.y) );
	}
}

void HelloWorld::cleanAll(Ref *ref)
{
	auto children = _models->getChildren();
	for (auto iter = children.begin() + 1; iter != children.end(); ++iter)
	{
		_models->removeChild(*iter);
	}
	_count = 1;
	char str[32];
	sprintf(str, "Model Count : %d", _count);
	_countLabel->setString(str);
}

HelloWorld::~HelloWorld()
{
	_models->release();
	_countLabel->release();
	_camera->release();
}
