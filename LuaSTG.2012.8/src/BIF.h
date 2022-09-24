#pragma once

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "hge_inc.h"

#include "random.h"

#define RES_TYPE_TEX 1
#define RES_TYPE_IMG 2
#define RES_TYPE_ANI 3
#define RES_TYPE_BGM 4
#define RES_TYPE_SND 5
#define RES_TYPE_PSI 6
#define RES_TYPE_FNT 7
#define RES_TYPE_TTF 8

class BIF
{
	public:
	//system functions
	static int SetWindowed(lua_State * L);
	static int SetFPS(lua_State * L);
	static int GetFPS(lua_State * L);
	static int SetVsync(lua_State * L);
	static int SetResolution(lua_State * L);
	static int SetSplash(lua_State * L);
	static int SetTitle(lua_State * L);
	static int SystemLog(lua_State * L);
	static int Print(lua_State * L);
	static int LoadPack(lua_State * L);
	static int UnloadPack(lua_State * L);
	static int DoFile(lua_State * L);
	static int SetResourceStatus(lua_State * L);
	static int GetnObj(lua_State * L);
	//object functions
	static int UpdateObjList(lua_State * L);
	static int ObjFrame(lua_State * L);
	static int ObjRender(lua_State * L);
	static int BoundCheck(lua_State * L);
	static int CollisionCheck(lua_State * L);
	static int UpdateXY(lua_State * L);
	static int AfterFrame(lua_State * L);
	static int New(lua_State * L);
	static int Del(lua_State * L);
	static int Kill(lua_State * L);
	static int IsValid(lua_State * L);
	static int SetV(lua_State * L);
	static int Angle(lua_State * L);
	static int Dist(lua_State * L);
	static int BoxCheck(lua_State * L);
	static int ResetPool(lua_State * L);
	static int ObjMetaIndex(lua_State * L);
	static int ObjMetaNewIndex(lua_State * L);
	static int DefaultRenderFunc(lua_State * L);
	static int NextObject(lua_State * L);
	static int ObjList(lua_State * L);
	//resource functions
	static int LoadTexture(lua_State * L);
	static int LoadImage_(lua_State * L);
	static int LoadAnimation(lua_State * L);
	static int LoadPS(lua_State * L);
	static int LoadSound(lua_State * L);
	static int LoadMusic(lua_State * L);
	static int LoadFont(lua_State * L);
	static int LoadTTF(lua_State * L);
	static int RemoveResource(lua_State * L);
	static int CheckRes(lua_State * L);
	static int EnumRes(lua_State * L);
	//graphical functions
	static int BeginScene(lua_State * L);
	static int EndScene(lua_State * L);
	static int GetTextureSize(lua_State * L);
	static int Render(lua_State * L);
	static int RenderRect(lua_State * L);
	static int Render4V(lua_State * L);
	static int RenderText(lua_State * L);
	static int RenderTexture(lua_State * L);
	static int RenderClear(lua_State * L);
	static int RenderTTF(lua_State * L);
	static int SetViewport(lua_State * L);
	static int SetOrtho(lua_State * L);
	static int SetPerspective(lua_State * L);
	static int SetImageScale(lua_State * L);
	static int SetImageState(lua_State * L);
	static int SetFontState(lua_State * L);
	static int SetFontState2(lua_State * L);
	static int SetAnimationState(lua_State * L);
	static int SetImageCenter(lua_State * L);
	static int SetAnimationCenter(lua_State * L);
	static int SetFog(lua_State * L);
	static int ParticleStop(lua_State * L);
	static int ParticleFire(lua_State * L);
	static int ParticleGetn(lua_State * L);
	static int ParticleGetEmission(lua_State * L);
	static int ParticleSetEmission(lua_State * L);
	static int SetImgState(lua_State * L);
	//snapshot function
	static int Snapshot(lua_State * L);
	//audio functions
	static int PlaySound_(lua_State * L);
	static int PlayMusic(lua_State * L);
	static int StopMusic(lua_State * L);
	static int PauseMusic(lua_State * L);
	static int ResumeMusic(lua_State * L);
	static int GetMusicState(lua_State * L);
	static int UpdateSound(lua_State * L);
	static int SetSEVolume(lua_State * L);
	static int SetBGMVolume(lua_State * L);
	//input functions
	static int GetKeyState(lua_State * L);
	static int GetLastKey(lua_State * L);
	static int GetLastChar(lua_State * L);
	//debug functions
	static int ObjTable(lua_State * L);
	static int Registry(lua_State * L);
	//register lib
	static void reg(lua_State * L);
};

#define COLOR_TYPENAME "lstgColor"

class Color
{
public:
	static DWORD * Push(lua_State *L);
	static int New(lua_State *L);
	static int Eq(lua_State *L);
	static int Add(lua_State *L);
	static int Mul(lua_State *L);
	static int ToARGB(lua_State *L);
	static int ToString(lua_State *L);
	static void reg(lua_State *L);
};

#define RANDGEN_TYPENAME "lstgRand"

class RandGen
{
public:
	static rand_gen * Push(lua_State *L);
	static int New(lua_State *L);
	static int ToString(lua_State *L);
	static int Seed(lua_State *L);
	static int Int(lua_State *L);
	static int Float(lua_State *L);
	static int Sign(lua_State * L);
	static void reg(lua_State *L);
};

bool RenderPrio(unsigned int i,unsigned int j);
bool FramePrio(unsigned int i,unsigned int j);

void print_stack(lua_State * L);

inline int TranslateBlendMode(lua_State * L,int n)
{
	if(strcmp(luaL_checkstring(L,n),"mul+add")==0) return BLEND_COLORMUL+BLEND_ALPHAADD;
	if(strcmp(luaL_checkstring(L,n),"")==0) return BLEND_COLORMUL+BLEND_ALPHABLEND;
	if(strcmp(luaL_checkstring(L,n),"mul+alpha")==0) return BLEND_COLORMUL+BLEND_ALPHABLEND;
	if(strcmp(luaL_checkstring(L,n),"add+add")==0) return BLEND_COLORADD+BLEND_ALPHAADD;
	if(strcmp(luaL_checkstring(L,n),"add+alpha")==0) return BLEND_COLORADD+BLEND_ALPHABLEND;
	luaL_error(L,"Invalid argument.");
	return BLEND_COLORMUL+BLEND_ALPHABLEND;
}