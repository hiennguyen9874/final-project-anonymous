#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
	this->b_Map1 = false;
	this->b_Map2 = false;
	this->b_Map3 = false;
	this->b_Map4 = false;
	this->m_bMuteBgMusic = false;
	this->m_bMuteEffectMusic = false;
	m_volumeBg = 0.5;
	m_volumeEffect = 1;
}

SoundMgr* SoundMgr::m_Instance = nullptr;
SoundMgr* SoundMgr::getInstance()
{
	if (!m_Instance)
		m_Instance = new SoundMgr();
	return m_Instance;
}

void SoundMgr::Preload()
{
	experimental::AudioEngine::preload("audios/effects/king_jump.mp3");
	experimental::AudioEngine::preload("audios/effects/Player_death.mp3");
	experimental::AudioEngine::preload("audios/effects/king_bump.mp3");
	experimental::AudioEngine::preload("audios/effects/king_land.mp3");
	experimental::AudioEngine::preload("audios/effects/gold.mp3");
	experimental::AudioEngine::preload("audios/effects/checkpoint.mp3");
	experimental::AudioEngine::preload("audios/map1.mp3");
	experimental::AudioEngine::preload("audios/map2.mp3");
	experimental::AudioEngine::preload("audios/map3.mp3");
	experimental::AudioEngine::preload("audios/map4.mp3");
	experimental::AudioEngine::preload("audios/mapBoss.mp3");
	experimental::AudioEngine::preload("audios/perfect.mp3");	
	experimental::AudioEngine::preload("audios/mainmenu1.mp3");
}

void SoundMgr::StopAll()
{
	experimental::AudioEngine::stop(this->m_idBgMusicMap1);
	experimental::AudioEngine::stop(this->m_idBgMusicMap2);
	experimental::AudioEngine::stop(this->m_idBgMusicMap3);
	experimental::AudioEngine::stop(this->m_idBgMusicMap4);
	experimental::AudioEngine::stop(this->m_idBgMusicMainMenu);
}

float SoundMgr::GetVolumeBg()
{
	if (this->m_bMuteBgMusic)
		return 0;
	return this->m_volumeBg;
}

float SoundMgr::GetVolumeEffect()
{
	if (this->m_bMuteEffectMusic)
		return 0;
	return this->m_volumeEffect;
}

void SoundMgr::SetVolumeBgMusic()
{
	experimental::AudioEngine::setVolume(SoundMgr::getInstance()->m_idBgMusicMap1, SoundMgr::getInstance()->GetVolumeBg());
	experimental::AudioEngine::setVolume(SoundMgr::getInstance()->m_idBgMusicMap2, SoundMgr::getInstance()->GetVolumeBg());
	experimental::AudioEngine::setVolume(SoundMgr::getInstance()->m_idBgMusicMap3, SoundMgr::getInstance()->GetVolumeBg());
	experimental::AudioEngine::setVolume(SoundMgr::getInstance()->m_idBgMusicMap4, SoundMgr::getInstance()->GetVolumeBg());
	experimental::AudioEngine::setVolume(SoundMgr::getInstance()->m_idBgMusicMainMenu, SoundMgr::getInstance()->GetVolumeBg());
}

void SoundMgr::SetVolumeBgMusic(float volume)
{
	this->m_volumeBg = volume;
	this->SetVolumeBgMusic();
}


void SoundMgr::SetVolumeEffectMusic(float volume)
{
	this->m_volumeEffect = volume;
}

void SoundMgr::AddBgVolume(float delta)
{
	this->m_volumeBg += delta;
	this->SetVolumeBgMusic();
}

void SoundMgr::AddEffectVolume(float delta)
{
	this->m_volumeEffect += delta;
}

void SoundMgr::PlayBgSound(int idMap)
{
	switch (idMap)
	{
	case 1:
		this->StopAll();
		this->m_idBgMusicMap1 = experimental::AudioEngine::play2d("audios/map1.mp3", true);
		experimental::AudioEngine::setVolume(this->m_idBgMusicMap1, this->GetVolumeBg());
		this->b_Map1 = true;
		//this->b_Map2 = false;
		//this->b_Map3 = false;
		//this->b_Map4 = false;
		break;
	case 2:
		this->StopAll();
		this->m_idBgMusicMap2 = experimental::AudioEngine::play2d("audios/map2.mp3", true);
		experimental::AudioEngine::setVolume(this->m_idBgMusicMap2, this->GetVolumeBg());
		//this->b_Map1 = false;
		this->b_Map2 = true;
		//this->b_Map3 = false;
		//this->b_Map4 = false;
		break;
	case 3:
		this->StopAll();
		this->m_idBgMusicMap3 = experimental::AudioEngine::play2d("audios/map3.mp3", true);
		experimental::AudioEngine::setVolume(this->m_idBgMusicMap3, this->GetVolumeBg());
		//this->b_Map1 = false;
		//this->b_Map2 = false;
		this->b_Map3 = true;
		//this->b_Map4 = false;
		break;
	case 4:
		this->StopAll();
		this->m_idBgMusicMap4 = experimental::AudioEngine::play2d("audios/map4.mp3", true);
		experimental::AudioEngine::setVolume(this->m_idBgMusicMap4, this->GetVolumeBg());
		//this->b_Map1 = false;
		//this->b_Map2 = false;
		//this->b_Map3 = false;
		this->b_Map4 = true;
		break;
	default:
		break;
	}
}

void SoundMgr::SetMuteBgMusic(bool mute)
{
	this->m_bMuteBgMusic = mute;
	this->SetVolumeBgMusic();
}

void SoundMgr::SetMuteEffectMusic(bool mute)
{
	this->m_bMuteEffectMusic = mute;
}

void SoundMgr::ResetBooleanBgMusicMap()
{
	this->b_Map1 = false;
	this->b_Map2 = false;
	this->b_Map3 = false;
	this->b_Map4 = false;
}

void SoundMgr::PlayMainMenuMusic()
{
	this->StopAll();
	this->m_idBgMusicMainMenu = experimental::AudioEngine::play2d("audios/mainmenu1.mp3", true);
	experimental::AudioEngine::setVolume(this->m_idBgMusicMainMenu, this->GetVolumeBg());
}
