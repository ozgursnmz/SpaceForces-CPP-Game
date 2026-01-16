/*
 * Menu.h
 *
 *  Created on: 20 Þub 2025
 *      Author: iaman
 */

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include <gBaseCanvas.h>
#include "gApp.h"
#include "gImage.h"
#include "gCanvas.h"
#include "gFont.h"
#include <cmath>


class Menu: public gBaseCanvas {
public:
	Menu(gApp* root);
	virtual ~Menu();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mouseExited();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();

private:
	gApp* root;

	float RAD_TO_DEG = 180.0f / 3.14159265358979323846f;
	float ComputeLookAtAngle(float fromX, float fromY, float toX, float toY, bool outputDegrees = false);

	gImage menuarkaplan;
	gImage playbuton[2];
	int playbutonx, playbutony, playbutonw, playbutonh;
	gRect playbutonhitbox;
	int playbutondurum;

	// Gemi
	int gemirandom;
	gImage gemiresmi[2];
	float gemiresmix[2], gemiresmiy[2], gemiresmiw[2], gemiresmih[2], gemiresmirotate[2];
	float gemiresmihizx[2], gemiresmihizy[2];
	void gemiSetup();
	void gemiDraw();
	void gemiUpdate();
	static const int patlamamaxframe = 15;
	static const int PATLAMA_FRAME = 0, PATLAMA_X = 1, PATLAMA_Y = 2, PATLAMA_W = 3, PATLAMA_H = 4;
	bool patlamagoster[2];
	gImage patlamaresmi[2][patlamamaxframe];
	std::vector<int> patlama[2];
	void patlamaSetup();
	void patlamaDraw();
	int patlamaw, patlamah;
	int patlamaframe ;
	void gemireset(int gemi);

	// baslik yazisi
	gFont baslikrengi;
	void pointerornek();
};

#endif /* SRC_MENU_H_ */
