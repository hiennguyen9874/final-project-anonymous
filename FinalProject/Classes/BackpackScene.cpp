#include "BackpackScene.h"

USING_NS_CC;

Scene* BackpackScene::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object
	BackpackScene* layer = BackpackScene::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BackpackScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_Background = Sprite::createWithSpriteFrameName("Backpack_background.png");
	this->m_Background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(this->m_Background);

	this->m_Character = Sprite::createWithSpriteFrameName("redbird.png");
	this->m_Character->setScale(0.5);
	this->m_Character->setPosition(visibleSize.width / 2, visibleSize.height*0.8);
	this->addChild(this->m_Character);

	this->m_cornScore = Sprite::createWithSpriteFrameName("corn_score.png");
	this->m_cornScore->setPosition(visibleSize.width*0.2, visibleSize.height*0.95);
	this->m_cornScore->setScale(0.7);
	this->addChild(this->m_cornScore);

	this->m_cornScoreLabel = Label::createWithTTF(std::to_string(GameValue::getInstance()->getcornScore()),
		"fonts/retro_computer_personal_use.ttf", 29);
	this->m_cornScoreLabel->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_cornScoreLabel->setPosition(visibleSize.width *0.2, visibleSize.height*0.95);
	this->addChild(this->m_cornScoreLabel);

	this->CreateLeftBox();

	this->CreateRightBox();

	this->CreateListViewItems();
	this->CreateListViewSlingShot();

	this->m_Quit = Button::create("Images/close.png", "Button/close1.png");
	this->m_Quit->setScale(0.3);
	this->m_Quit->setPosition(Vec2(visibleSize.width * 0.95, visibleSize.height * 0.97));
	addChild(this->m_Quit);
	this->m_Quit->addTouchEventListener(CC_CALLBACK_2(BackpackScene::OnButtonQuitTouch, this));
	
	return true;
}

void BackpackScene::OnButtonQuitTouch(Ref * sender, Widget::TouchEventType type)
{
	Director::getInstance()->popScene();
}

void BackpackScene::OnListViewItemsRoll(Ref * senderRef, ListView::EventType e)
{
	if (e == ListView::EventType::ON_SELECTED_ITEM_END) {
		Button* tempButton = (Button*)this->m_listItems->getItem(this->m_listItems->getCurSelectedIndex());
		if (tempButton != nullptr)
		{
			int index = tempButton->getTag();
			this->m_boxLeft->loadTextures("Images/box_items_" + std::to_string(index) + ".png",
				"Images/box_items_" + std::to_string(index) + "-1.png");
			GameValue::getInstance()->setUsedItem(index);
		}
	}
}

void BackpackScene::OnListViewSlingShotRoll(Ref * senderRef, ListView::EventType e)
{
	if (e == ListView::EventType::ON_SELECTED_ITEM_END) {
		Button* tempButton = (Button*)this->m_listSlingShotItems->getItem(this->m_listSlingShotItems->getCurSelectedIndex());
		if (tempButton != nullptr)
		{
			int index = tempButton->getTag();
			this->m_boxRight->loadTextures("Images/box_slingshot" + std::to_string(index) + ".png",
				"Images/box_slingshot" + std::to_string(index) + "-1.png");
			GameValue::getInstance()->setUsedSlingShot(index);
		}
	}
}

void BackpackScene::OnBoxLeftTouch(Ref * sender, Widget::TouchEventType type)
{
	this->m_listItems->setVisible(true);
	this->m_listItems->setEnabled(true);
	this->m_listSlingShotItems->setVisible(false);
	this->m_listSlingShotItems->setEnabled(false);
}

void BackpackScene::OnBoxRightTouch(Ref * sender, Widget::TouchEventType type)
{
	this->m_listItems->setVisible(false);
	this->m_listItems->setEnabled(false);
	this->m_listSlingShotItems->setVisible(true);
	this->m_listSlingShotItems->setEnabled(true);
}

void BackpackScene::OnButtonTakeOffTouch(Ref * sender, Widget::TouchEventType type)
{
	this->m_boxLeft->loadTextures("Images/box_items1.png", "Images/box_items.png");
	GameValue::getInstance()->setUsedItem(-1);
}

