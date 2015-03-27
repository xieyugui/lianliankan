#include "SimpleAudioEngine.h"
#include "AudioProxy.h"

USING_NS_CC;
using namespace CocosDenshion;

AudioProxy* AudioProxy::m_instance = nullptr;
AudioProxy* AudioProxy::getInstance() {
	if (m_instance == nullptr) {
		m_instance = new AudioProxy();
	}
	return m_instance;
}

void AudioProxy::playBGM() {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/class.mp3", true);
}


void AudioProxy::playSprite() {
	SimpleAudioEngine::getInstance()->playEffect("music/12.wav");
}

void AudioProxy::playEliminate(){
	SimpleAudioEngine::getInstance()->playEffect("music/4.wav");
}

void AudioProxy::playButtonClick() {
	SimpleAudioEngine::getInstance()->playEffect("wav/button_click_menu.mp3");
}


void AudioProxy::prepare(){
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/class.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/12.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music/4.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("wav/button_click_menu.mp3");
}