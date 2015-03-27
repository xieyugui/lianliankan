#include "SimpleAudioEngine.h"
<<<<<<< HEAD:Classes/AudioProxy.cpp
#include "AudioProxy.h"
=======
#include "GameData.h"
>>>>>>> upstream/master:Classes/Audio.cpp

USING_NS_CC;
using namespace CocosDenshion;

AudioProxy* AudioProxy::m_instance = nullptr;
AudioProxy* AudioProxy::getInstance() {
	if (m_instance == nullptr) {
		m_instance = new AudioProxy();
	}
	return m_instance;
}

<<<<<<< HEAD:Classes/AudioProxy.cpp
void AudioProxy::playBGM() {
=======
void Audio::playBGM() {
	if(GameData::getInstance()->getisPause())
		return;
>>>>>>> upstream/master:Classes/Audio.cpp
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/class.mp3", true);
}


<<<<<<< HEAD:Classes/AudioProxy.cpp
void AudioProxy::playSprite() {
	SimpleAudioEngine::getInstance()->playEffect("music/12.wav");
}

void AudioProxy::playEliminate(){
	SimpleAudioEngine::getInstance()->playEffect("music/4.wav");
}

void AudioProxy::playButtonClick() {
=======
void Audio::playSprite() {
	if(GameData::getInstance()->getisPause())
		return;
	SimpleAudioEngine::getInstance()->playEffect("music/12.wav");
}

void Audio::playEliminate(){
	if(GameData::getInstance()->getisPause())
		return;
	SimpleAudioEngine::getInstance()->playEffect("music/4.wav");
}

void Audio::playButtonClick() {
	if(GameData::getInstance()->getisPause())
		return;
>>>>>>> upstream/master:Classes/Audio.cpp
	SimpleAudioEngine::getInstance()->playEffect("wav/button_click_menu.mp3");
}


void AudioProxy::prepare(){
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/class.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/12.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/4.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("wav/button_click_menu.mp3");
}

void Audio::pauseAllEffects() {
	SimpleAudioEngine::getInstance()->pauseAllEffects();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void Audio::resumeAllEffects() {
	 SimpleAudioEngine::getInstance()->resumeAllEffects();
	 SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}