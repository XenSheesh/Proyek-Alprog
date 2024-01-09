#include <iostream>
#include <sl.h>
#include "menu.h"
#include <vector>
#include <random>
#include <Windows.h>
#include <string>
#include <chrono>


using namespace std;


// Assets Backsound
void backsound()
{
	int bgm = slLoadWAV("theme1.wav");
	slSoundLoop(bgm);
}

// Assets Sfx
void select()
{
	int sfx = slLoadWAV("select.wav");
	slSoundPlay(sfx);
}

void popup()
{
	int sfx = slLoadWAV("popup.wav");
	slSoundPlay(sfx);
}

void opengame()
{
	int sfx = slLoadWAV("opengame.wav");
	slSoundPlay(sfx);
}

// Assets Color
void normalcolor()
{
	slSetForeColor(1, 1, 1, 1);
}

void colorblack()
{
	slSetForeColor(0, 0, 0, 1);
}

void colorred()
{
	slSetForeColor(1, 0, 0, 1);
}

void colorgreen()
{
	slSetForeColor(0, 1, 0, 1);
}

void colorblue()
{
	slSetForeColor(0, 0, 1, 1);
}

void coloryellow()
{
	slSetForeColor(1, 1, 0, 1);
}

void colorpurple()
{
	slSetForeColor(1, 0, 1, 1);
}

void colorcyan()
{
	slSetForeColor(0, 1, 1, 1);
}

// Fungsi untuk memeriksa apakah titik (x, y) berada di dalam area persegi panjang dengan pusat (centerX, centerY) dan ukuran (width, height)
bool isPointInsideRect(int x, int y, int centerX, int centerY, int width, int height)
{
	int setengahLebar = width / 2;
	int setengahTinggi = height / 2;
	return x >= centerX - setengahLebar && x <= centerX + setengahLebar && y >= centerY - setengahTinggi && y <= centerY + setengahTinggi;
}

void drawGlitchText(int font, int fontSize, const string& text, double x, double y)
{
	// Original text
	slSetTextAlign(SL_ALIGN_LEFT);
	slSetFont(font, fontSize);
	coloryellow(); // Yellow Color
	slText(x, y, text.c_str());

	// Glitch effect 1
	slSetTextAlign(SL_ALIGN_LEFT);
	slSetFont(font, fontSize);
	coloryellow(); // Adjust color as needed
	slText(x - 2, y - 2, text.c_str());

	// Glitch effect 2
	slSetTextAlign(SL_ALIGN_LEFT);
	slSetFont(font, fontSize);
	coloryellow(); // Adjust color as needed
	slText(x + 2, y + 2, text.c_str());
}

