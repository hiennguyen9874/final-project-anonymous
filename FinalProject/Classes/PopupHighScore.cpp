#include "PopupHighScore.h"
#include "GameValue.h"

bool PopupHighScore::init()
{
	if (!PopUp::init())
		return false;

	this->setTitlePopup("High Score");

	m_labelHighScore = Label::createWithTTF("", "fonts/retro_computer_personal_use.ttf", 50);
	m_labelHighScore->setAdditionalKerning(7.0f);
	m_labelHighScore->setPosition(Vec2(this->m_backgroundContentSize.width * 5.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 5.f / 10.f + m_origin.y));
	m_labelHighScore->setColor(Color3B(255, 0, 0));
	m_popupLayer->addChild(m_labelHighScore, 15);

	return true;
}

void PopupHighScore::onExit()
{
	PopUp::onExit();
}

void PopupHighScore::appear()
{
	m_labelHighScore->setString(std::to_string(GameValue::getInstance()->GetHighScore()));
	PopUp::appear();
}
