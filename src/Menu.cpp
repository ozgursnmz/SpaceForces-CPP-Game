/*
 * Menu.cpp
 *
 *  Created on: 20 Þub 2025
 *      Author: iaman
 */

#include <Menu.h>

Menu::Menu(gApp *root) :
		gBaseCanvas(root) {
	this->root = root;
}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

void Menu::setup() {
	//pointerornek();
	menuarkaplan.loadImage("menu_background2.png");
	playbuton[0].loadImage("play.png");
	playbuton[1].loadImage("play_ticked.png");
	playbutonw = playbuton[0].getWidth();
	playbutonh = playbuton[0].getHeight();
	playbutonx = getWidth() / 2 - playbutonw / 2;
	playbutony = getHeight() / 2 - playbutonh / 2;
	playbutondurum = 0;
	gemiSetup();
	root->setTargetFramerate(60);
	patlamaSetup();

	baslikrengi.loadFont("FreeSansBold.ttf", 60);

}

void Menu::update() {
	gemiUpdate();
}

void Menu::draw() {
	menuarkaplan.draw(0, 0);
	gColor *oldcolor;
	oldcolor->set(renderer->getColor()->r, renderer->getColor()->g,
			renderer->getColor()->b);
	renderer->setColor(0, 255, 0, 255);
	baslikrengi.drawText("Space", 750, 300);
	renderer->setColor(0, 255, 200, 255);
	baslikrengi.drawText("Forces", 950, 400);
	renderer->setColor(oldcolor);
	playbuton[playbutondurum].draw(playbutonx, playbutony);
	gemiDraw();
	patlamaDraw();

}

void Menu::keyPressed(int key) {
}

void Menu::keyReleased(int key) {
}

void Menu::charPressed(unsigned int codepoint) {
}

void Menu::mouseMoved(int x, int y) {
}

void Menu::mouseDragged(int x, int y, int button) {
}

void Menu::mouseExited() {
}

void Menu::mousePressed(int x, int y, int button) {
	playbutondurum = 1;
}

void Menu::mouseReleased(int x, int y, int button) {
	playbutonhitbox.set(playbutonx, playbutony, playbutonx + playbutonw,
			playbutony + playbutonh);
	if (playbutonhitbox.contains(x, y)) {
		playbutondurum = 0;
		gCanvas *cnv = new gCanvas(root);
		appmanager->setCurrentCanvas(cnv);
	}
}

void Menu::mouseScrolled(int x, int y) {
}

void Menu::mouseEntered() {
}

void Menu::windowResized(int w, int h) {
}

void Menu::showNotify() {
}

void Menu::hideNotify() {
}

void Menu::gemiSetup() {
	gemirandom = gRandom(4);
	gemiresmi[0].loadImage("animasyon/ship_"+gToStr(gemirandom+1)+"_1.png");
	gemiresmiw[0] = gemiresmi[0].getWidth();
	gemiresmih[0] = gemiresmi[0].getHeight();
	gemiresmix[0] = 0;
	gemiresmiy[0] = getHeight() / 2 - gemiresmih[0] / 2;
	gemiresmirotate[0] = 135.0f;
	gemiresmihizx[0] = 0;
	gemiresmihizy[0] = -20;

	gemirandom = gRandom(4);
	gemiresmi[1].loadImage("animasyon/ship_"+gToStr(gemirandom+1)+"_1.png");
	gemiresmiw[1] = gemiresmi[0].getWidth();
	gemiresmih[1] = gemiresmi[0].getHeight();
	gemiresmix[1] = getWidth() - gemiresmiw[1];
	gemiresmiy[1] = getHeight() / 2 - gemiresmih[1] / 2;
	gemiresmirotate[1] = 135.0f;
	gemiresmihizx[1] = 0;
	gemiresmihizy[1] = +20;
}

void Menu::gemiDraw() {
	gemiresmi[0].draw(gemiresmix[0], gemiresmiy[0], gemiresmiw[0], gemiresmih[0],
			gemiresmirotate[0]);
	gemiresmi[1].draw(gemiresmix[1], gemiresmiy[1], gemiresmiw[1], gemiresmih[1],
			gemiresmirotate[1]);
}

