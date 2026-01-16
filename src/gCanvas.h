 /*
 * gCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GCANVAS_H_
#define GCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gFont.h"





class gCanvas : public gBaseCanvas {
public:
	gCanvas(gApp* root);
	virtual ~gCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();

private:
	gApp* root;

	//Arkaplan
	gImage arkaplan;
	void arkaplanSetup();
	void arkaplanDraw();

	//Oyuncu Platformu
	static const int yolsayisi = 2;
	static const int YOL_UST = 0, YOL_ALT = 1;
	gImage oyuncuplatform[yolsayisi];

	int oyuncuplatformx[yolsayisi], oyuncuplatformy[yolsayisi], oyuncuplatformw[yolsayisi], oyuncuplatformh[yolsayisi];
	void oyuncuplatformSetup();
	void oyuncuplatformDraw();
	static const int platformmaxframe = 24;
	gImage platformanimation[platformmaxframe];
	int platformanimationframe;

	int secilenplatform;

	gImage dusmanplatform[yolsayisi];
	int dusmanplatformx[yolsayisi], dusmanplatformy[yolsayisi], dusmanplatformw[yolsayisi], dusmanplatformh[yolsayisi];
	void dusmanplatformSetup();
	void dusmanplatformDraw();
	void platformPressed(int x, int y);

	void gemisecimiKeymap(int key);
	void parabannerGuncelleme();

	//Gemi Secimi
	static const int gemicesidi = 4;
	gImage gemisecimi[gemicesidi];
	int gemisecimix[gemicesidi], gemisecimiy[gemicesidi], gemisecimiw[gemicesidi], gemisecimih[gemicesidi];
	int panelw, panelh;
	void gemisecimiSetup();
	void gemisecimiDraw();
	int secilengemi;
	void gemisecimiPressed(int x, int y);

	//gemi secimi efekti
	static const int gemisecimiefektimaxframe = 14;
	gImage gemisecimiefekti[gemisecimiefektimaxframe];
	int gemisecimiefektix, gemisecimiefektiy;
	bool gemisecimiefekticalis;
	int gemisecimiefekticurrentframe;

	//Para
	int para;
	gImage paragosterge;
	int paragostergex, paragostergey, paragostergew, paragostergeh;
	int gemisecimibannerdurumu[4];
	gImage gemisecimibanner[2];
	int gemisecimibannerx, gemisecimibannery, gemisecimibannerw, gemisecimibannerh;
	gFont parafont;
	int gemifiyati[gemicesidi];
	static const int SARIGEMI = 0, SIYAHGEMI = 1, YILDIZGEMI = 2, TOPACGEMI = 3;
	void paraSetup();
	void paraDraw();


	//Ayar Butonu
	static const int NORMAL = 0, TIKLA = 1;
	static const int PRESSED = 0, DRAGGED = 1, RELEASED = 2;
	int ayarbutondurumu;
	gImage ayarbuton[2];
	int ayarbutonx, ayarbutony, ayarbutonw, ayarbutonh;
	void ayarbutonSetup();
	void ayarbutonDraw();
	void ayarbutonPressed(int x, int y, int eventtype);

	//Oyun Modu
	static const int OYUN_NORMAL = 0, OYUN_PAUSE = 1, OYUN_BITTI = 2;
	int oyunmodu;

	//Pause Menu
	gImage pausemenu;
	gFont pauseyazi;
	int pausemenux, pausemenuy, pausemenuw, pausemenuh;
	void pausemenuSetup();
	void pausemenuDraw();

	int geributondurum;
	gImage geributon[2];
	int geributonx, geributony, geributonw, geributonh;
	void geributonSetup();
	void geributonDraw();
	void geributtonPressed(int x, int y, int eventtype);

	//Devam Butonu
	int devambutondurumu;
	gImage devambuton[2];
	int devambutonx, devambutony, devambutonw, devambutonh;
	void devambutonSetup();
	void devambutonDraw();
	void devambutonPressed(int x, int y, int eventtype);

	//Gemi
	gImage gemiresim[gemicesidi][25];
	int gemimaxframe[gemicesidi];
	int framegecikmesi, framegecikmesimax;
	int gemimaxcan[gemicesidi];
	int gemisaldirigucu[gemicesidi];
	int gemihizlari[gemicesidi];
	int gemisaldirimenzili[gemicesidi];
	//gemi saldiri resimleri
	gImage gemiatakresmi[gemicesidi][25];
	int gemiatakmaxframe[gemicesidi];
	void gemiSetup();
	void gemiDraw();

	//Oyuncu Gemi
	static const int OGEMI_TUR = 0, OGEMI_FRAME = 1, OGEMI_GECIKME = 2, OGEMI_X = 3, OGEMI_Y = 4,
			OGEMI_W = 5, OGEMI_H = 6, OGEMI_HIZX = 7, OGEMI_HIZY = 8, OGEMI_YOL = 9, OGEMI_SM = 10,
			OGEMI_MERMITURU = 11, OGEMI_RELOAD = 12, OGEMI_RELOADSAYAC = 13, OGEMI_CAN = 14, OGEMI_ESKISM = 15,
			OGEMI_SALDIRIMENZIL = 16;
	std::vector <int> oyuncuyenigemi;
	std::vector <std::vector <int>> ogemilistesi;
	void ogemiUret(int tur);
	void ogemiUpdate();
	void ogemiDraw();
	void ogemiCanbariDraw(int ogemi);
	void ogemiNextFrame(int ogemi);
	void ogemiSaldiriKontrolu();
	gRect carpisan1, carpisan2;

	//Dusman Gemi
	static const int DGEMI_TUR = 0, DGEMI_FRAME = 1, DGEMI_GECIKME = 2, DGEMI_X = 3, DGEMI_Y = 4,
					 DGEMI_W = 5, DGEMI_H = 6, DGEMI_HIZX = 7, DGEMI_HIZY = 8, DGEMI_YOL = 9, DGEMI_SM = 10,
					 DGEMI_MERMITURU = 11, DGEMI_RELOAD = 12, DGEMI_RELOADSAYAC = 13, DGEMI_CAN = 14, DGEMI_ESKISM = 15,
					 DGEMI_SALDIRIMENZIL = 16;
	std::vector <int> dusmanyenigemi;
	std::vector <std::vector <int>> dgemilistesi;
	int dgemisayac;
	void dgemiUret();
	void dgemiUretici();
	void dgemiUpdate();
	void dgemiDraw();
	void dgemiSaldiriKontrolu();
	gRect dcarpisan1, dcarpisan2;
	void dgeminextFrame(int dgemi);

	//Menu buton
	int menubutondurum;
	gImage menubuton[2];
	int menubutonx, menubutony, menubutonw, menubutonh;
	void menubutonSetup();
	void menubutonDraw();
	void menubuttonPressed(int x, int y, int eventtype);

	//Mermi
	static const int MERMI_OATES = 0, MERMI_DATES = 1;
	static const int OMERMI_TUR = 0, OMERMI_FRAME = 1, OMERMI_X = 2, OMERMI_Y = 3, OMERMI_W = 4,
			OMERMI_H = 5, OMERMI_HIZX = 6, OMERMI_HIZY = 7, OMERMI_SALDIRIGUCU = 8;
	static const int DMERMI_TUR = 0, DMERMI_FRAME = 1, DMERMI_X = 2, DMERMI_Y = 3, DMERMI_W = 4, DMERMI_H = 5,
			DMERMI_HIZX = 6, DMERMI_HIZY = 7;
	gImage mermiresmi[2];
	void mermiSetup();
	void mermiDraw();
	std::vector<int>yeniomermi;
	std::vector<std::vector<int>>omermilistesi;
	void omermiUret(int ogemiID);
	void omermiAtes();
	void omermiUpdate();
	void omermivsdgemi();

	//dusman mermi
	std::vector<int> yenidmermi;
	std::vector<std::vector<int>> dmermilistesi;
	void dmermiUret(int dgemiId);
	void dmermiDraw();
	void dmermiAtes();
	void dmermiUpdate();
	void dmermivsogemi();

	// patlama
	static const int PATLAMA_FRAME = 0, PATLAMA_X = 1, PATLAMA_Y = 2, PATLAMA_W = 3, PATLAMA_H = 4;
	static const int patlamamaxframe = 15;
	gImage patlamaresim[patlamamaxframe];
	void patlamaSetup();
	std::vector<int> yenipatlama;
	std::vector<std::vector<int>> patlamalistesi;
	void patlamaUret(int gemiID);
	void patlamaDraw();
	void patlamaDusmanUret(int gemiID);

	// oyun sonu
	static const int WIN = 0, LOSE = 1;
	gImage oyunsonu;
	gImage sonucresmi[2];
	bool kazandin, kaybettin;
	int oyunsonux, oyunsonuy;
	void oyunsonuSetup();
	void oyunsonuDraw();
	//canbari
	static const int CANBARI_X = 0, CANBARI_Y = 1, CANBARI_WCERCEVE = 2, CANBARI_HCERCEVE = 3, CANBARI_AZALTMA = 4,
			CANBARI_WBAR = 5, CANBARI_HBAR = 6, CANBARI_STATE = 7;
	static const int MAVI = 0, SARI = 1, TURUNCU = 2, KIRMIZI = 3;
	gImage canbaricerceve;
	gImage canbariresmi[4];
	gRect canbarisrc, canbaridst;
	std::vector<float> yenicanbari;
	std::vector<std::vector<float>> ogemicanbarilistesi;
	std::vector<std::vector<float>> dgemicanbarilistesi;
	void canbariSetup();
	void canbariStateUpdate(int ogemi);
	//ses bari
	static const int KEYBOARD = 0, MOUSE = 1;
	gImage sescerceve;
	int sescercevex, sescercevey, sescercevew, sescerceveh;
	void sesbariSetup();
	void sesbariDraw();
	void sesbarKeyMap(int key);
	void sesbarPressed(int x, int y, int eventType);
	float sesbarix, sesbariy, sesbariw, sesbarih;
	float sesbariazaltmamiktari;
	int sesbarimaxw;
	int sesseviyesi;
	int mousex, mousey;
	int hangiyolda;//uretilen oyuncu gemilerini sayicak.
	//oyun sonu butonlari
	int osyenidendurumu;
	int osyenidenx, osyenideny, osyenidenw, osyenidenh;
	gRect osyenidenhitbox;
	gImage osyenidenbuton[2];
	void osyenidenSetup();
	void osyenidenDraw();
	void osyenidenPressed(int x, int y, int eventtype);
	//osmenu
	int osmenudurumu;
	int osmenux, osmenuy, osmenuw, osmenuh;
	gRect osmenuhitbox;
	gImage osmenubuton[2];
	void osmenuSetup();
	void osmenuDraw();
	void osmenuPressed(int x, int y, int eventtype);
};


#endif /* GCANVAS_H_ */
