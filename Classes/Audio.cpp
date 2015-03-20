#include "Audio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance() {
	if (m_instance == nullptr) {
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM() {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/class.mp3", true);
}


void Audio::playSprite() {
	SimpleAudioEngine::getInstance()->playEffect("music/12.wav");
}

void Audio::playEliminate(){
	SimpleAudioEngine::getInstance()->playEffect("music/4.wav");
}

void Audio::playButtonClick() {
	SimpleAudioEngine::getInstance()->playEffect("wav/button_click_menu.mp3");
}


void Audio::prepare(){
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/class.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/12.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/4.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("wav/button_click_menu.mp3");
}