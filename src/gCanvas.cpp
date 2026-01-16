/*
 * gCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#include "gCanvas.h"
#include "Menu.h"

gCanvas::gCanvas(gApp *root) :
		gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
}

void gCanvas::setup() {
	hangiyolda = 0;
	parafont.loadFont("FreeSansBold.ttf", 20);
	arkaplanSetup();
	oyuncuplatformSetup();
	dusmanplatformSetup();
	gemisecimiSetup();
	devambutonSetup();
	ayarbutonSetup();
	pausemenuSetup();
	devambutonSetup();
	geributonSetup();
	menubutonSetup();
	gemiSetup();
	mermiSetup();
	patlamaSetup();
	oyunsonuSetup();
	canbariSetup();
	sesbariSetup();
	paraSetup();
	osyenidenSetup();
	osmenuSetup();
	oyunmodu = OYUN_NORMAL;
	root->sescalarSetVolume(1);
	//root->muzikcalarPlay();
}

void gCanvas::update() {
	if (oyunmodu != OYUN_NORMAL) {
		return;
	}
	ogemiUpdate();
	dgemiUretici();
	dgemiUpdate();
	ogemiSaldiriKontrolu();
	dgemiSaldiriKontrolu();
	omermiAtes();
	omermiUpdate();
	omermivsdgemi();
	dmermiAtes();
	dmermiUpdate();
	dmermivsogemi();

}

void gCanvas::draw() {
	arkaplanDraw();
	oyuncuplatformDraw();
	dusmanplatformDraw();
	gemisecimiDraw();
	ayarbutonDraw();
	devambutonDraw();
	gemiDraw();
	mermiDraw();
	patlamaDraw();
	pausemenuDraw();
	geributonDraw();
	menubutonDraw();
	paraDraw();
	oyunsonuDraw();
	osyenidenDraw();
	osmenuDraw();

}

void gCanvas::sesbarKeyMap(int key) {
	if (key == G_KEY_A && sesseviyesi > 0) {
		sesseviyesi -= 1;
		sesbariw -= sesbariazaltmamiktari;
	}
	if (key == G_KEY_D && sesseviyesi < 10) {
		sesseviyesi += 1;
		sesbariw += sesbariazaltmamiktari;
	}
}

void gCanvas::keyPressed(int key) {
	//gLogi("gCanvas") << "keyPressed:" << key;
	sesbarKeyMap(key);
	gemisecimiKeymap(key);
	if (key == G_KEY_ESC || key == G_KEY_P) {
		if (oyunmodu == OYUN_NORMAL) {
			oyunmodu = OYUN_PAUSE;
		} else if (oyunmodu == OYUN_PAUSE) {
			oyunmodu = OYUN_NORMAL;
		}
	}
}

void gCanvas::keyReleased(int key) {
	//gLogi("gCanvas") << "keyReleased:" << key;

}

void gCanvas::charPressed(unsigned int codepoint) {
//	gLogi("gCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void gCanvas::mouseMoved(int x, int y) {
//	gLogi("gCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
	if (oyunmodu == OYUN_NORMAL) {
		ayarbutonPressed(x, y, DRAGGED);
	}
	if (oyunmodu == OYUN_PAUSE) {
		geributtonPressed(x, y, DRAGGED);
		devambutonPressed(x, y, DRAGGED);
		menubuttonPressed(x, y, DRAGGED);
	}
	if (oyunmodu == OYUN_BITTI){
		osyenidenPressed(x, y, DRAGGED);
		osmenuPressed(x, y, DRAGGED);
	}

}

void gCanvas::mousePressed(int x, int y, int button) {
	mousex = x;
	mousey = y;
//	gLogi("gCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	ayarbutonPressed(x, y, PRESSED);
	if (oyunmodu == OYUN_BITTI){
		osyenidenPressed(x, y, PRESSED);
		osmenuPressed(x, y, PRESSED);
	}
	if (oyunmodu == OYUN_NORMAL) {
		platformPressed(x, y);
		gemisecimiPressed(x, y);
	}
	if (oyunmodu == OYUN_PAUSE) {
		devambutonPressed(x, y, PRESSED);
		geributtonPressed(x, y, PRESSED);
		menubuttonPressed(x, y, PRESSED);
		sesbarPressed(x, y, PRESSED);
	}
}

void gCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseReleased" << ", button:" << button;
	ayarbutonPressed(x, y, RELEASED);
	if (oyunmodu == OYUN_NORMAL) {

	}
	if (oyunmodu == OYUN_PAUSE) {
		devambutonPressed(x, y, RELEASED);
		geributtonPressed(x, y, RELEASED);
		menubuttonPressed(x, y, RELEASED);
	}
	if (oyunmodu == OYUN_BITTI){
		osyenidenPressed(x, y, RELEASED);
		osmenuPressed(x, y, RELEASED);
	}
}

void gCanvas::mouseScrolled(int x, int y) {
	//gLogi("gCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseEntered() {

}

void gCanvas::mouseExited() {

}

void gCanvas::windowResized(int w, int h) {

}

void gCanvas::showNotify() {

}

void gCanvas::hideNotify() {

}

void gCanvas::arkaplanSetup() {
	arkaplan.loadImage("map.png");
}

void gCanvas::arkaplanDraw() {
	arkaplan.draw(0, 0);
}

void gCanvas::oyuncuplatformSetup() {
	platformanimationframe = 0;
	secilenplatform = YOL_UST;

	for (int sira = 0; sira < yolsayisi; ++sira) {
		oyuncuplatform[sira].loadImage("silahli_gemi1.png");
		oyuncuplatformw[sira] = oyuncuplatform[sira].getWidth();
		oyuncuplatformh[sira] = oyuncuplatform[sira].getHeight();
	}
	oyuncuplatformx[YOL_UST] = 250;
	oyuncuplatformy[YOL_UST] = 150;
	oyuncuplatformx[YOL_ALT] = 250;
	oyuncuplatformy[YOL_ALT] = 150 + 510;
	//Platform Animasyonu
	for (int frame = 0; frame < platformmaxframe; ++frame) {
		platformanimation[frame].loadImage(
				"animasyon/platform_" + gToStr(frame + 1) + ".png");
	}
}

void gCanvas::oyuncuplatformDraw() {
	for (int sira = 0; sira < yolsayisi; ++sira) {
		oyuncuplatform[sira].draw(oyuncuplatformx[sira], oyuncuplatformy[sira]);
	}

	//Animasyon
	platformanimation[platformanimationframe].draw(
			oyuncuplatformx[secilenplatform], oyuncuplatformy[secilenplatform]);

	//frame+1
	if (platformanimationframe < platformmaxframe - 1
			&& oyunmodu == OYUN_NORMAL)
		platformanimationframe += 1;
}

void gCanvas::dusmanplatformSetup() {
	for (int sira = 0; sira < yolsayisi; ++sira) {
		dusmanplatform[sira].loadImage("silahli_dusmangemi1.png");
		dusmanplatformw[sira] = dusmanplatform[sira].getWidth();
		dusmanplatformh[sira] = dusmanplatform[sira].getHeight();
	}
	dusmanplatformx[YOL_UST] = 1490;
	dusmanplatformy[YOL_UST] = 140;
	dusmanplatformx[YOL_ALT] = 1490;
	dusmanplatformy[YOL_ALT] = 140 + 510;
}

void gCanvas::dusmanplatformDraw() {
	for (int sira = 0; sira < yolsayisi; ++sira) {
		dusmanplatform[sira].draw(dusmanplatformx[sira], dusmanplatformy[sira]);
	}
}

void gCanvas::gemisecimiSetup() {
	for (int sira = 0; sira < gemicesidi; sira++) {
		gemisecimi[sira].loadImage(
				"animasyon/ship_" + gToStr(sira + 1) + "_1.png");

	}
	//gemi secimi efekti
	gemisecimiefekticurrentframe = 0;
	gemisecimiefekticalis = false;
	for (int frame = 0; frame < gemisecimiefektimaxframe; ++frame) {
		gemisecimiefekti[frame].loadImage("suruklebirak/surukle_birak_1_"+gToStr(frame)+".png");
	}
	gemisecimiefektix = 0;
	gemisecimiefektiy = 0;

	gemisecimibannerdurumu[SARIGEMI] = 1;
	gemisecimibannerdurumu[SIYAHGEMI] = 1;
	gemisecimibannerdurumu[YILDIZGEMI] = 1;
	gemisecimibannerdurumu[TOPACGEMI] = 1;

	//Panel Boyutlari
	panelw = 200;
	panelh = 265;

	//Birinci Gemi
	gemisecimiw[0] = gemisecimi[0].getWidth();
	gemisecimih[0] = gemisecimi[0].getHeight();
	gemisecimix[0] = 75 + (panelw - gemisecimiw[0]) / 2;
	gemisecimiy[0] = 10 + (panelh - gemisecimih[0]) / 2;

	//Ikinci Gemi
	gemisecimiw[1] = gemisecimi[1].getWidth();
	gemisecimih[1] = gemisecimi[1].getHeight();
	gemisecimix[1] = 75 + (panelw - gemisecimiw[1]) / 2;
	gemisecimiy[1] = 275 + (panelh - gemisecimih[1]) / 2;

	//Ucuncu Gemi
	gemisecimiw[2] = gemisecimi[2].getWidth();
	gemisecimih[2] = gemisecimi[2].getHeight();
	gemisecimix[2] = 75 + (panelw - gemisecimiw[2]) / 2;
	gemisecimiy[2] = 275 + panelh + (panelh - gemisecimih[2]) / 2;

	//Dorduncu Gemi
	gemisecimiw[3] = gemisecimi[3].getWidth();
	gemisecimih[3] = gemisecimi[3].getHeight();
	gemisecimix[3] = 75 + (panelw - gemisecimiw[3]) / 2;
	gemisecimiy[3] = 275 + panelh * 2 + (panelh - gemisecimih[3]) / 2;

	//Banner
	gemisecimibanner[0].loadImage("para_kapali.png");
	gemisecimibanner[1].loadImage("para_acik.png");
	gemisecimibannerw = gemisecimibanner[0].getWidth();
	gemisecimibannerh = gemisecimibanner[0].getHeight();
	gemisecimibannerx = gemisecimix[0] + panelw - gemisecimibannerw / 3;
	gemisecimibannery = gemisecimiy[0];
}

void gCanvas::gemisecimiDraw() {
	for (int sira = 0; sira < gemicesidi; ++sira) {
		gemisecimi[sira].draw(gemisecimix[sira], gemisecimiy[sira]);
		gemisecimibanner[gemisecimibannerdurumu[sira]].draw(gemisecimibannerx,
				gemisecimibannery + 265 * sira, gemisecimibannerw / 2,
				gemisecimibannerh / 2);
		parafont.drawText("" + gToStr(gemifiyati[sira]), gemisecimibannerx,
				gemisecimibannery
						+ parafont.getStringHeight(
								"" + gToStr(gemifiyati[sira])) * 1.5f
						+ 265 * sira);
	}
	if (gemisecimiefekticalis != true) return;
	//gemi secimi efekti
	//draw
	gemisecimiefekti[gemisecimiefekticurrentframe].draw(gemisecimiefektix, gemisecimiefektiy);
	//frame+1
	if (gemisecimiefekticurrentframe < gemisecimiefektimaxframe-1) {
		gemisecimiefekticurrentframe +=1;
	} else {
		gemisecimiefekticurrentframe = 0;
		gemisecimiefekticalis = false;
	}
}

void gCanvas::platformPressed(int x, int y) {
	if (x > oyuncuplatformx[0] && x < oyuncuplatformx[0] + oyuncuplatformw[0]
			&& y > oyuncuplatformy[0]
			&& y < oyuncuplatformy[0] + oyuncuplatformh[0]) {
		platformanimationframe = 0;
		secilenplatform = YOL_UST;
	}
	if (x > oyuncuplatformx[1] && x < oyuncuplatformx[1] + oyuncuplatformw[1]
			&& y > oyuncuplatformy[1]
			&& y < oyuncuplatformy[1] + oyuncuplatformh[1]) {
		platformanimationframe = 0;
		secilenplatform = YOL_ALT;
	}
}

void gCanvas::gemisecimiPressed(int x, int y) {
	for (int sira = 0; sira < gemicesidi; sira++) {
		if (x > gemisecimix[sira] && x < gemisecimix[sira] + gemisecimiw[sira]
				&& y > gemisecimiy[sira]
				&& y < gemisecimiy[sira] + gemisecimih[sira]) {
			secilengemi = sira;

			ogemiUret(secilengemi);



		}
	}
}

void gCanvas::ayarbutonSetup() {
	ayarbuton[NORMAL].loadImage("ayarlar_buton.png");
	ayarbuton[TIKLA].loadImage("ayarlar_butonu_tiklandi.png");
	ayarbutondurumu = NORMAL;
	ayarbutonw = ayarbuton[ayarbutondurumu].getWidth();
	ayarbutonh = ayarbuton[ayarbutondurumu].getHeight();
	ayarbutonx = getWidth() - ayarbutonw;
	ayarbutony = 0;
}

void gCanvas::ayarbutonDraw() {
	ayarbuton[ayarbutondurumu].draw(ayarbutonx, ayarbutony);
}

void gCanvas::ayarbutonPressed(int x, int y, int eventtype) {
	if (x > ayarbutonx && x < ayarbutonx + ayarbutonw && y > ayarbutony
			&& y < ayarbutony + ayarbutonh) {
		if (eventtype == PRESSED) {
			ayarbutondurumu = TIKLA;
			root->sesPlay(root->SES_TIKLA);
		}

		if (eventtype == DRAGGED) {
			ayarbutondurumu = TIKLA;
		}

		if (eventtype == RELEASED) {
			ayarbutondurumu = NORMAL;
			root->sesPlay(root->SES_TIKLA);
			if (oyunmodu == OYUN_NORMAL)
				oyunmodu = OYUN_PAUSE;
			else if (oyunmodu == OYUN_PAUSE)
				oyunmodu = OYUN_NORMAL;
		}
	} else {
		ayarbutondurumu = NORMAL;
	}
}

void gCanvas::pausemenuSetup() {
	pausemenu.loadImage("pause/pause_ekran.png");
	pausemenuw = pausemenu.getWidth();
	pausemenuh = pausemenu.getHeight();
	pausemenux = (getWidth() - pausemenuw) / 2;
	pausemenuy = (getHeight() - pausemenuh);
}

void gCanvas::pausemenuDraw() {
	if (oyunmodu != OYUN_PAUSE)
		return;
	pausemenu.draw(pausemenux, pausemenuy);
	devambutonDraw();
	sesbariDraw();
}
void gCanvas::devambutonSetup() {
	devambuton[NORMAL].loadImage("pause/oyna.png");
	devambuton[TIKLA].loadImage("pause/oyna_tiklandi.png");
	devambutondurumu = NORMAL;
	devambutonw = devambuton[devambutondurumu].getWidth() / 2;
	devambutonh = devambuton[devambutondurumu].getHeight() / 2;
	devambutonx = pausemenux + pausemenuw / 2 - devambutonw / 2;
	devambutony = pausemenuy + pausemenuh - devambutonh * 1.5f;
}

void gCanvas::devambutonDraw() {
	if (oyunmodu != OYUN_PAUSE) {
		return;
	}
	devambuton[devambutondurumu].draw(devambutonx, devambutony, devambutonw,
			devambutonh);
}

void gCanvas::devambutonPressed(int x, int y, int eventtype) {
	if (x > devambutonx && x < devambutonx + devambutonw && y > devambutony
			&& y < devambutony + devambutonh) {
		if (eventtype == PRESSED) {
			devambutondurumu = TIKLA;
			root->sesPlay(root->SES_TIKLA);
		}

		if (eventtype == DRAGGED) {
			devambutondurumu = TIKLA;
		}

		if (eventtype == RELEASED) {
			devambutondurumu = NORMAL;
			oyunmodu = OYUN_NORMAL;
		}
	} else {
		devambutondurumu = NORMAL;
		root->sesPlay(root->SES_TIKLA);
	}
}

void gCanvas::gemiSetup() {

	framegecikmesi = 0;
	framegecikmesimax = 0;
	dgemisayac = 0;

	//Geminin baslangic degerlerini belirt
	gemimaxframe[SARIGEMI] = 25;
	gemimaxframe[SIYAHGEMI] = 16;
	gemimaxframe[YILDIZGEMI] = 25;
	gemimaxframe[TOPACGEMI] = 25;

	gemiatakmaxframe[SARIGEMI] = 11;
	gemiatakmaxframe[SIYAHGEMI] = 8;
	gemiatakmaxframe[YILDIZGEMI] = 11;
	gemiatakmaxframe[TOPACGEMI] = 25;

	gemifiyati[SARIGEMI] = 15;
	gemifiyati[SIYAHGEMI] = 20;
	gemifiyati[YILDIZGEMI] = 30;
	gemifiyati[TOPACGEMI] = 40;

	gemimaxcan[SARIGEMI] = 10;
	gemimaxcan[SIYAHGEMI] = 6;
	gemimaxcan[YILDIZGEMI] = 15;
	gemimaxcan[TOPACGEMI] = 30;

	gemisaldirigucu[SARIGEMI] = 2;
	gemisaldirigucu[SIYAHGEMI] = 4;
	gemisaldirigucu[YILDIZGEMI] = 5;
	gemisaldirigucu[TOPACGEMI] = 10;

	gemihizlari[SARIGEMI] = 5;
	gemihizlari[SIYAHGEMI] = 10;
	gemihizlari[YILDIZGEMI] = 7;
	gemihizlari[TOPACGEMI] = 3;

	gemisaldirimenzili[SARIGEMI] = 800;
	gemisaldirimenzili[SIYAHGEMI] = 1000;
	gemisaldirimenzili[YILDIZGEMI] = 600;
	gemisaldirimenzili[TOPACGEMI] = 500;

	//Gemi resimlerini yukle
	for (int gemino = 0; gemino < gemicesidi; ++gemino) {
		//gLogi("gemino") << gemino;
		for (int frame = 0; frame < gemimaxframe[gemino]; ++frame) {
			gemiresim[gemino][frame].loadImage(
					"animasyon/ship_" + gToStr(gemino + 1) + "_"
							+ gToStr(frame + 1) + ".png");
			//gLogi("frame") << frame;
		}
	}

	//gemi atak resimleri yukle
	for (int gemino = 0; gemino < gemicesidi; ++gemino) {
		for (int frameno = 0; frameno < gemiatakmaxframe[gemino]; ++frameno) {
			gemiatakresmi[gemino][frameno].loadImage(
					"animasyon/ship_" + gToStr(gemino + 1) + "_shot_"
							+ gToStr(frameno + 1) + ".png");
		}
	}
}

void gCanvas::gemiDraw() {
	//gemiresim[2][14].draw(oyuncuplatformx[secilenplatform],oyuncuplatformy[secilenplatform]);
	ogemiDraw();
	dgemiDraw();
}

void gCanvas::ogemiUret(int tur) {
	if (para >= gemifiyati[tur]) para -= gemifiyati[tur];
	else return;
	parabannerGuncelleme();
	gemisecimiefektix = gemisecimix[tur];
	gemisecimiefektiy = gemisecimiy[tur];
	gemisecimiefekticalis = true;
	//Gemi parametreleri yazilacak
	//int tur = gRandom(gemicesidi);
	oyuncuyenigemi.push_back(tur); //Geminin turu, index = 0
	oyuncuyenigemi.push_back(0); //Frame, index = 1
	oyuncuyenigemi.push_back(0); //Gecikme, index = 2
	oyuncuyenigemi.push_back(
			oyuncuplatformx[secilenplatform]
					+ (-gemiresim[tur][0].getWidth()
							+ oyuncuplatformw[secilenplatform]) / 2); //Geminin x, index = 3
	oyuncuyenigemi.push_back(
			oyuncuplatformy[secilenplatform]
					+ (-gemiresim[tur][0].getHeight()
							+ oyuncuplatformh[secilenplatform]) / 2); //Geminin y, index = 4
	oyuncuyenigemi.push_back(gemiresim[tur][0].getWidth()); //Geminin w, index = 5
	oyuncuyenigemi.push_back(gemiresim[tur][0].getHeight()); //Geminin h, index = 6
	oyuncuyenigemi.push_back(gemihizlari[tur]); //Hiz x, index = 7
	oyuncuyenigemi.push_back(0); //Hiz y, index = 8
	oyuncuyenigemi.push_back(secilenplatform); //Yol, index = 9
	oyuncuyenigemi.push_back(0); //Saldiri modu, index = 10
	oyuncuyenigemi.push_back(0); //Mermi turu, index = 11
	oyuncuyenigemi.push_back(60); //Reload suresi, index = 12
	oyuncuyenigemi.push_back(60); //Reload Sayac, index = 13
	oyuncuyenigemi.push_back(gemimaxcan[tur]); //gemican index = 14
	oyuncuyenigemi.push_back(0); //Eski Saldiri modu, index = 15
	oyuncuyenigemi.push_back(gemisaldirimenzili[tur]); //saldiri menzili, index = 16

	//Olusturulan gemi listeye gonderilecek
	ogemilistesi.push_back(oyuncuyenigemi);
	//gemicanbari //bayrak
	yenicanbari.push_back(
			oyuncuplatformx[secilenplatform]
					+ (-gemiresim[tur][0].getWidth()
							+ oyuncuplatformw[secilenplatform]) / 2); //x
	yenicanbari.push_back(
			(oyuncuplatformy[secilenplatform]
					+ (-gemiresim[tur][0].getHeight()
							+ oyuncuplatformh[secilenplatform]) / 2)
					+ gemiresim[tur][0].getHeight() * 1.2f); //y
	yenicanbari.push_back(gemiresim[tur][0].getWidth()); //w cerceve
	yenicanbari.push_back(canbariresmi[MAVI].getHeight()); //h cerceve
	yenicanbari.push_back((gemiresim[tur][0].getWidth() / gemimaxcan[tur])); //azaltmamiktari
	yenicanbari.push_back(gemiresim[tur][0].getWidth()); //w canbar
	yenicanbari.push_back(canbariresmi[MAVI].getHeight()); //h canbar
	yenicanbari.push_back(0); //state => mavi

	ogemicanbarilistesi.push_back(yenicanbari);
	yenicanbari.clear();

	//Yeni gemi icin oyuncugemi temizlenecek
	oyuncuyenigemi.clear();

}

void gCanvas::ogemiUpdate() {
	for (int ogemi = 0; ogemi < ogemilistesi.size(); ogemi++) {
		if (oyunmodu != OYUN_NORMAL)
			continue;
		if (ogemilistesi[ogemi][OGEMI_SM] == 1)
			continue;
		if (ogemilistesi[ogemi][OGEMI_X] + ogemilistesi[ogemi][OGEMI_W] / 2
				< dusmanplatformx[ogemilistesi[ogemi][OGEMI_YOL]]
						+ dusmanplatformw[ogemilistesi[ogemi][OGEMI_YOL]] / 2) {
			ogemilistesi[ogemi][OGEMI_X] += ogemilistesi[ogemi][OGEMI_HIZX];
			ogemicanbarilistesi[ogemi][CANBARI_X] +=
					ogemilistesi[ogemi][OGEMI_HIZX];
		} else if (oyunmodu == OYUN_NORMAL) {
			oyunmodu = OYUN_BITTI;
			kazandin = true;
		}
	}
}

void gCanvas::ogemiDraw() {
	for (int ogemi = 0; ogemi < ogemilistesi.size(); ++ogemi) {
		//hangi yolda daha çok gemi var hesabi
		//Hesaplamadan once reset islemi
		if(ogemi == 0) hangiyolda = 0;
		//Hesapla
		if(ogemilistesi[ogemi][OGEMI_YOL] == YOL_UST) hangiyolda += 1;
		else if(ogemilistesi[ogemi][OGEMI_YOL] == YOL_ALT) hangiyolda -= 1;
		if (ogemilistesi[ogemi][OGEMI_SM] == 0) {
			//gemiyi ciz
			gemiresim[ogemilistesi[ogemi][OGEMI_TUR]][ogemilistesi[ogemi][OGEMI_FRAME]].draw(
					ogemilistesi[ogemi][OGEMI_X], ogemilistesi[ogemi][OGEMI_Y],
					ogemilistesi[ogemi][OGEMI_W], ogemilistesi[ogemi][OGEMI_H],
					180.0f);
		} else if (ogemilistesi[ogemi][OGEMI_SM] == 1) {
			gemiatakresmi[ogemilistesi[ogemi][OGEMI_TUR]][ogemilistesi[ogemi][OGEMI_FRAME]].draw(
					ogemilistesi[ogemi][OGEMI_X], ogemilistesi[ogemi][OGEMI_Y],
					ogemilistesi[ogemi][OGEMI_W], ogemilistesi[ogemi][OGEMI_H],
					180.0f);
		}
		ogemiCanbariDraw(ogemi);
		//oyun modu kontrolu
		if (oyunmodu != OYUN_NORMAL)
			continue;
		ogemiNextFrame(ogemi);
	}
}

void gCanvas::dgemiUret() {
	//Gemi parametreleri yazilacak
	//1 Bir yoldan digerinden fazla gemi varsa o yoldan uretsin.
	int tur = 0;
	int yol = 0;
	if(hangiyolda !=0){
	if(hangiyolda > 0)yol = YOL_UST; else if(hangiyolda < 0)yol = YOL_ALT;
	for (int ogemi = 0; ogemi < ogemilistesi.size(); ++ogemi) {
		if(ogemilistesi[ogemi][OGEMI_X] > getWidth() / 2){
			yol = ogemilistesi[ogemi][OGEMI_YOL];
			break;
		}
	}
	}else{
		 tur = gRandom(gemicesidi);
		 yol = gRandom(2);
	}
	//Bir gemi yani oyuncu gemisi dusman plartformuna yakin ise o geminin bulundugu yola oncelik verilsin.
	tur = gRandom(gemicesidi);

	dusmanyenigemi.push_back(tur); //Geminin turu, index = 0
	dusmanyenigemi.push_back(0); //Frame, index = 1
	dusmanyenigemi.push_back(0); //Gecikme, index = 2
	dusmanyenigemi.push_back(
			dusmanplatformx[yol]
					+ (-gemiresim[tur][0].getWidth() + dusmanplatformw[yol])
							/ 2); //Geminin x, index = 3
	dusmanyenigemi.push_back(
			dusmanplatformy[yol]
					+ (-gemiresim[tur][0].getHeight() + dusmanplatformh[yol])
							/ 2); //Geminin y, index = 4
	dusmanyenigemi.push_back(gemiresim[tur][0].getWidth()); //Geminin w, index = 5
	dusmanyenigemi.push_back(gemiresim[tur][0].getHeight()); //Geminin h, index = 6
	dusmanyenigemi.push_back(-gemihizlari[tur]); //Hiz x, index = 7
	dusmanyenigemi.push_back(0); //Hiz y, index = 8
	dusmanyenigemi.push_back(yol); //Yol, index = 9
	dusmanyenigemi.push_back(0); //Saldiri modu, index = 10
	dusmanyenigemi.push_back(1); //mermi turu, index = 11
	dusmanyenigemi.push_back(60); //reload suresi , index = 12
	dusmanyenigemi.push_back(60); //reload sayaci , index = 13
	dusmanyenigemi.push_back(gemimaxcan[tur]); //can , index = 14
	dusmanyenigemi.push_back(0); //eski saldiri modu ,index = 15
	dusmanyenigemi.push_back(gemisaldirimenzili[tur]); //salidir menzil, index = 16

	//Olusturulan gemi listeye gonderilecek
	dgemilistesi.push_back(dusmanyenigemi);

	//gemicanbari //bayrak
	yenicanbari.push_back(
			dusmanplatformx[yol]
					+ (-gemiresim[tur][0].getWidth() + dusmanplatformw[yol])
							/ 2); //x
	yenicanbari.push_back(
			(dusmanplatformy[yol]
					+ (-gemiresim[tur][0].getHeight() + dusmanplatformh[yol])
							/ 2) + gemiresim[tur][0].getHeight() * 1.2f); //y
	yenicanbari.push_back(gemiresim[tur][0].getWidth()); //w cerceve
	yenicanbari.push_back(canbariresmi[MAVI].getHeight()); //h cerceve
	yenicanbari.push_back((gemiresim[tur][0].getWidth() / gemimaxcan[tur])); //azaltmamiktari
	yenicanbari.push_back(gemiresim[tur][0].getWidth()); //w canbar
	yenicanbari.push_back(canbariresmi[MAVI].getHeight()); //h canbar
	yenicanbari.push_back(0); //state => mavi
	//dusman canbari listeye
	dgemicanbarilistesi.push_back(yenicanbari);

	//Yeni gemi icin dusmangemi temizlenecek
	dusmanyenigemi.clear();
	yenicanbari.clear();

}

void gCanvas::dgemiUpdate() {
	for (int dgemi = 0; dgemi < dgemilistesi.size(); ++dgemi) {
		if (oyunmodu != OYUN_NORMAL)
			continue;
		if (dgemilistesi[dgemi][DGEMI_SM] == 1)
			continue;
		if (dgemilistesi[dgemi][DGEMI_X]
				> oyuncuplatformx[dgemilistesi[dgemi][DGEMI_YOL]]) {
			dgemilistesi[dgemi][DGEMI_X] += dgemilistesi[dgemi][DGEMI_HIZX];
			dgemicanbarilistesi[dgemi][CANBARI_X] +=
					dgemilistesi[dgemi][DGEMI_HIZX];
		} else if (oyunmodu == OYUN_NORMAL) {
			oyunmodu = OYUN_BITTI;
			kaybettin = true;
		}
	}
}

void gCanvas::dgemiUretici() {
	if (dgemisayac < 30) {
		dgemisayac++;
	} else {
		dgemisayac = 0;
		dgemiUret();
	}
}

void gCanvas::geributonSetup() {
	geributondurum = NORMAL;
	geributon[NORMAL].loadImage("bitti/bitti_yeniden.png");
	geributon[TIKLA].loadImage("bitti/bitti_yeniden_tiklandi.png");
	geributonw = geributon[NORMAL].getWidth() / 2;
	geributonh = geributon[NORMAL].getHeight() / 2;
	geributonx = pausemenux + pausemenuw / 2 + geributonw / 2;
	geributony = devambutony;
}

void gCanvas::geributonDraw() {
	if (oyunmodu != OYUN_PAUSE)
		return;
	geributon[geributondurum].draw(geributonx, geributony, geributonw,
			geributonh);
}

void gCanvas::geributtonPressed(int x, int y, int eventtype) {
	if (x > geributonx && x < geributonx + geributonw && y > geributony
			&& y < geributony + geributonh) {
		if (eventtype == PRESSED) {
			geributondurum = TIKLA;
			root->sesPlay(root->SES_TIKLA);
		}
		if (eventtype == DRAGGED) {
			geributondurum = TIKLA;
		}
		if (eventtype == RELEASED) {
			geributondurum = NORMAL;
			//root->muzikcalarStop();
			gCanvas *cnv = new gCanvas(root);
			appmanager->setCurrentCanvas(cnv);
		}
	}
}

void gCanvas::ogemiSaldiriKontrolu() {
	for (int ogemi = 0; ogemi < ogemilistesi.size(); ++ogemi) {
		ogemilistesi[ogemi][OGEMI_SM] = 0; //SM degeri resetledi
		carpisan1.set(ogemilistesi[ogemi][OGEMI_X],
				ogemilistesi[ogemi][OGEMI_Y],
				ogemilistesi[ogemi][OGEMI_X] + ogemilistesi[ogemi][OGEMI_W],
				ogemilistesi[ogemi][OGEMI_Y] + ogemilistesi[ogemi][OGEMI_H]);
		for (int dgemi = 0; dgemi < dgemilistesi.size(); ++dgemi) {
			carpisan2.set(dgemilistesi[dgemi][DGEMI_X],
					dgemilistesi[dgemi][DGEMI_Y],
					dgemilistesi[dgemi][DGEMI_X] + dgemilistesi[dgemi][DGEMI_W],
					dgemilistesi[dgemi][DGEMI_Y]
							+ dgemilistesi[dgemi][DGEMI_H]);
			//Mesafe kontrolu
			//gLogi(gToStr( ogemilistesi[ogemi][OGEMI_SALDIRIMENZIL]));
			if (carpisan2.centerX() -carpisan1.centerX()
					< ogemilistesi[ogemi][OGEMI_SALDIRIMENZIL]
					&& ogemilistesi[ogemi][OGEMI_YOL]
							== dgemilistesi[dgemi][DGEMI_YOL]) {
				ogemilistesi[ogemi][OGEMI_SM] = 1;
				if (ogemilistesi[ogemi][OGEMI_SM]
						!= ogemilistesi[ogemi][OGEMI_ESKISM]) {
					ogemilistesi[ogemi][OGEMI_FRAME] = 0;
					ogemilistesi[ogemi][OGEMI_ESKISM] =
							ogemilistesi[ogemi][OGEMI_SM];
				}
				dgemi = dgemilistesi.size();
			}
		}
	}
}

void gCanvas::dgemiDraw() {
	//Butun gemileri ciz
	for (int dgemi = 0; dgemi < dgemilistesi.size(); ++dgemi) {

		if (dgemilistesi[dgemi][DGEMI_SM] == 0) {
			gemiresim[dgemilistesi[dgemi][DGEMI_TUR]][dgemilistesi[dgemi][DGEMI_FRAME]].draw(
					dgemilistesi[dgemi][DGEMI_X], dgemilistesi[dgemi][DGEMI_Y]);
		} else if (dgemilistesi[dgemi][DGEMI_SM] == 1) {
			gemiatakresmi[dgemilistesi[dgemi][DGEMI_TUR]][dgemilistesi[dgemi][DGEMI_FRAME]].draw(
					dgemilistesi[dgemi][DGEMI_X], dgemilistesi[dgemi][DGEMI_Y]);
		}

		//gemi can bari
		//geminin canini ciz //bayrak3
		//bar
		canbarisrc.set(0, 0, dgemicanbarilistesi[dgemi][CANBARI_WBAR],
				dgemicanbarilistesi[dgemi][CANBARI_HBAR]);
		canbaridst.set(dgemicanbarilistesi[dgemi][CANBARI_X],
				dgemicanbarilistesi[dgemi][CANBARI_Y],
				dgemicanbarilistesi[dgemi][CANBARI_X]
						+ dgemicanbarilistesi[dgemi][CANBARI_WBAR],
				dgemicanbarilistesi[dgemi][CANBARI_Y]
						+ dgemicanbarilistesi[dgemi][CANBARI_HBAR]);
		canbariresmi[(int) dgemicanbarilistesi[dgemi][CANBARI_STATE]].drawSub(
				canbarisrc, canbaridst, 0.0f);		//bayrak
		//cerceve
		canbaricerceve.draw(dgemicanbarilistesi[dgemi][CANBARI_X],
				dgemicanbarilistesi[dgemi][CANBARI_Y],
				dgemicanbarilistesi[dgemi][CANBARI_WCERCEVE],
				dgemicanbarilistesi[dgemi][CANBARI_HCERCEVE]);

		//frame+1 islemi icin gecikme suresi
		if (oyunmodu != OYUN_NORMAL)
			continue;
		dgeminextFrame(dgemi);

	}
}

void gCanvas::menubutonSetup() {
	menubutondurum = NORMAL;
	menubuton[NORMAL].loadImage("pause/menu.png");
	menubuton[TIKLA].loadImage("pause/menu_tiklandi.png");
	menubutonw = menubuton[NORMAL].getWidth() / 2;
	menubutonh = menubuton[NORMAL].getHeight() / 2;
	menubutonx = pausemenux + pausemenuw / 2 - menubutonw * 2;
	menubutony = devambutony;
}

void gCanvas::menubutonDraw() {
	if (oyunmodu != OYUN_PAUSE)
		return;
	menubuton[menubutondurum].draw(menubutonx, menubutony, menubutonw,
			menubutonh);
}

void gCanvas::menubuttonPressed(int x, int y, int eventtype) {
	if (x > menubutonx && x < menubutonw + menubutonx && y > menubutony
			&& y < menubutony + menubutonh) {
		if (eventtype == PRESSED) {
			menubutondurum = TIKLA;
			root->sesPlay(root->SES_TIKLA);
		}
		if (eventtype == DRAGGED) {
			menubutondurum = TIKLA;
		}
		if (eventtype == RELEASED) {
			menubutondurum = NORMAL;
			root->sesPlay(root->SES_TIKLA);
			Menu *cnv = new Menu(root);
			appmanager->setCurrentCanvas(cnv);
		}
	}
}

void gCanvas::dgemiSaldiriKontrolu() {
	//Dusman gemilerini secen dongu
	for (int dgemi = 0; dgemi < dgemilistesi.size(); ++dgemi) {
		dgemilistesi[dgemi][DGEMI_SM] = 0;
		dcarpisan1.set(dgemilistesi[dgemi][DGEMI_X],
				dgemilistesi[dgemi][DGEMI_Y],
				dgemilistesi[dgemi][DGEMI_X] + dgemilistesi[dgemi][DGEMI_W],
				dgemilistesi[dgemi][DGEMI_Y] + dgemilistesi[dgemi][DGEMI_H]);
		for (int ogemi = 0; ogemi < ogemilistesi.size(); ++ogemi) {
			dcarpisan2.set(ogemilistesi[ogemi][OGEMI_X],
					ogemilistesi[ogemi][OGEMI_Y],
					ogemilistesi[ogemi][OGEMI_X] + ogemilistesi[ogemi][OGEMI_W],
					ogemilistesi[ogemi][OGEMI_Y]
							+ ogemilistesi[ogemi][OGEMI_H]);
			//Mesafe kontrolu
			if ( dcarpisan1.centerX() - dcarpisan2.centerX()
					< dgemilistesi[dgemi][DGEMI_SALDIRIMENZIL]
					&& dgemilistesi[dgemi][DGEMI_YOL]
							== ogemilistesi[ogemi][OGEMI_YOL]) {
				dgemilistesi[dgemi][DGEMI_SM] = 1;
				if (dgemilistesi[dgemi][DGEMI_SM]
						!= dgemilistesi[dgemi][DGEMI_ESKISM]) {
					dgemilistesi[dgemi][DGEMI_FRAME] = 0;
					dgemilistesi[dgemi][DGEMI_ESKISM] =
							dgemilistesi[dgemi][DGEMI_SM];
				}
				ogemi = ogemilistesi.size();
			}
		}
	}
}

void gCanvas::mermiSetup() {
	mermiresmi[MERMI_OATES].loadImage("kirmizi_ates.png");
	mermiresmi[MERMI_DATES].loadImage("mavi_ates.png");

}

void gCanvas::mermiDraw() {
	for (int omermi = 0; omermi < omermilistesi.size(); ++omermi) {
		mermiresmi[omermilistesi[omermi][OMERMI_TUR]].draw(
				omermilistesi[omermi][OMERMI_X],
				omermilistesi[omermi][OMERMI_Y]);
	}
	dmermiDraw();
}

void gCanvas::omermiUret(int ogemiID) {
	yeniomermi.push_back(ogemilistesi[ogemiID][OGEMI_MERMITURU]); //Mermi turu, 0
	yeniomermi.push_back(0); //Frame, 1
	yeniomermi.push_back(
			ogemilistesi[ogemiID][OGEMI_X]
					+ (ogemilistesi[ogemiID][OGEMI_W]
							- mermiresmi[ogemilistesi[ogemiID][OGEMI_MERMITURU]].getWidth())
							/ 2); //x, 2
	yeniomermi.push_back(
			ogemilistesi[ogemiID][OGEMI_Y]
					+ (ogemilistesi[ogemiID][OGEMI_H]
							- mermiresmi[ogemilistesi[ogemiID][OGEMI_MERMITURU]].getHeight())
							/ 2); //y, 3
	yeniomermi.push_back(
			mermiresmi[ogemilistesi[ogemiID][OGEMI_MERMITURU]].getWidth()); //w, 4
	yeniomermi.push_back(
			mermiresmi[ogemilistesi[ogemiID][OGEMI_MERMITURU]].getHeight()); //h, 5
	yeniomermi.push_back(+10); //Hizx, 6
	yeniomermi.push_back(0); //Hizy, 7
	yeniomermi.push_back(gemisaldirigucu[ogemilistesi[ogemiID][OGEMI_TUR]]); //saldiri gucu 8

	omermilistesi.push_back(yeniomermi);
	yeniomermi.clear();
	root->sesPlay(root->SES_ATES);
}

void gCanvas::omermiAtes() {
	for (int ogemi = 0; ogemi < ogemilistesi.size(); ++ogemi) {
		if (ogemilistesi[ogemi][OGEMI_RELOADSAYAC]
				< ogemilistesi[ogemi][OGEMI_RELOAD]) {
			ogemilistesi[ogemi][OGEMI_RELOADSAYAC]++;
		} else if (ogemilistesi[ogemi][OGEMI_SM] == 1) {
			ogemilistesi[ogemi][OGEMI_RELOADSAYAC] = 0;
			omermiUret(ogemi);
		}
	}
}

void gCanvas::omermiUpdate() {
	for (int omermi = 0; omermi < omermilistesi.size(); ++omermi) {
		if (omermilistesi[omermi][OMERMI_X] + omermilistesi[omermi][OMERMI_W]
				< getWidth()) {
			omermilistesi[omermi][OMERMI_X] +=
					omermilistesi[omermi][OMERMI_HIZX];
		} else {
			omermilistesi.erase(omermilistesi.begin() + omermi);
			break;
		}
	}
}

void gCanvas::omermivsdgemi() {
	for (int omermi = 0; omermi < omermilistesi.size(); ++omermi) {
		// secilen merminin hitboxi
		carpisan1.set(omermilistesi[omermi][OMERMI_X] + 48,
				omermilistesi[omermi][OMERMI_Y] + 48,
				omermilistesi[omermi][OMERMI_X]
						+ omermilistesi[omermi][OMERMI_W] - 48,
				omermilistesi[omermi][OMERMI_Y]
						+ omermilistesi[omermi][OMERMI_H] - 48);
		for (int dgemi = 0; dgemi < dgemilistesi.size(); ++dgemi) {
			carpisan2.set(dgemilistesi[dgemi][DGEMI_X] + 48,
					dgemilistesi[dgemi][DGEMI_Y] + 48,
					dgemilistesi[dgemi][DGEMI_X] + dgemilistesi[dgemi][DGEMI_W]
							- 48,
					dgemilistesi[dgemi][DGEMI_Y] + dgemilistesi[dgemi][DGEMI_H]
							- 48);

			// karsilastirma
			if (carpisan1.intersects(carpisan2)) {
				omermilistesi.erase(omermilistesi.begin() + omermi);
				dgemilistesi[dgemi][DGEMI_CAN] -=
						omermilistesi[omermi][OMERMI_SALDIRIGUCU];
				dgemicanbarilistesi[dgemi][CANBARI_WBAR] -=
						dgemicanbarilistesi[dgemi][CANBARI_AZALTMA]
								* omermilistesi[omermi][OMERMI_SALDIRIGUCU];
				if (dgemilistesi[dgemi][DGEMI_CAN] <= 0) {
					patlamaDusmanUret(dgemi);
					dgemicanbarilistesi.erase(
							dgemicanbarilistesi.begin() + dgemi); //can bari silindi.
					para += gemifiyati[dgemilistesi[dgemi][DGEMI_TUR]];
					dgemilistesi.erase(dgemilistesi.begin() + dgemi); //dgemi silindi.
					root->sesPlay(root->SES_PATLAMA);
				}
				break;
			}
		}
	}
}

void gCanvas::dmermiUret(int dgemiId) {

	yenidmermi.push_back(dgemilistesi[dgemiId][DGEMI_MERMITURU]); //Mermi turu, 0
	yenidmermi.push_back(0); //frame(0), 1
	yenidmermi.push_back(
			dgemilistesi[dgemiId][DGEMI_X]
					+ (dgemilistesi[dgemiId][DGEMI_W]
							- mermiresmi[dgemilistesi[dgemiId][DGEMI_MERMITURU]].getWidth())
							/ 2); //x
	yenidmermi.push_back(
			dgemilistesi[dgemiId][DGEMI_Y]
					+ (dgemilistesi[dgemiId][DGEMI_H]
							- mermiresmi[dgemilistesi[dgemiId][DGEMI_MERMITURU]].getHeight())
							/ 2); //y
	yenidmermi.push_back(dgemilistesi[dgemiId][DGEMI_W]); //w
	yenidmermi.push_back(dgemilistesi[dgemiId][DGEMI_H]); //h
	yenidmermi.push_back(-10); //yatay hiz
	yenidmermi.push_back(0); //dikey hiz
	dmermilistesi.push_back(yenidmermi);
	yenidmermi.clear();
	root->sesPlay(root->SES_ATES);

}

void gCanvas::dmermiDraw() {
	for (int dmermi = 0; dmermi < dmermilistesi.size(); ++dmermi) {
		mermiresmi[1].draw(dmermilistesi[dmermi][2], dmermilistesi[dmermi][3]);
	}
}

void gCanvas::dmermiAtes() {
	for (int dgemi = 0; dgemi < dgemilistesi.size(); ++dgemi) {
		if (dgemilistesi[dgemi][DGEMI_RELOADSAYAC]
				< dgemilistesi[dgemi][DGEMI_RELOAD]) {
			dgemilistesi[dgemi][DGEMI_RELOADSAYAC] += 1;

		} else if (dgemilistesi[dgemi][DGEMI_SM] == 1) {
			dgemilistesi[dgemi][DGEMI_RELOADSAYAC] = 0;
			dmermiUret(dgemi);
		}
	}
}

void gCanvas::dmermiUpdate() {
	for (int dmermi = dmermilistesi.size() - 1; dmermi > -1; --dmermi) {
		if (dmermilistesi[dmermi][DMERMI_X] + dmermilistesi[dmermi][DMERMI_W]
				> 0) {
			dmermilistesi[dmermi][DMERMI_X] +=
					dmermilistesi[dmermi][DMERMI_HIZX];
		} else {
			dmermilistesi.erase(dmermilistesi.begin() + dmermi);

		}
	}
}

void gCanvas::dmermivsogemi() {
	//1 dusman mermilerini teker teker sec
	for (int dmermi = 0; dmermi < dmermilistesi.size(); ++dmermi) {
		//2 secilen mermi hitbox olustur
		carpisan1.set(dmermilistesi[dmermi][DMERMI_X] + 48,
				dmermilistesi[dmermi][DMERMI_Y] + 48,
				dmermilistesi[dmermi][DMERMI_X]
						+ dmermilistesi[dmermi][DMERMI_W] - 48,
				dmermilistesi[dmermi][DMERMI_Y]
						+ dmermilistesi[dmermi][DMERMI_H] - 48);
		//3 oyuncu gemilerini sec mermi hedefi
		for (int ogemi = 0; ogemi < ogemilistesi.size(); ++ogemi) {
			//4 gemilerin hitboxini olustur.
			carpisan2.set(ogemilistesi[ogemi][OGEMI_X] + 48,
					ogemilistesi[ogemi][OGEMI_Y] + 48,
					ogemilistesi[ogemi][OGEMI_X] + ogemilistesi[ogemi][OGEMI_W]
							- 48,
					ogemilistesi[ogemi][OGEMI_Y] + ogemilistesi[ogemi][OGEMI_H]
							- 48);
			//5 merminin alani oyuncu geminin alanina carpiyor mu
			if (carpisan1.intersects(carpisan2)) {
				//6 eger carpiyorsa hem mermi hem oyuncu gemisi yok et(booms)
				ogemilistesi[ogemi][OGEMI_CAN] -= 1; //geminin cani indi
				ogemicanbarilistesi[ogemi][CANBARI_WBAR] -=
						ogemicanbarilistesi[ogemi][CANBARI_AZALTMA];
				canbariStateUpdate(ogemi);
				if (ogemilistesi[ogemi][OGEMI_CAN] <= 0) {
					patlamaUret(ogemi); //bayrak2
					ogemicanbarilistesi.erase(
							ogemicanbarilistesi.begin() + ogemi); //canbari silindi
					ogemilistesi.erase(ogemilistesi.begin() + ogemi); //gemi silindi
					root->sesPlay(root->SES_PATLAMA);
					break;
				} else {
					dmermilistesi.erase(dmermilistesi.begin() + dmermi);
					break;
				}
			}
		}
	}
}

void gCanvas::patlamaSetup() {
	for (int frame = 0; frame < patlamamaxframe; ++frame) {
		patlamaresim[frame].loadImage(
				"arapatlamaanimasyon/patlama_" + gToStr(frame + 1) + ".png");
	}
}

void gCanvas::patlamaUret(int gemiID) {
	yenipatlama.push_back(0);	//frame 0
	yenipatlama.push_back(ogemilistesi[gemiID][OGEMI_X]);	//x 1
	yenipatlama.push_back(ogemilistesi[gemiID][OGEMI_Y]);	//y 2
	yenipatlama.push_back(ogemilistesi[gemiID][OGEMI_W]);	//w 3
	yenipatlama.push_back(ogemilistesi[gemiID][OGEMI_H]);	//h 4
	patlamalistesi.push_back(yenipatlama);

	yenipatlama.clear();
}

void gCanvas::patlamaDusmanUret(int gemiID) {
	yenipatlama.push_back(0);	//frame 0
	yenipatlama.push_back(dgemilistesi[gemiID][DGEMI_X]);	//x 1
	yenipatlama.push_back(dgemilistesi[gemiID][DGEMI_Y]);	//y 2
	yenipatlama.push_back(dgemilistesi[gemiID][DGEMI_W]);	//w 3
	yenipatlama.push_back(dgemilistesi[gemiID][DGEMI_H]);	//h 4
	patlamalistesi.push_back(yenipatlama);

	yenipatlama.clear();
}

void gCanvas::patlamaDraw() {
	for (int patlamaID = 0; patlamaID < patlamalistesi.size(); ++patlamaID) {
		patlamaresim[patlamalistesi[patlamaID][PATLAMA_FRAME]].draw(
				patlamalistesi[patlamaID][PATLAMA_X],
				patlamalistesi[patlamaID][PATLAMA_Y],
				patlamalistesi[patlamaID][PATLAMA_W],
				patlamalistesi[patlamaID][PATLAMA_H]);
		// frame+1
		if (patlamalistesi[patlamaID][PATLAMA_FRAME] < patlamamaxframe - 1)
			patlamalistesi[patlamaID][PATLAMA_FRAME] += 1;
		else {
			patlamalistesi.erase(patlamalistesi.begin() + patlamaID);
			patlamaID--;
		}
	}
}

void gCanvas::oyunsonuSetup() {
	kazandin = false;
	kaybettin = false;
	//ARKAPLAN
	oyunsonu.loadImage("bitti/kaybettiniz_arka.png");
	oyunsonux = 0;
	oyunsonuy = 0;
	//sonuc yazisi
	sonucresmi[WIN].loadImage("bitti/you_win.png");
	sonucresmi[LOSE].loadImage("bitti/you_lose.png");

}

void gCanvas::oyunsonuDraw() {
	if (oyunmodu != OYUN_BITTI)
		return;
	oyunsonu.draw(oyunsonux, oyunsonuy);
	if (kazandin)
		sonucresmi[WIN].draw(getWidth() / 2 - sonucresmi[WIN].getWidth() / 2,
				getHeight() / 3);
	if (kaybettin)
		sonucresmi[LOSE].draw(getWidth() / 2 - sonucresmi[LOSE].getWidth() / 2,
				getHeight() / 3);
}

void gCanvas::canbariSetup() {
	canbaricerceve.loadImage("arkaplan_hp_03.png");
	canbariresmi[MAVI].loadImage("platform_hp_02.png");
	canbariresmi[SARI].loadImage("platform_sari.png");
	canbariresmi[TURUNCU].loadImage("platform_turuncu.png");
	canbariresmi[KIRMIZI].loadImage("platform_kirmizi.png");
	//bayrak
}

void gCanvas::canbariStateUpdate(int ogemi) {
	float canyuzdesi;
	canyuzdesi = (ogemilistesi[ogemi][OGEMI_CAN]
			/ (gemimaxcan[ogemilistesi[ogemi][OGEMI_TUR]] * 1.0f));
	if (canyuzdesi > 0.8f && canyuzdesi <= 1.0f)
		ogemicanbarilistesi[ogemi][CANBARI_STATE] = MAVI;
	else if (canyuzdesi > 0.5f && canyuzdesi <= 0.8f)
		ogemicanbarilistesi[ogemi][CANBARI_STATE] = SARI;
	else if (canyuzdesi > 0.25f && canyuzdesi <= 0.5f)
		ogemicanbarilistesi[ogemi][CANBARI_STATE] = TURUNCU;
	else if (canyuzdesi > 0.0f && canyuzdesi <= 0.25f)
		ogemicanbarilistesi[ogemi][CANBARI_STATE] = KIRMIZI;
}

void gCanvas::sesbarPressed(int x, int y, int eventType) {
	//hitboxlar tanýmladik
	gRect sesbarleftside;
	gRect sesbarrightside;
	//hitbox alanlari belirleniyor
	sesbarleftside.set(sesbarix, sesbariy, sesbarix + sesbarimaxw / 2,
			sesbariy + sesbarih);
	sesbarrightside.set(sesbarix + (sesbarimaxw / 2), sesbariy,
			sesbarix + sesbarimaxw, sesbariy + sesbarih);
	//hit kontrol
	if (sesbarleftside.contains(x, y)) {
		//ses azaltma
		if (sesseviyesi > 0) {
			sesseviyesi--;
			sesbariw -= sesbariazaltmamiktari;
		}
	}
	if (sesbarrightside.contains(x, y)) {
		//ses artirma
		if (sesseviyesi < 10) {
			sesseviyesi++;
			sesbariw += sesbariazaltmamiktari;
		}
	}
}

void gCanvas::sesbariSetup() {
	pauseyazi.loadFont("FreeSansBold.ttf", 30);
	sesseviyesi = 5;
	sescerceve.loadImage("surebar.png");
	sescercevew = sescerceve.getWidth();
	sescerceveh = sescerceve.getHeight();
	sescercevex = getWidth() / 2 - sescercevew / 2;
	sescercevey = pausemenuy + sescerceveh * 6;
	sesbariw = sescercevew - 45;
	sesbarih = sescerceveh - 40;
	sesbarix = sescercevex + 20;
	sesbariy = sescercevey + 20;
	sesbarimaxw = sesbariw;
	sesbariazaltmamiktari = sesbarimaxw / 10;
	//ses seviyesine gore ses bari guncellenecek
	sesbariw = sesbarimaxw * (sesseviyesi * 0.1f);
}

void gCanvas::sesbariDraw() {
	pauseyazi.drawText("" + gToStr(sesseviyesi), sescercevex + sescercevew / 2, sescercevey + sescerceveh + pauseyazi.getStringHeight("" + gToStr(sesseviyesi)));
	pauseyazi.drawText("ses seviyesi", sescercevex, sescercevey);
	gDrawRectangle(sesbarix, sesbariy, sesbariw, sesbarih, true);
	sescerceve.draw(sescercevex, sescercevey);
}

void gCanvas::paraSetup() {
	paragosterge.loadImage("coin_icon.png");
	paragostergew = paragosterge.getWidth();
	paragostergeh = paragosterge.getHeight();
	paragostergex = 300;
	paragostergey = 10;
	para = 300;
}

void gCanvas::paraDraw() {
	paragosterge.draw(paragostergex, paragostergey);
	parafont.drawText(gToStr(para), paragostergex + 100, paragostergey + 35);
}

void gCanvas::ogemiCanbariDraw(int ogemi) {
	//geminin canini ciz //bayrak3
	//bar
	canbarisrc.set(0, 0, ogemicanbarilistesi[ogemi][CANBARI_WBAR],
			ogemicanbarilistesi[ogemi][CANBARI_HBAR]);
	canbaridst.set(ogemicanbarilistesi[ogemi][CANBARI_X],
			ogemicanbarilistesi[ogemi][CANBARI_Y],
			ogemicanbarilistesi[ogemi][CANBARI_X]
					+ ogemicanbarilistesi[ogemi][CANBARI_WBAR],
			ogemicanbarilistesi[ogemi][CANBARI_Y]
					+ ogemicanbarilistesi[ogemi][CANBARI_HBAR]);
	canbariresmi[(int) ogemicanbarilistesi[ogemi][CANBARI_STATE]].drawSub(
			canbarisrc, canbaridst, 0.0f);	//bayrak
	//cerceve
	canbaricerceve.draw(ogemicanbarilistesi[ogemi][CANBARI_X],
			ogemicanbarilistesi[ogemi][CANBARI_Y],
			ogemicanbarilistesi[ogemi][CANBARI_WCERCEVE],
			ogemicanbarilistesi[ogemi][CANBARI_HCERCEVE]);
}

void gCanvas::ogemiNextFrame(int ogemi) {
	int maxframe = 0;
	//Saldýrý moduna gore maxframe degerleri belirleniyor
	if (ogemilistesi[ogemi][OGEMI_SM] == 0) {
		framegecikmesimax = 60 / gemimaxframe[ogemilistesi[ogemi][OGEMI_TUR]];
		maxframe = gemimaxframe[ogemilistesi[ogemi][OGEMI_TUR]] - 1;
	} else if (ogemilistesi[ogemi][OGEMI_SM] == 1) {
		framegecikmesimax = 60
				/ gemiatakmaxframe[ogemilistesi[ogemi][OGEMI_TUR]];
		maxframe = gemiatakmaxframe[ogemilistesi[ogemi][OGEMI_TUR]] - 1;
	}
	//yeterince gecikme oldumu frameler arasi
	if (ogemilistesi[ogemi][OGEMI_GECIKME] < framegecikmesimax) {
		ogemilistesi[ogemi][OGEMI_GECIKME]++;
	} else {
		ogemilistesi[ogemi][OGEMI_GECIKME] = 0;
		//frame+1
		if (ogemilistesi[ogemi][OGEMI_FRAME] < maxframe) {
			ogemilistesi[ogemi][OGEMI_FRAME] += 1;
		} else {
			ogemilistesi[ogemi][OGEMI_FRAME] = 0;
			//if(ogemilistesi[ogemi][OGEMI_SM] == 1)omermiUret(ogemi);
		}
	}
}

void gCanvas::dgeminextFrame(int dgemi) {
	int maxframe = 0;

	if (dgemilistesi[dgemi][DGEMI_SM] == 0) {
		framegecikmesimax = 60 / gemimaxframe[dgemilistesi[dgemi][DGEMI_TUR]];
		maxframe = gemimaxframe[dgemilistesi[dgemi][DGEMI_TUR]] - 1;
	} else if (dgemilistesi[dgemi][DGEMI_SM] == 1) {
		framegecikmesimax = 60
				/ gemiatakmaxframe[dgemilistesi[dgemi][DGEMI_TUR]];
		maxframe = gemiatakmaxframe[dgemilistesi[dgemi][DGEMI_TUR]] - 1;
	}

	if (dgemilistesi[dgemi][DGEMI_GECIKME] < framegecikmesimax) {
		dgemilistesi[dgemi][DGEMI_GECIKME]++;
	} else {
		dgemilistesi[dgemi][DGEMI_GECIKME] = 0;
		//frame+1
		if (dgemilistesi[dgemi][DGEMI_FRAME] < maxframe) {
			dgemilistesi[dgemi][DGEMI_FRAME]++;
		} else {
			dgemilistesi[dgemi][DGEMI_FRAME] = 0;
		}
	}
}

void gCanvas::gemisecimiKeymap(int key) {
	if (key == G_KEY_W && secilenplatform > 0)
		secilenplatform -= 1;
	if (key == G_KEY_S && secilenplatform < yolsayisi)
		secilenplatform += 1;
	if (key == G_KEY_1) ogemiUret(0);
	if (key == G_KEY_2) ogemiUret(1);
	if (key == G_KEY_3) ogemiUret(2);
	if (key == G_KEY_4) ogemiUret(3);
}

void gCanvas::parabannerGuncelleme() {
	//banner guncelleme
	if (para < gemifiyati[0])
		gemisecimibannerdurumu[0] = 0;
	else
		gemisecimibannerdurumu[1];
	if (para < gemifiyati[1])
		gemisecimibannerdurumu[1] = 0;
	else
		gemisecimibannerdurumu[1];
	if (para < gemifiyati[2])
		gemisecimibannerdurumu[2] = 0;
	else
		gemisecimibannerdurumu[1];
	if (para < gemifiyati[3])
		gemisecimibannerdurumu[3] = 0;
	else
		gemisecimibannerdurumu[1];
}

void gCanvas::osyenidenSetup() {
	osyenidendurumu = NORMAL;
	osyenidenbuton[NORMAL].loadImage("bitti/bitti_yeniden.png");
	osyenidenbuton[TIKLA].loadImage("bitti/bitti_yeniden_tiklandi.png");
	osyenidenw = osyenidenbuton[osyenidendurumu].getWidth();
	osyenidenh = osyenidenbuton[osyenidendurumu].getHeight();
	osyenidenx = getWidth() / 2 - osyenidenw / 2;
	osyenideny = getHeight() * 0.70f;
	osyenidenhitbox.set(osyenidenx, osyenideny, osyenidenx + osyenidenw, osyenideny + osyenidenh);
}

void gCanvas::osyenidenDraw() {
	if(oyunmodu != OYUN_BITTI)return;
	osyenidenbuton[osyenidendurumu].draw(osyenidenx, osyenideny);
}

void gCanvas::osyenidenPressed(int x, int y, int eventtype) {
	if(osyenidenhitbox.contains(x,y)){
		if(eventtype == PRESSED) {
			osyenidendurumu = TIKLA;
		}
		if(eventtype == DRAGGED) {
			osyenidendurumu = TIKLA;
		}
		if(eventtype == RELEASED) {
			osyenidendurumu = NORMAL;
			gCanvas* cnv = new gCanvas(root);
			appmanager->setCurrentCanvas(cnv);
		}
	}else osyenidendurumu = NORMAL;

}
void gCanvas::osmenuSetup() {
	osmenudurumu = NORMAL;
	osmenubuton[NORMAL].loadImage("bitti/bitti_geri.png");
	osmenubuton[TIKLA].loadImage("bitti/bitti_geri_tiklandi.png");
	osmenuw = osmenubuton[osmenudurumu].getWidth();
	osmenuh = osmenubuton[osmenudurumu].getHeight();
	osmenux = getWidth() / 2 - osmenuw * 2;
	osmenuy = getHeight() * 0.70f;
	osmenuhitbox.set(osmenux, osmenuy, osmenux + osmenuw, osmenuy + osmenuh);
}
void gCanvas::osmenuDraw() {
	if(oyunmodu != OYUN_BITTI)return;
	osmenubuton[osmenudurumu].draw(osmenux, osmenuy);
}
void gCanvas::osmenuPressed(int x, int y, int eventtype) {
	if(osmenuhitbox.contains(x,y)){
		if(eventtype == PRESSED) {
			osmenudurumu = TIKLA;
		}
		if(eventtype == DRAGGED) {
			osmenudurumu = TIKLA;
		}
		if(eventtype == RELEASED) {
			osmenudurumu = NORMAL;
			Menu* cnv = new Menu(root);
			appmanager->setCurrentCanvas(cnv);
		}
	}else osmenudurumu = NORMAL;

}