void Menu::gemiUpdate() {
	gemiresmihizx[0] = (float) (getWidth() - gemiresmiw[0])
			/ (float) (root->getFramerate() * 2);
	//gLogi("gCanvas") << "gemiresmihizx:" << gemiresmihizx;
	//if (gemiresmirotate[0] < 235.0f)
	//	gemiresmirotate[0] += (235.0f - 135.0f) / (60.0f * 2.0f);
	gemiresmirotate[0] = ComputeLookAtAngle(gemiresmix[0], gemiresmiy[0], gemiresmix[1], gemiresmiy[1], true);
	//gLogi("gCanvas") << "gemiresmirotate:" << gemiresmirotate;
	if (gemiresmix[0] < (getWidth() - gemiresmiw[0])) {
		gemiresmix[0] += gemiresmihizx[0];
		// y ekseni
		gemiresmihizy[0] += (40) / (float) (root->getFramerate() * 2);
		gemiresmiy[0] += gemiresmihizy[0];
	} else {
		// bayrak
		patlamagoster[0] = true;
		patlama[0][PATLAMA_X] = gemiresmix[0];
		patlama[0][PATLAMA_Y] = gemiresmiy[0];
		patlama[0][PATLAMA_W] = gemiresmiw[0];
		patlama[0][PATLAMA_H] = gemiresmih[0];
	}
	gemiresmihizx[1] = (float) (getWidth() - gemiresmiw[1])
			/ (float) (root->getFramerate() * 2);
	//gLogi("gCanvas") << "gemiresmihizx:" << gemiresmihizx;
	gemiresmirotate[1] = ComputeLookAtAngle(gemiresmix[1], gemiresmiy[1], gemiresmix[0], gemiresmiy[0], true);
	//gLogi("gCanvas") << "gemiresmirotate:" << gemiresmirotate;
	if (gemiresmix[1] > (0.0f)) {
		gemiresmix[1] -= gemiresmihizx[1];
		// y ekseni
		gemiresmihizy[1] -= (40) / (float) (root->getFramerate() * 2);
		gemiresmiy[1] += gemiresmihizy[1];
	} else {
		// bayrak
		patlamagoster[1] = true;
		patlama[1][PATLAMA_X] = gemiresmix[1];
		patlama[1][PATLAMA_Y] = gemiresmiy[1];
		patlama[1][PATLAMA_W] = gemiresmiw[1];
		patlama[1][PATLAMA_H] = gemiresmih[1];
	}
}

void Menu::patlamaSetup() {
	patlamagoster[0] = false;
	patlamaw = 64;
	patlamah = 64;
	patlamaframe = 0;
	for (int pat = 0; pat < 2; ++pat) {
		for (int frameno = 0; frameno < patlamamaxframe; ++frameno) {
			patlamaresmi[pat][frameno].loadImage(
					"arapatlamaanimasyon/patlama_" + gToStr(frameno + 1)
							+ ".png");
		}
		patlama[pat].push_back(0); // frame
		patlama[pat].push_back(0); // x
		patlama[pat].push_back(0); // y
		patlama[pat].push_back(0); // w
		patlama[pat].push_back(0); // h
	}

}

void Menu::patlamaDraw() {
	for (int pat = 0; pat < 2; ++pat) {
		if (patlamagoster[pat] != true)
			return;
		patlamaresmi[pat][patlama[pat][PATLAMA_FRAME]].draw(patlama[pat][PATLAMA_X],
				patlama[pat][PATLAMA_Y], patlama[pat][PATLAMA_W], patlama[pat][PATLAMA_H]);
		// frame+1
		if (patlama[pat][PATLAMA_FRAME] < patlamamaxframe - 1)
			patlama[pat][PATLAMA_FRAME] += 1;
		else {
			patlama[pat][PATLAMA_FRAME] = 0;
			patlamagoster[pat] = false;
			gemireset(pat);
		}
	}

}

void Menu::gemireset(int gemi) {
	for (int gemi = 0; gemi < 2; ++gemi) {
		gemirandom = gRandom(4);
		gemiresmi[gemi].loadImage("animasyon/ship_"+gToStr(gemirandom+1)+"_1.png");
		gemiresmiw[gemi] = gemiresmi[gemi].getWidth();
		gemiresmih[gemi] = gemiresmi[gemi].getHeight();
	}
	gemiresmiy[gemi] = getHeight() / 2 - gemiresmih[gemi] / 2;
	gemiresmirotate[gemi] = 135.0f;
	if (gemi == 0) {
		gemiresmihizy[gemi] = -20;
		gemiresmix[gemi] = 0;
	}
	else {
		gemiresmihizy[gemi] = +20;
		gemiresmix[gemi] = getWidth() - gemiresmiw[gemi];
	}
}

float Menu::ComputeLookAtAngle(float fromX, float fromY, float toX, // thanks to chatgpt
		float toY, bool outputDegrees) {
    float dx = toX - fromX;
    float dy = toY - fromY;

    float angleRad = std::atan2f(dy, dx);
    return outputDegrees ? angleRad * RAD_TO_DEG : angleRad;
}

void Menu::pointerornek() {
	int sayi = 12;
	gLogi("sayi") << "sayidegeri: " << sayi;
	gLogi("sayi") << "sayidegeriadresi: " << &sayi;
	int *sayiadresi = &sayi;
	gLogi("sayi") << "sayiadresi: " << sayiadresi;
	gLogi("sayi") << "sayiadresi&: " << &sayiadresi;
	gLogi("sayi") << "sayiadresi*: " << *sayiadresi;

}

