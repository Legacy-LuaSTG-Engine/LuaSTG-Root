#pragma once

#include "hge_inc.h"

#define SOUND_MIX 20.0

class lstgTexture
{
public:
	HTEXTURE tex;
	lstgTexture(const char * filename,int mipmap);
	~lstgTexture();
};

class lstgImage:public hgeSprite
{
public:
	lstgImage(lstgTexture * ptex,float x,float y,float w,float h,float a,float b,bool rect=false):hgeSprite(ptex->tex,x,y,w,h)
	{_a=a;_b=b;_rect=rect;SetHotSpot(w*0.5f,h*0.5f);}
	float _a,_b;
	bool _rect;
	void Render4V(float x0,float y0,float z0,
				float x1,float y1,float z1,
				float x2,float y2,float z2,
				float x3,float y3,float z3);
};

class lstgAnimation
{
public:
	hgeQuad quad;
	lstgAnimation(lstgTexture * ptex,float x,float y,float w,float h,int n,int m,int intv,float a,float b,bool rect=false);
	void RenderEx(int n, float x, float y, float rot, float hscale=1.0f, float vscale=0.0f);
	float _a,_b,width,height,tx,ty,tw,th,hotX,hotY;
	int _n,_m,_intv;
	bool _rect;
};

class lstgPSI
{
public:
	hgeParticleSystemInfo * psi;
	hgeSprite * spr;
	float _a,_b;
	bool _rect;
	lstgPSI(const char * filename,lstgImage * pimg,float a,float b, bool rect);
	~lstgPSI();
};

class lstgSound
{
private:
        double v,p;
        HEFFECT se;
        HCHANNEL ch;
public:
        lstgSound(const char * filename);
        ~lstgSound();
        void play(double volume,double pan);
        void update();
        friend class BIF;
};

class lstgBGM
{
private:
        HEFFECT se;
		//HSTREAM st;
        double _end;
        double _loop;
        HCHANNEL ch;
		bool paused;
public:
        lstgBGM(const char * filename,double end,double loop);
        ~lstgBGM();
        void play(float volume=1.0f,float pos=0.0f);
        void stop();
        void pause();
        void resume();
        void update();
        friend class BIF;
};
class lstgTTF
{
public:
	HTTF font;
	lstgTTF(const char * fontname, LONG width, LONG height, LONG weight, LONG deco, LONG charset);
	~lstgTTF();
};