#include "ShopingScene.h"

USING_NS_CC;

Scene* ShopingScene::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object
	ShopingScene* layer = ShopingScene::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

bool ShopingScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_Background = Sprite::createWithSpriteFrameName("Backpack_background.png");
	this->m_Background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(this->m_Background);

	this->m_cornScore = Sprite::createWithSpriteFrameName("corn_score.png");
	this->m_cornScore->setPosition(visibleSize.width*0.2, visibleSize.height*0.95);
	this->m_cornScore->setScale(0.7);
	this->addChild(this->m_cornScore);

	this->m_Price = Sprite::createWithSpriteFrameName("price.png");
	this->m_Price->setPosition(visibleSize.width/2, visibleSize.height*0.75);
	this->m_Price->setScale(0.7);
	this->addChild(this->m_Price);

	this->m_labelPrice = Label::createWithTTF("0", "fonts/retro_computer_personal_use.ttf", 22);
	this->m_labelPrice->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_labelPrice->setPosition(visibleSize.width *0.53, visibleSize.height*0.751);
	this->addChild(this->m_labelPrice);

	this->m_cornScoreLabel = Label::createWithTTF(std::to_string(GameValue::getInstance()->getcornScore()),
		"fonts/retro_computer_personal_use.ttf", 29);
	this->m_cornScoreLabel->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_cornScoreLabel->setPosition(visibleSize.width *0.2, visibleSize.height*0.95);
	this->addChild(this->m_cornScoreLabel);

	this->m_buy = Button::create("Images/buy.png", "Images/buy-1.png");
	this->m_buy->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.68));
	this->m_buy->setScale(0.7);
	this->addChild(this->m_buy);
	this->m_buy->addTouchEventListener(CC_CALLBACK_2(ShopingScene::OnButtonBuyTouch, this));

	this->m_box = Button::create("Images/box_items1.png", "Images/box_items1.png");
	this->m_box->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.85));
	this->m_box->setScale(0.7);
	this->addChild(this->m_box);

	this->CreateListViewItems();

	this->m_Quit = Button::create("Images/close.png", "Images/close1.png");
	this->m_Quit->setScale(0.3);
	this->m_Quit->setPosition(Vec2(visibleSize.width * 0.95, visibleSize.height * 0.97));
	addChild(this->m_Quit);
	this->m_Quit->addTouchEventListener(CC_CALLBACK_2(ShopingScene::OnButtonQuitTouch, this));

	return true;
}

void ShopingScene::OnButtonQuitTouch(Ref * sender, Widget::TouchEventType type)
{
	//Director::getInstance()->pushScene(pop_scene_with<TransitionFade>::create(0.3));
	Director::getInstance()->popScene();
}
void ShopingScene::CreateListViewItems()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_listItems = ListView::create();
	this->m_listItems->setContentSize(Size(700, 750));
	this->m_listItems->setAnchorPoint(Vec2(0.5, 0.5));
	this->m_listItems->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.31));
	this->m_listItems->setDirection(ScrollView::Direction::VERTICAL);
	this->m_listItems->setTouchEnabled(true);
	this->addChild(this->m_listItems);
	this->m_listItems->addEventListenerListView(this, listvieweventselector(ShopingScene::OnListViewItemsRoll));
	this->m_listItems->setScrollBarEnabled(true);
	this->AddItems();
}
void ShopingScene::AddItems()
{
	for (int i = 0; i < GameItems; i++)
	{
		if (!GameValue::getInstance()->checkItems(i))
		{
			Button* button = Button::create("Images/items_" + std::to_string(i) + ".png", "Images/items_" + std::to_string(i) + "-1.png");
			button->setTouchEnabled(true);
			this->m_listItems->pushBackCustomItem(button);
		}
		else
		{
			Button* button = Button::create("Images/items_" + std::to_string(i) + "-2.png", "Images/items_" + std::to_string(i) + "-2.png");
			button->setTouchEnabled(false);
			this->m_listItems->pushBackCustomItem(button);
		}
	}
}
void ShopingScene::OnListViewItemsRoll(Ref * senderRef, ListView::EventType e)
{
	if (e == ListView::EventType::ON_SELECTED_ITEM_END) {
		this->m_box->loadTextures("Images/box_items_" + std::to_string(this->m_listItems->getCurSelectedIndex()) + ".png",
			"Images/box_items_" + std::to_string(this->m_listItems->getCurSelectedIndex()) + "-1.png");
		this->m_labelPrice->setString(std::to_string(GameValue::getInstance()->getPrice(this->m_listItems->getCurSelectedIndex())));
	}
}

void ShopingScene::OnButtonBuyTouch(Ref * sender, Widget::TouchEventType type)
{
	if (GameValue::getInstance()->getcornScore() >= GameValue::getInstance()->getPrice(this->m_listItems->getCurSelectedIndex()))
	{
		Button* tempButton = (Button*)this->m_listItems->getItem(this->m_listItems->getCurSelectedIndex());
		if (tempButton != nullptr)
		{
			tempButton->loadTextures("Images/items_" + std::to_string(this->m_listItems->getCurSelectedIndex()) + "-2.png",
				"Images/items_" + std::to_string(this->m_listItems->getCurSelectedIndex()) + "-2.png");
			tempButton->setTouchEnabled(false);
			GameValue::getInstance()->getItems(this->m_listItems->getCurSelectedIndex());
		}
	}
}

//void ShopingScene::onEnter()
//{
//	Scene::onEnter();
//}
//
//void ShopingScene::onExit()
//{
//	Scene::onExit();
//}