void BackpackScene::CreateRightBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_boxRight = Button::create("Images/box_slingshot" +std::to_string(GameValue::getInstance()->getUsedSlingShot()) + ".png",
		"Images/box_slingshot" + std::to_string(GameValue::getInstance()->getUsedSlingShot()) + "-1.png");
	this->m_boxRight->setPosition(Vec2(visibleSize.width*0.82, visibleSize.height*0.8));
	this->m_boxRight->setScale(0.7);
	this->addChild(this->m_boxRight);
	this->m_boxRight->addTouchEventListener(CC_CALLBACK_2(BackpackScene::OnBoxRightTouch, this));
}

void BackpackScene::CreateLeftBox()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->m_takeOff = Button::create("Images/close.png", "Images/close1.png");
	this->m_takeOff->setScale(0.25);
	this->m_takeOff->setPosition(Vec2(visibleSize.width * 0.27, visibleSize.height * 0.85));
	addChild(this->m_takeOff,1);
	this->m_takeOff->addTouchEventListener(CC_CALLBACK_2(BackpackScene::OnButtonTakeOffTouch, this));

	if (GameValue::getInstance()->getUsedItem() == -1)
	{
		this->m_boxLeft = Button::create("Images/box_items1.png", "Images/box_items.png");
		this->m_boxLeft->setPosition(Vec2(visibleSize.width*0.18, visibleSize.height*0.8));
		this->m_boxLeft->setScale(0.7);
		this->addChild(this->m_boxLeft);
		this->m_boxLeft->addTouchEventListener(CC_CALLBACK_2(BackpackScene::OnBoxLeftTouch, this));
	}
	else
	{
		this->m_boxLeft = Button::create("Images/box_items_" + std::to_string(GameValue::getInstance()->getUsedItem()) + ".png",
			"Images/box_items_" +std::to_string(GameValue::getInstance()->getUsedItem()) + "-1.png");
		this->m_boxLeft->setPosition(Vec2(visibleSize.width*0.18, visibleSize.height*0.8));
		this->m_boxLeft->setScale(0.7);
		this->addChild(this->m_boxLeft);
		this->m_boxLeft->addTouchEventListener(CC_CALLBACK_2(BackpackScene::OnBoxLeftTouch, this));
	}
}

void BackpackScene::CreateListViewItems()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_listItems = ListView::create();
	this->m_listItems->setContentSize(Size(700, 750));
	this->m_listItems->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_listItems->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.31));
	this->m_listItems->setDirection(ScrollView::Direction::VERTICAL);
	this->m_listItems->setTouchEnabled(true);
	this->addChild(this->m_listItems);
	this->m_listItems->addEventListenerListView(this, listvieweventselector(BackpackScene::OnListViewItemsRoll));
	this->m_listItems->setScrollBarEnabled(true);
	this->m_listItems->setVisible(true);
	this->m_listItems->setEnabled(true);
	this->AddItems();
}

void BackpackScene::CreateListViewSlingShot()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_listSlingShotItems = ListView::create();
	this->m_listSlingShotItems->setContentSize(Size(700, 750));
	this->m_listSlingShotItems->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_listSlingShotItems->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.31));
	this->m_listSlingShotItems->setDirection(ScrollView::Direction::VERTICAL);
	this->m_listSlingShotItems->setTouchEnabled(true);
	this->addChild(this->m_listSlingShotItems);
	this->m_listSlingShotItems->addEventListenerListView(this, listvieweventselector(BackpackScene::OnListViewSlingShotRoll));
	this->m_listSlingShotItems->setScrollBarEnabled(true);
	this->m_listSlingShotItems->setVisible(false);
	this->m_listSlingShotItems->setEnabled(false);
	this->AddSlingShot();
}

void BackpackScene::AddSlingShot()
{
	for (int i = 0; i < SlingShots; i++)
	{
		if (GameValue::getInstance()->checkSlingShots(i))
		{
			Button* button = Button::create("Images/SlingShot" + std::to_string(i) + ".png", "Images/SlingShot" + std::to_string(i) + "-1.png");
			button->setTouchEnabled(true);
			button->setTag(i);
			this->m_listSlingShotItems->pushBackCustomItem(button);
		}
	}
}

void BackpackScene::AddItems()
{
	for (int i = 0; i < GameItems; i++)
	{
		if (GameValue::getInstance()->checkItems(i))
		{
			Button* button = Button::create("Images/items_" + std::to_string(i) + ".png", "Images/items_" + std::to_string(i) + "-1.png");
			button->setTouchEnabled(true);
			button->setTag(i);
			this->m_listItems->pushBackCustomItem(button);
		}
	}
}
