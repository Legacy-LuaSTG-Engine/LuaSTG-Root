#include <float.h>
#include <windows.h>

#include "lstg.h"
#include "BIF.h"

lstg * _lstg=0;

lstg::lstg()
{
	se_volume=bgm_volume=100;
	id_counter=0;
	resource_status=RESOURCE_GLOBAL;
	image_scale=1.0;
	screen_freq_save=0;
}

lstg::~lstg()
{
	release();
}

bool lstg::start(int argc, char** argv)
{
	//init object pool
	obj.init();
	//init hge
	hge=hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_LOGFILE,LOG_FILE);
	hge->System_SetState(HGE_FRAMEFUNC,FrameFunc);
	hge->System_SetState(HGE_FOCUSLOSTFUNC,FocusLoseFunc);
	hge->System_SetState(HGE_FOCUSGAINFUNC,FocusGainFunc);
	hge->System_SetState(HGE_DONTSUSPEND,true);
	//init lua and libs
	L=lua_open();
	luaL_openlibs(L);
	BIF::reg(L);
	Color::reg(L);
	RandGen::reg(L);
	//args
	lua_newtable(L);
	for(int i=0;i<argc;i++)
	{
		lua_pushnumber(L,i+1);
		lua_pushstring(L,argv[i]);
		lua_settable(L,-3);
	}
	lua_setglobal(L,"arg");
	//create metatable for objects and save it in lua registry as key "mt"
	lua_pushlightuserdata(L,(void *)_lstg);
	lua_createtable(L,POOL_INIT_SIZE,0);
	lua_newtable(L);
	lua_pushcfunction(L,BIF::ObjMetaIndex);
	lua_setfield(L,3,"__index");
	lua_pushcfunction(L,BIF::ObjMetaNewIndex);
	lua_setfield(L,3,"__newindex");
	lua_setfield(L,2,"mt");
	lua_settable(L,LUA_REGISTRYINDEX);
	//load basic scripts
	Ldofile(L,"launch","core init");
	//change screen's refresh freq to 60 if fullscreen mode is set
	/*
	lua_getglobal(L,"setting");
	lua_getfield(L,-1,"windowed");
	if(!lua_toboolean(L,-1))
	{
		DEVMODE DevMode;
		EnumDisplaySettings(NULL,ENUM_REGISTRY_SETTINGS,&DevMode);
		screen_freq_save=DevMode.dmDisplayFrequency;
		DevMode.dmDisplayFrequency=60;
		ChangeDisplaySettings(&DevMode,CDS_UPDATEREGISTRY);
	}
	lua_pop(L,2);
	*/
	//
	if(!hge->System_Initiate())
		Err("Can not initiate HGE.");
	//set fpu to double mode (it was previously changed to single by d3d)
	_controlfp_s(0,_PC_53,MCW_PC);
	//load core and user script
	Ldofile(L,"core.lua","core init");
	lua_getglobal(L,"GameInit");
	Lcall(L,0,0,"core init");
	//system start
	hge->System_Start();
	return false;
}

void lstg::release()
{
	if(screen_freq_save)
	{
		DEVMODE DevMode;
		EnumDisplaySettings(NULL,ENUM_REGISTRY_SETTINGS,&DevMode);
		DevMode.dmDisplayFrequency=screen_freq_save;
		ChangeDisplaySettings(&DevMode,CDS_UPDATEREGISTRY);
	}
}

void lstg::Err(const char * format,...)
{
	va_list vl;
	va_start(vl, format);
	vprintf(format,vl);
	printf("\n");
	FILE * logfile;
	if(!fopen_s(&logfile,LOG_FILE,"a"))
	{
		vfprintf(logfile,format,vl);
		fprintf(logfile,"\n");
		fclose(logfile);
	}
	va_end(vl);
	release();
	exit(1);
}

void lstg::Log(const char * format,...)
{
	va_list vl;
	va_start(vl, format);
	vprintf(format,vl);
	printf("\n");
	FILE * logfile;
	if(!fopen_s(&logfile,LOG_FILE,"a"))
	{
		vfprintf(logfile,format,vl);
		fprintf(logfile,"\n");
		fclose(logfile);
	}
	va_end(vl);
}

void lstg::Ldofile(lua_State * L,const char * filename,const char * from)
{
	DWORD sz;
	char * ptr=(char *)hge->Resource_Load(filename,&sz);
	if(ptr==0)
	{
		Err("from %s lstg::Ldofile Script \'%s\' not found.",from,filename);
		return;
	}
	if(luaL_loadbuffer(L,ptr,sz,filename)||lua_pcall(L,0,0,0))
	{
		Err("from %s lstg::Ldofile %s",from,lua_tostring(L,-1));
	}
	hge->Resource_Free(ptr);
}

void lstg::Lcall(lua_State * L,int nargs,int nresults,const char * from)
{
	if(lua_pcall(L,nargs,nresults,0))
		Err("from %s lstg::Lcall %s",from,lua_tostring(L,-1));
}

void lstg::Lcall(lua_State * L,int nargs,int nresults)
{
	if(lua_pcall(L,nargs,nresults,0))
		luaL_error(L,"\n%s",lua_tostring(L,-1));
}

void lstg_close()
{
	if(_lstg!=0) delete _lstg;
	_lstg=0;
	return;
}
lstg * lstg_open()
{
	lstg_close();
	return _lstg=new lstg();
}

bool FrameFunc()
{
	lua_getglobal(_lstg->L,"FrameFunc");
	_lstg->Lcall(_lstg->L,0,1,"FrameFunc");
	int re=lua_toboolean(_lstg->L,1);
	lua_settop(_lstg->L,0);
	return re;
}
bool FocusLoseFunc()
{
	lua_getglobal(_lstg->L,"FocusLoseFunc");
	_lstg->Lcall(_lstg->L,0,1,"FocusLoseFunc");
	lua_settop(_lstg->L,0);
	return false;
}
bool FocusGainFunc()
{
	lua_getglobal(_lstg->L,"FocusGainFunc");
	_lstg->Lcall(_lstg->L,0,1,"FocusGainFunc");
	lua_settop(_lstg->L,0);
	return false;
}