#pragma once
#pragma warning(disable:4800 4244)

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "hge_inc.h"

#include "dict.cpp"
#include "pool.cpp"
#include "helper.h"

#define LOG_FILE "log.txt"
#define SCRIPT_HEAD_LEN 256

#define FUNC_INIT 1
#define FUNC_DEL 2
#define FUNC_FRAME 3
#define FUNC_RENDER 4
#define FUNC_COLLI 5
#define FUNC_KILL 6
#define FUNC_NUM_OF_FUNC 6

#define GROUP_DEFAULT 0
#define GROUP_ALL 16
#define GROUP_NUM_OF_GROUP 16

#define STATUS_NORMAL 0
#define STATUS_DEL 1
#define STATUS_KILL 2
#define STATUS_NUM_OF_STS 3

#define DEFAULT_RES_X 640.0f
#define DEFAULT_RES_Y 480.0f

#define FPS_DEFAULT 60.0f

#define RESOURCE_GLOBAL 0
#define RESOURCE_STAGE 1
#define RESOURCE_NONE 2

#define RAD2DEGREE 180.0/3.141592653589793
#define DEGREE2RAD 1.0/(RAD2DEGREE)

struct lstgobj
{
	lua_Number x,y,r,vx,vy,omiga,layer,lastx,lasty,dx,dy,a,b,hscale,vscale;
	int status,group,timer,ani_timer,hide,bound,navi,colli,rect;
	char * img;
	lstgImage * pimage;
	lstgAnimation * panimation;
	hgeParticleSystem * pps;
	int fireps;
	unsigned int uniq_id;
	void reset()
	{
		x=y=r=vx=vy=omiga=layer=lastx=lasty=dx=dy=a=b=0.0;
		hscale=vscale=1.0;
		status=STATUS_NORMAL;
		group=GROUP_DEFAULT;
		timer=ani_timer=hide=navi=rect=0;
		colli=bound=1;
		uniq_id=0;
		img=0;
		pimage=0;
		panimation=0;
		pps=0;
		fireps=1;
	}
};

class lstg
{
public:
	lstg();
	~lstg();
	bool start(int argc, char** argv);
	void release();
	pool<lstgobj> obj;
	lua_State * L;
	HGE * hge;
	int se_volume,bgm_volume,resource_status;
	unsigned int id_counter;
	lua_Number image_scale;
	DWORD screen_freq_save;
	std::vector<unsigned int> obj_list_all;
	std::vector<unsigned int> obj_list_render;
	std::vector<unsigned int> obj_list_type[GROUP_NUM_OF_GROUP];
	dict<lstgTexture> tex[2];
	dict<lstgImage> img[2];
	dict<lstgAnimation> ani[2];
	dict<lstgSound> snd[2];
	dict<lstgBGM> bgm[2];
	dict<lstgPSI> psi[2];
	dict<hgeFont> fnt[2];
	dict<lstgTTF> ttf[2];
	void Err(const char * format,...);
	void Log(const char * format,...);
	void Ldofile(lua_State * L,const char * filename,const char * from="");
	void Lcall(lua_State * L,int nargs,int nresults,const char * from);
	void Lcall(lua_State * L,int nargs,int nresults);
};

extern lstg * _lstg;
void lstg_close();
lstg * lstg_open();

bool FrameFunc();
bool FocusGainFunc();
bool FocusLoseFunc();

bool colli_check(lstgobj * o1,lstgobj * o2);