int main()
{
	// Ukuran Windows
	slWindow(1920, 1200, "Catch The Ball", 0);
	//backsound();

	// Random
	random_device rd;

	// Background
	vector <int> imgBack(3);
	{
		imgBack[0] = slLoadTexture("background.jpg");
		imgBack[1] = slLoadTexture("ground.png");
		imgBack[2] = slLoadTexture("cloud2.png");
	}

	// Position Background
	Back bg;
	bg.posX1 = 0;
	bg.posX2 = 1920;
	bg.posY = 450;

	// Position Ground
	Ground gd;
	gd.posX = 960;
	gd.posY = 43;

	// Position Cloud
	Cloud c;
	c.posX = 1000;
	c.posY = 600;

	// Random Cloud
	vector <Cloud> clouds;
	for (int i = 0; i < 5; i++)
	{
		double x = c.posX * i / 4.0 + 100 * i;
		double y = gd.posY + 50 + static_cast<double>(rd() % 3) * 150 + 50;
		clouds.push_back({ x, y });
	}

	// Bird1 dari Kiri
	vector <int> Bird1Left;
	{
		Bird1Left.push_back(slLoadTexture("bird2_1.png"));
		Bird1Left.push_back(slLoadTexture("bird2_2.png"));
		Bird1Left.push_back(slLoadTexture("bird2_3.png"));
		Bird1Left.push_back(slLoadTexture("bird2_4.png"));
		Bird1Left.push_back(slLoadTexture("bird2_5.png"));
		Bird1Left.push_back(slLoadTexture("bird2_6.png"));
		Bird1Left.push_back(slLoadTexture("bird2_7.png"));
		Bird1Left.push_back(slLoadTexture("bird2_8.png"));
	}

	// Position Bird1
	Bird1 b1;
	b1.posX = -100;
	b1.posY = 320;

	// Random Bird1
	vector <Bird1> birds1;
	int numBird = rd() % 2 + 1;

	for (int i = 0; i < numBird; i++)
	{
		double x = b1.posX + i * 200;
		double y = b1.posY + static_cast<double>(rd() % 3);
		birds1.push_back({ x, y });
	}

	// Bird1
	int bird1Frame = 0;

	//Bird2 dari Kanan
	vector <int> Bird2Right;
	{
		Bird2Right.push_back(slLoadTexture("bird3_1.png"));
		Bird2Right.push_back(slLoadTexture("bird3_2.png"));
		Bird2Right.push_back(slLoadTexture("bird3_3.png"));
		Bird2Right.push_back(slLoadTexture("bird3_4.png"));
		Bird2Right.push_back(slLoadTexture("bird3_5.png"));
		Bird2Right.push_back(slLoadTexture("bird3_6.png"));
		Bird2Right.push_back(slLoadTexture("bird3_7.png"));
		Bird2Right.push_back(slLoadTexture("bird3_8.png"));
	}

	// Position Bird2
	Bird2 b2;
	b2.posX = 1940;
	b2.posY = 450;

	// Random Bird2
	vector <Bird2> birds2;
	int numBird2 = rd() % 2 + 1;

	for (int i = 0; i < numBird2; i++)
	{
		double x = b2.posX + i * 200;
		double y = b2.posY + static_cast<double>(rd() % 3);
		birds2.push_back({ x, y });
	}

	// Bird2
	int bird2Frame = 0;

	// All Birds
	double BirdDelay = 0.3;

	// Sun di Tengah
	vector <int> imgSun(2);
	{
		imgSun[0] = slLoadTexture("tengahansun.png");
		imgSun[1] = slLoadTexture("sampingansun.png");
	}

	// Position Sun
	Sun s;
	s.posX = 380;
	s.posY = 600;

	JariSun js;
	js.posX = 380;
	js.posY = 600;

	int duck = slLoadTexture("duck.png");

	// Position Duck
	Duck d;
	d.posX = 1930;
	d.posY = 170;

	// Jenis Font
	int font1 = slLoadFont("RoadPixel.ttf");
	int font2 = slLoadFont("Crima.ttf");
	int font3 = slLoadFont("game_over.ttf");
	int font4 = slLoadFont("pixel_lcd_7.ttf");
	int font5 = slLoadFont("PixelBook-Regular.ttf");

	// Position Font
	Font1 f1;
	f1.posX = 560;
	f1.posY = 580;

	// Teks Untuk Press
	string pressSpaceText = "Press Space To Continue";

	// Letak Coordinate
	int windowWidth = 680;
	int windowHeight = 320;

	double blinkTime = 0.0;

	double angle = 0;

	while (!slShouldClose())
	{
		// Background
		normalcolor(); // Default Color
		slSprite(imgBack[0], bg.posX1, bg.posY, 1920, 1200);
		slSprite(imgBack[0], bg.posX2, bg.posY, 1920, 1200);

		// Render Background
		bg.posX1 -= 1.5; // --Kecepatannya
		bg.posX2 -= 1.5;

		// Proses Loop Background
		if (bg.posX1 <= -1000)
		{
			bg.posX1 = bg.posX2 + 1920;
		}

		if (bg.posX2 <= -1000)
		{
			bg.posX2 = bg.posX1 + 1920;
		}

		// Ground
		// slSprite(imgBack[1], gd.posX, gd.posY, 1920, 400);

		// Memanggil Duck
		normalcolor();
		slSprite(duck, d.posX, d.posY, 288, 64);

		d.posX -= 2.0; // -- Kecepatannya

		if (d.posX <= -140)
		{
			d.posX = 1925;
		}

		// Cloud
		for (Cloud& c : clouds)
		{
			c.posX -= 2;
			if (c.posX <= -200)
			{
				c.posX = 1920;
				c.posY = gd.posY + 50 + static_cast<double>(rd() % 3) * 150 + 100;
			}
			slSprite(imgBack[2], c.posX, c.posY, 238, 83);
		}

		// Bird1 random dari arah kiri
		for (Bird1& b1 : birds1)
		{
			b1.posX += 5;
			if (b1.posX >= 1930)
			{
				b1.posX = -50;
				b1.posY = 70 + static_cast<double>(rd() % 3) * 150 + 200;
			}
			slSprite(Bird1Left[bird1Frame], b1.posX, b1.posY, 62, 50);

			// Update animation frame dengan delay
			BirdDelay -= slGetDeltaTime();
			if (BirdDelay <= 0)
			{
				bird1Frame = (bird1Frame + 1) % Bird1Left.size();
				BirdDelay = 0.25; // Delay
			}

		}

		// Bird3 random dari arah kanan
		for (Bird2& b2 : birds2)
		{
			b2.posX -= 5;
			if (b2.posX <= -100)
			{
				b2.posX = 1940;
				b2.posY = 100 + static_cast<double>(rd() % 3) * 180 + 230;
			}
			slSprite(Bird2Right[bird2Frame], b2.posX, b2.posY, 62, 50);

			// Update animation frame dengan delay
			BirdDelay -= slGetDeltaTime();
			if (BirdDelay <= 0)
			{
				bird2Frame = (bird2Frame + 1) % Bird2Right.size();
				BirdDelay = 0.2; // Delay
			}

		}

		// Memanggil Sun
		slSprite(imgSun[0], s.posX, s.posY, 134, 134);

		// Rotate Jari Sun
		slPush();
		slTranslate(js.posX, js.posY);
		slRotate(angle);
		slSprite(imgSun[1], 0, 0, 242, 242);
		slPop();

		angle++;

		// Setting Font
		slSetTextAlign(SL_ALIGN_LEFT);
		slSetFont(font1, 82);

		// Input Text "Catch The Ball"
		drawGlitchText(font1, 82, "CATCH THE BALL", f1.posX, f1.posY);

		// Hitung waktu berkedip
		blinkTime += slGetDeltaTime();

        // Tampilkan teks dan berkedip
		if (static_cast<int>(blinkTime) % 2 == 0) 
		{
			slSetTextAlign(SL_ALIGN_CENTER);
			slSetFont(font3, 54);
			colorblack();
			slText(windowWidth, windowHeight, "Press Space to Continue");
		}

        // Periksa apakah tombol spasi ditekan
        if (slGetKey(' '))
        {
			// Suara
			select();

            // Lakukan aksi yang diinginkan saat tombol spasi ditekan
            cout << "Space Pressed! Do something..." << endl;

            // Contoh: Keluar dari loop atau lakukan aksi lainnya
            //break;
        }

		// Render
		slRender();
	}

	slClose();
	return 0;

}