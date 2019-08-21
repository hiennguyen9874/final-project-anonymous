#pragma once
#include "Config.h"
#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

class SoundMgr
{
public:
	SoundMgr();
	static SoundMgr* getInstance();

	void Preload();
	void StopAll();

	float GetVolumeBg();
	float GetVolumeEffect();

	void SetVolumeBgMusic();

	void SetVolumeBgMusic(float volume);
	void SetVolumeEffectMusic(float volume);

	void AddBgVolume(float delta);
	void AddEffectVolume(float delta);

	void PlayBgSound(int idMap);

	void SetMuteBgMusic(bool mute);
	void SetMuteEffectMusic(bool mute);

	bool isMuteBgMusic() { return this->m_bMuteBgMusic; }
	bool isMusteEffectMusic() { return this->m_bMuteEffectMusic; }

	float GetVolumeBgMusicWithoutMute() { return this->m_volumeBg; }
	float GetVolumeEffectMusicWithoutMute() { return this->m_volumeEffect; }
	void ResetBooleanBgMusicMap();

	void PlayMainMenuMusic();
public:
	int m_idBgMusicMainMenu;
	int m_idBgMusicMap1;	// Map binh thuong
	bool b_Map1;
	int m_idBgMusicMap2;	// Map gio
	bool b_Map2;
	int m_idBgMusicMap3;	// Map bang
	bool b_Map3;
	int m_idBgMusicMap4;	// Map Lau dai
	bool b_Map4;
private:
	static SoundMgr* m_Instance;

	bool m_bMuteBgMusic;
	bool m_bMuteEffectMusic;

	float m_volumeBg;
	float m_volumeEffect;
};
