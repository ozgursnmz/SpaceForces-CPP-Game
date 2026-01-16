/*
 * gApp.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GAPP_H_
#define GAPP_H_

#include "gBaseApp.h"
#include "gFmodSound.h"


class gApp : public gBaseApp {
public:
	gApp();
	gApp(int argc, char **argv);
	~gApp();

	void setup();
	void update();

	static const int SES_ATES = 0, SES_TIKLA = 1, SES_PATLAMA = 2;
	void sesPlay(int sesID);
	void sescalarSetVolume(int sesID, int volume);
	void sescalarSetVolume(int volume);
	void sescalarStop(int sesID);
	void sescalarStopAll();

	void muzikcalarPlay();
	void muzikcalarStop();

private:
	static const int sessayisi = 3;
	//gSound muzikcalar;
	gFmodSound sescalar[sessayisi];
	gFmodSound muzikcalar[1];
	void muzikSetup();
	void sesSetup();
	int sesseviyesi;
};

#endif /* GAPP_H_ */
