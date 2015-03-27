#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"

USING_NS_CC;
using namespace CocosDenshion;

Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance() {
	if (m_instance == nullptr) {
		m_instance = new Audio();
	}
	return m_instance;
}

Audio::Audio() :
		isPause(false) {
}

void Audio::playBGM() {
	if (GameData::getInstance()->getisPause())
		return;
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/class.mp3",
			true);
}

void Audio::playSprite() {
	if (GameData::getInstance()->getisPause())
		return;
	SimpleAudioEngine::getInstance()->playEffect("music/12.wav");
}

void Audio::playEliminate() {
	if (GameData::getInstance()->getisPause())
		return;
	SimpleAudioEngine::getInstance()->playEffect("music/4.wav");
}

void Audio::playButtonClick() {
	if (GameData::getInstance()->getisPause())
		return;
	SimpleAudioEngine::getInstance()->playEffect("wav/button_click_menu.mp3");
}

void Audio::prepare() {
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/class.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/12.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/4.wav");
	SimpleAudioEngine::getInstance()->preloadEffect(
			"wav/button_click_menu.mp3");
}

void Audio::pauseAllEffects() {
	SimpleAudioEngine::getInstance()->pauseAllEffects();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void Audio::resumeAllEffects() {
	SimpleAudioEngine::getInstance()->resumeAllEffects();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
