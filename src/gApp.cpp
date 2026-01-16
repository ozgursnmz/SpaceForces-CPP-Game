/*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#include "gApp.h"
#include "gCanvas.h"
#include "Menu.h"

gApp::gApp() {

}

gApp::gApp(int argc, char **argv) : gBaseApp(argc, argv) {

}

gApp::~gApp() {
}

void gApp::setup() {
	//gCanvas* cnv = new gCanvas(this);
	muzikSetup();
	sesSetup();
	Menu* cnv = new Menu(this);
	appmanager->setCurrentCanvas(cnv);

}

void gApp::update() {
}

void gApp::sesPlay(int sesID) {
	if (sesID < 0 || sesID >= sessayisi) return;
	sescalar[sesID].play();
}

void gApp::sescalarSetVolume(int sesID, int volume) {
	if (sesID < 0 || sesID >= sessayisi) return;
	if (volume < 0 || volume > 10) return;
	sescalar[sesID].setVolume(volume * 0.1f);
}

void gApp::sescalarSetVolume(int volume) {
	if (volume < 0 || volume > 10) return;
	for (int sesID = 0; sesID < sessayisi; ++sesID) {
		sescalar[sesID].setVolume(volume * 0.1f);
	}
}

void gApp::sescalarStop(int sesID) {
	if (sesID < 0 || sesID >= sessayisi) return;
	if (sescalar[sesID].isPlaying() == true)
		sescalar[sesID].stop();
}

void gApp::sescalarStopAll() {
	for (int sesID = 0; sesID < sessayisi; ++sesID) {
		if (sescalar[sesID].isPlaying() == true)
			sescalar[sesID].stop();
	}
}


void gApp::muzikSetup() {
		muzikcalar[0].loadSound("menu_muzigi.mp3");
}

void gApp::muzikcalarPlay() {
		if (muzikcalar[0].isPlaying() == false) muzikcalar[0].play();
	}

void gApp::muzikcalarStop() {
		if (muzikcalar[0].isPlaying() == true) muzikcalar[0].stop();
}


void gApp::sesSetup() {
	sesseviyesi = 5;
	sescalar[SES_ATES].loadSound("dusmanates.wav");
	sescalar[SES_TIKLA].loadSound("click.wav");
	sescalar[SES_PATLAMA].loadSound("patlama.mp3");
}
