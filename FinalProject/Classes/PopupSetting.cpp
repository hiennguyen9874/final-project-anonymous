#include "PopupSetting.h"
#include "SoundMgr.h"

bool PopupSetting::init()
{
	if (!PopUp::init())
		return false;

	this->setTitlePopUpWithSprite("92.png");

	/*******************************************/
	// label
	auto  _labelMusic = Label::createWithTTF("MUSIC", "fonts/retro_computer_personal_use.ttf", 30);
	_labelMusic->setAdditionalKerning(7.0f);
	_labelMusic->setPosition(Vec2(this->m_backgroundContentSize.width * 8.25f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 6.6 / 10 + m_origin.y));
	_labelMusic->setColor(Color3B(255, 0, 0));
	m_popupLayer->addChild(_labelMusic, 15);

	// slider bar
	m_sliderOptionMusics[0] = Slider::create("Images/93.png", "Images/dot (2).png");
	m_sliderOptionMusics[0]->setTag(0);
	m_sliderOptionMusics[0]->loadProgressBarTexture("Images/94.png");
	m_sliderOptionMusics[0]->setScaleX(0.415);
	m_sliderOptionMusics[0]->setScaleY(0.431);

	m_sliderOptionMusics[0]->setPosition(Vec2(this->m_backgroundContentSize.width * 4.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 6.5 / 10 + m_origin.y));
	m_sliderOptionMusics[0]->addEventListener(CC_CALLBACK_2(PopupSetting::sliderEventMusic, this));
	m_popupLayer->addChild(m_sliderOptionMusics[0], 15);
	
	/*******************************************/
	// label
	auto  _labelSound = Label::createWithTTF("SOUND", "fonts/retro_computer_personal_use.ttf", 30);
	_labelSound->setAdditionalKerning(7.0f);
	_labelSound->setPosition(Vec2(this->m_backgroundContentSize.width * 8.25f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * (6.6 - 1 * 2) / 10 + m_origin.y));
	_labelSound->setColor(Color3B(255, 0, 0));
	m_popupLayer->addChild(_labelSound, 15);

	// slider bar
	m_sliderOptionMusics[1] = Slider::create("Images/93.png", "Images/dot (2).png");
	m_sliderOptionMusics[1]->setTag(1);
	m_sliderOptionMusics[1]->loadProgressBarTexture("Images/94.png");
	m_sliderOptionMusics[1]->setScaleX(0.415);
	m_sliderOptionMusics[1]->setScaleY(0.431);

	m_sliderOptionMusics[1]->setPosition(Vec2(this->m_backgroundContentSize.width * 4.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * (6.5 - 1 * 2) / 10 + m_origin.y));
	m_sliderOptionMusics[1]->addEventListener(CC_CALLBACK_2(PopupSetting::sliderEventSound, this));
	m_popupLayer->addChild(m_sliderOptionMusics[1], 15);
	/*******************************************/

	// Music
	if (SoundMgr::getInstance()->isMusteEffectMusic())
		m_buttonMusic = Button::create("Images/music_off.png", "Images/music_off1.png");
	else
		m_buttonMusic = Button::create("Images/misic.png", "Images/misic1.png");
	m_buttonMusic->setScale(0.5);
	m_buttonMusic->setPosition(Vec2(this->m_backgroundContentSize.width * 3.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 3.f / 10.f + m_origin.y));
	m_popupLayer->addChild(m_buttonMusic, 15);
	m_buttonMusic->addTouchEventListener(CC_CALLBACK_2(PopupSetting::OnButtonMusic, this));

	// Sound
	if (SoundMgr::getInstance()->isMuteBgMusic())
		m_buttonSound = Button::create("Images/sound_off.png", "Images/sound_off1.png");
	else
		m_buttonSound = Button::create("Images/sound.png", "Images/sound1.png");
	m_buttonSound->setScale(0.5);
	m_buttonSound->setPosition(Vec2(this->m_backgroundContentSize.width * 7.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 3.f / 10.f + m_origin.y));
	m_popupLayer->addChild(m_buttonSound, 15);
	m_buttonSound->addTouchEventListener(CC_CALLBACK_2(PopupSetting::OnButtonSound, this));
	return true;
}

void PopupSetting::onExit()
{
	PopUp::onExit();
}

void PopupSetting::appear()
{
	this->m_sliderOptionMusics[0]->setPercent(SoundMgr::getInstance()->GetVolumeEffectMusicWithoutMute() * 100);
	this->m_sliderOptionMusics[1]->setPercent(SoundMgr::getInstance()->GetVolumeBgMusicWithoutMute() * 100);
	PopUp::appear();
}

void PopupSetting::sliderEventMusic(Ref* pSender, Slider::EventType type)
{
	switch (type)
	{
	case Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		SoundMgr::getInstance()->SetVolumeEffectMusic(this->m_sliderOptionMusics[0]->getPercent() / 100.0f);
		break;
	}
	default:
		break;
	}
}

void PopupSetting::sliderEventSound(Ref* pSender, Slider::EventType type)
{
	switch (type)
	{
	case Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		SoundMgr::getInstance()->SetVolumeBgMusic(this->m_sliderOptionMusics[1]->getPercent() / 100.0f);
		break;
	}
	default:
		break;
	}
}


void PopupSetting::OnButtonSound(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (SoundMgr::getInstance()->isMuteBgMusic())
		{
			m_buttonSound->loadTextures("Images/sound.png", "Images/sound1.png");
			SoundMgr::getInstance()->SetMuteBgMusic(false);

		}
		else
		{
			m_buttonSound->loadTextures("Images/sound_off.png", "Images/sound_off1.png");
			SoundMgr::getInstance()->SetMuteBgMusic(true);
		}
		break;
	default:
		break;
	}
}

void PopupSetting::OnButtonMusic(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (SoundMgr::getInstance()->isMusteEffectMusic())
		{
			m_buttonMusic->loadTextures("Images/misic.png", "Images/misic1.png");
			SoundMgr::getInstance()->SetMuteEffectMusic(false);
		}
		else
		{
			m_buttonMusic->loadTextures("Images/music_off.png", "Images/music_off1.png");
			SoundMgr::getInstance()->SetMuteEffectMusic(true);
		}
		break;
	default:
		break;
	}
}
