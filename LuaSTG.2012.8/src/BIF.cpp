#include "BIF.h"
#include "lstg.h"
#include <sstream>

#define STRBUFSZ 256
char strbuf[STRBUFSZ];

void BIF::reg(lua_State *L)
{
	luaL_Reg bif[]=
	{
		{"SetWindowed",&BIF::SetWindowed},
		{"SetFPS",&BIF::SetFPS},
		{"GetFPS",&BIF::GetFPS},
		{"SetVsync",&BIF::SetVsync},
		{"SetResolution",&BIF::SetResolution},
		{"SetSplash",&BIF::SetSplash},
		{"SetTitle",&BIF::SetTitle},
		{"SystemLog",&BIF::SystemLog},
		{"Print",&BIF::Print},
		{"LoadPack",&BIF::LoadPack},
		{"UnloadPack",&BIF::UnloadPack},
		{"DoFile",&BIF::DoFile},
		{"SetResourceStatus",&BIF::SetResourceStatus},
		{"GetAttr",&BIF::ObjMetaIndex},
		{"SetAttr",&BIF::ObjMetaNewIndex},
		{"GetnObj",&BIF::GetnObj},
		{"UpdateObjList",&BIF::UpdateObjList},
		{"ObjFrame",&BIF::ObjFrame},
		{"ObjRender",&BIF::ObjRender},
		{"BoundCheck",&BIF::BoundCheck},
		{"CollisionCheck",&BIF::CollisionCheck},
		{"UpdateXY",&BIF::UpdateXY},
		{"AfterFrame",&BIF::AfterFrame},
		{"New",&BIF::New},
		{"Del",&BIF::Del},
		{"Kill",&BIF::Kill},
		{"IsValid",&BIF::IsValid},
		{"SetV",&BIF::SetV},
		{"ResetPool",&BIF::ResetPool},
		{"DefaultRenderFunc",&BIF::DefaultRenderFunc},
		{"NextObject",&BIF::NextObject},
		{"ObjList",&BIF::ObjList},
		{"LoadTexture",&BIF::LoadTexture},
		{"LoadImage",&BIF::LoadImage_},
		{"LoadAnimation",&BIF::LoadAnimation},
		{"LoadPS",&BIF::LoadPS},
		{"LoadSound",&BIF::LoadSound},
		{"LoadMusic",&BIF::LoadMusic},
		{"LoadFont",&BIF::LoadFont},
		{"LoadTTF",&BIF::LoadTTF},
		{"RemoveResource",&BIF::RemoveResource},
		{"CheckRes",&BIF::CheckRes},
		{"EnumRes",&BIF::EnumRes},
		{"BeginScene",&BIF::BeginScene},
		{"EndScene",&BIF::EndScene},
		{"GetTextureSize",&BIF::GetTextureSize},
		{"Render",&BIF::Render},
		{"RenderRect",&BIF::RenderRect},
		{"Render4V",&BIF::Render4V},
		{"RenderText",&BIF::RenderText},
		{"RenderTexture",&BIF::RenderTexture},
		{"RenderClear",&BIF::RenderClear},
		{"RenderTTF",&BIF::RenderTTF},
		{"SetViewport",&BIF::SetViewport},
		{"SetOrtho",&BIF::SetOrtho},
		{"SetPerspective",&BIF::SetPerspective},
		{"SetImageScale",&BIF::SetImageScale},
		{"SetImageState",&BIF::SetImageState},
		{"SetFontState",&BIF::SetFontState},
		{"SetFontState2",&BIF::SetFontState2},
		{"SetAnimationState",&BIF::SetAnimationState},
		{"SetImageCenter",&BIF::SetImageCenter},
		{"SetAnimationCenter",&BIF::SetAnimationCenter},
		{"SetFog",&BIF::SetFog},
		{"ParticleStop",&BIF::ParticleStop},
		{"ParticleFire",&BIF::ParticleFire},
		{"ParticleGetn",&BIF::ParticleGetn},
		{"ParticleGetEmission",&BIF::ParticleGetEmission},
		{"ParticleSetEmission",&BIF::ParticleSetEmission},
		{"SetImgState",&BIF::SetImgState},
		{"Snapshot",&BIF::Snapshot},
		{"PlaySound",&BIF::PlaySound_},
		{"PlayMusic",&BIF::PlayMusic},
		{"StopMusic",&BIF::StopMusic},
		{"PauseMusic",&BIF::PauseMusic},
		{"ResumeMusic",&BIF::ResumeMusic},
		{"GetMusicState",&BIF::GetMusicState},
		{"UpdateSound",&BIF::UpdateSound},
		{"SetSEVolume",&BIF::SetSEVolume},
		{"SetBGMVolume",&BIF::SetBGMVolume},
		{"GetKeyState",&BIF::GetKeyState},
		{"GetLastKey",&BIF::GetLastKey},
		{"GetLastChar",&BIF::GetLastChar},
		{"Angle",&BIF::Angle},
		{"Dist",&BIF::Dist},
		{"BoxCheck",&BIF::BoxCheck},
		{"ObjTable",&BIF::ObjTable},
		{"Registry",&BIF::Registry},
		{"Color",&Color::New},
		{"Rand",&RandGen::New},
		{NULL,NULL}
	};
	luaL_register(L,"lstg",bif);
	lua_pop(L,1);
}

int BIF::SetWindowed(lua_State * L)
{
	_lstg->hge->System_SetState(HGE_WINDOWED,lua_toboolean(L,1));
	return 0;
}

int BIF::SetFPS(lua_State * L)
{
	_lstg->hge->System_SetState(HGE_FPS,luaL_checkint(L,1));
	return 0;
}
int BIF::SetVsync(lua_State * L)
{
	_lstg->hge->System_SetState(HGE_VSYNC,lua_toboolean(L,1)?true:false);
	return 0;
}
int BIF::GetFPS(lua_State * L)
{
	lua_pushnumber(L,_lstg->hge->Timer_GetFPS());
	return 1;
}
int BIF::SetResolution(lua_State *L)
{
	_lstg->hge->System_SetState(HGE_SCREENWIDTH,luaL_checkint(L,1));
	_lstg->hge->System_SetState(HGE_SCREENHEIGHT,luaL_checkint(L,2));
	return 0;
}
int BIF::SetSplash(lua_State * L)
{
	_lstg->hge->System_SetState(HGE_SHOWSPLASH,lua_toboolean(L,1));
	return 0;
}
int BIF::SetTitle(lua_State * L)
{
	_lstg->hge->System_SetState(HGE_TITLE,luaL_checkstring(L,1));
	return 0;
}
int BIF::SystemLog(lua_State * L)
{
	_lstg->Log("%s",luaL_checkstring(L,1));
	return 0;
}
int BIF::Print(lua_State * L)
{
	FILE * logfile;
	if(fopen_s(&logfile,LOG_FILE,"a"))
	{
		printf("Cannot open \'%s\'.\n",LOG_FILE);
		return 0;
	}
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for(i=1;i<=n;i++)
	{
		const char *s;
		lua_pushvalue(L,-1);  /* function to be called */
		lua_pushvalue(L,i);   /* value to print */
		lua_call(L,1,1);
		s = lua_tostring(L,-1);  /* get result */
		if (s==NULL)
			return luaL_error(L,LUA_QL("tostring") " must return a string to " LUA_QL("print"));
		if(i>1){printf("\t");fprintf(logfile,"\t");}
		printf("%s",s);fprintf(logfile,"%s",s);
		lua_pop(L,1);  /* pop result */
	}
	printf("\n");fprintf(logfile,"\n");
	fclose(logfile);
	return 0;
}
int BIF::LoadPack(lua_State * L)
{
	if(!_lstg->hge->Resource_AttachPack(luaL_checkstring(L,1)))
		luaL_error(L,"Pack \'%s\' not found.",luaL_checkstring(L,1));
	return 0;
}
int BIF::UnloadPack(lua_State * L)
{
	_lstg->hge->Resource_RemovePack(luaL_checkstring(L,1));
	return 0;
}
int BIF::DoFile(lua_State * L)
{
	DWORD sz;
	char * ptr=(char *)_lstg->hge->Resource_Load(luaL_checkstring(L,1),&sz);
	if(ptr==0)
	{
		luaL_error(L,"Script \'%s\' not found.",luaL_checkstring(L,1));
		return 0;
	}
	if(luaL_loadbuffer(L,ptr,sz,luaL_checkstring(L,1))||lua_pcall(L,0,0,0))
	{
		luaL_error(L,"\n%s %s",luaL_checkstring(L,1),lua_tostring(L,-1));
		return 0;
	}
	_lstg->hge->Resource_Free(ptr);
	return 0;
}
int BIF::SetResourceStatus(lua_State * L)
{
	if(strcmp(luaL_checkstring(L,1),"global")==0) _lstg->resource_status=RESOURCE_GLOBAL;
	else if (strcmp(luaL_checkstring(L,1),"stage")==0) _lstg->resource_status=RESOURCE_STAGE;
	else if (strcmp(luaL_checkstring(L,1),"none")==0) _lstg->resource_status=RESOURCE_NONE;
	else luaL_error(L,"Invalid argument.");
	return 0;
}
int BIF::GetnObj(lua_State * L)
{
	lua_pushnumber(L,_lstg->obj.getn());
	return 1;
}
int BIF::UpdateObjList(lua_State * L)
{
	lstgobj * pobj;
	_lstg->obj_list_all.clear();
	for(int i=0;i<GROUP_NUM_OF_GROUP;i++)
		_lstg->obj_list_type[i].clear();
	for(unsigned int i=0;i<_lstg->obj.size();i++)
	{
		pobj=_lstg->obj.ptr(i);
		if(pobj)
			_lstg->obj_list_all.push_back(i);
	}
	std::sort(_lstg->obj_list_all.begin(),_lstg->obj_list_all.end(),FramePrio);
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_all.begin();it!=_lstg->obj_list_all.end();it++)
	{
		pobj=_lstg->obj.ptr(*it);
		if(pobj->group>=0&&pobj->group<GROUP_NUM_OF_GROUP)
			_lstg->obj_list_type[pobj->group].push_back(*it);
	}
	return 0;
}
int BIF::ObjFrame(lua_State * L)
{
	lua_pushlightuserdata(L,(void *)_lstg);
	lua_gettable(L,LUA_REGISTRYINDEX);
	//stack status: ... obj_table
	lstgobj * pobj;
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_all.begin();it!=_lstg->obj_list_all.end();it++)
	{
		pobj=_lstg->obj.ptr(*it);
		if(pobj)
		{
			//stack status: ... obj_table
			lua_rawgeti(L,-1,(*it)+1);
			//stack status: ... obj_table obj
			lua_rawgeti(L,-1,1);
			//stack status: ... obj_table obj class
			lua_rawgeti(L,-1,FUNC_FRAME);
			//stack status: ... obj_table obj class frame_func
			lua_pushvalue(L,-3);
			//stack status: ... obj_table obj class frame_func obj
			_lstg->Lcall(L,1,0);
			//stack status: ... obj_table obj class
			lua_pop(L,2);
			//stack status: ... obj_table
			//
			pobj->x+=pobj->vx;
			pobj->y+=pobj->vy;
			pobj->r+=pobj->omiga;
			//
			if(pobj->pps)
			{
				pobj->pps->info.fDirection=pobj->r-M_PI_2;
				pobj->pps->info.fSpinStart=pobj->r;
				pobj->pps->SetScale(pobj->hscale*_lstg->image_scale);
				if(pobj->fireps)
					pobj->pps->FireAt(pobj->x/pobj->hscale/_lstg->image_scale,pobj->y/pobj->hscale/_lstg->image_scale);
				else
					pobj->pps->Stop();
				pobj->pps->Update(1.0f/60.0f);
			}
		}
	}
	lua_pop(L,1);
	return 0;
}
int BIF::ObjRender(lua_State * L)
{
	lstgobj * pobj;
	_lstg->obj_list_render.clear();
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_all.begin();it!=_lstg->obj_list_all.end();it++)
	{
		pobj=_lstg->obj.ptr((*it));
		if(pobj)
			_lstg->obj_list_render.push_back((*it));
	}
	std::sort(_lstg->obj_list_render.begin(),_lstg->obj_list_render.end(),RenderPrio);
	lua_pushlightuserdata(L,(void *)_lstg);
	lua_gettable(L,LUA_REGISTRYINDEX);
	//stack status: ... obj_table
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_render.begin();it!=_lstg->obj_list_render.end();it++)
	{
		pobj=_lstg->obj.ptr((*it));
		if(!pobj->hide)
		{
			//stack status: ... obj_table
			lua_rawgeti(L,-1,(*it)+1);
			//stack status: ... obj_table obj
			lua_rawgeti(L,-1,1);
			//stack status: ... obj_table obj class
			lua_rawgeti(L,-1,FUNC_RENDER);
			//stack status: ... obj_table obj class render_func
			lua_pushvalue(L,-3);
			//stack status: ... obj_table obj class render_func obj
			_lstg->Lcall(L,1,0);
			//stack status: ... obj_table obj class
			lua_pop(L,2);
			//stack status: ... obj_table
		}
	}
	lua_pop(L,1);
	return 0;
}
int BIF::BoundCheck(lua_State * L)
{
	lua_Number l=luaL_checknumber(L,1);
	lua_Number r=luaL_checknumber(L,2);
	lua_Number b=luaL_checknumber(L,3);
	lua_Number t=luaL_checknumber(L,4);
	lua_settop(L,0);
	lua_pushlightuserdata(L,(void *)_lstg);
	lua_gettable(L,LUA_REGISTRYINDEX);
	//stack status: obj_table
	lstgobj * pobj;
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_all.begin();it!=_lstg->obj_list_all.end();it++)
	{
		pobj=_lstg->obj.ptr(*it);
		if(pobj&&(pobj->x<l||pobj->x>r||pobj->y<b||pobj->y>t)&&pobj->bound)
		{
			//stack status: obj_table
			pobj->status=STATUS_DEL;
			lua_rawgeti(L,1,(*it)+1);
			//stack status: obj_table obj
			lua_rawgeti(L,2,1);
			//stack status: obj_table obj class
			lua_rawgeti(L,3,FUNC_DEL);
			//stack status: obj_table obj class del_func
			lua_insert(L,2);
			//stack status: obj_table del_func obj class
			lua_pop(L,1);
			//stack status: obj_table del_func obj
			_lstg->Lcall(L,1,0);
			//stack status: obj_table
		}
	}
	lua_pop(L,1);
	return 0;
}
int BIF::CollisionCheck(lua_State * L)
{
	int t1=luaL_checkint(L,1);
	int t2=luaL_checkint(L,2);
	if(t1<0||t1>=GROUP_NUM_OF_GROUP||t2<0||t2>=GROUP_NUM_OF_GROUP||t1==t2)
		luaL_error(L,"Invalid argument.");
	lua_settop(L,0);
	lua_pushlightuserdata(L,(void *)_lstg);
	lua_gettable(L,LUA_REGISTRYINDEX);
	// obj_table
	for(std::vector<unsigned int>::iterator it1=_lstg->obj_list_type[t1].begin();it1!=_lstg->obj_list_type[t1].end();it1++)
		for(std::vector<unsigned int>::iterator it2=_lstg->obj_list_type[t2].begin();it2!=_lstg->obj_list_type[t2].end();it2++)
		{
			if(colli_check(_lstg->obj.ptr(*it1),_lstg->obj.ptr(*it2)))
			{
				lua_rawgeti(L,1,(*it1)+1);
				// obj_table obj1
				lua_rawgeti(L,1,(*it2)+1);
				// obj_table obj1 obj2
				lua_rawgeti(L,2,1);
				// obj_table obj1 obj2 class1
				lua_rawgeti(L,4,FUNC_COLLI);
				// obj_table obj1 obj2 class1 func_colli_1
				lua_insert(L,2);
				// obj_table func_colli_1 obj1 obj2 class1
				lua_pop(L,1);
				// obj_table func_colli_1 obj1 obj2
				_lstg->Lcall(L,2,0);
				// obj_table
			}
		}
	return 0;
}
int BIF::UpdateXY(lua_State * L)
{
	lstgobj * pobj;
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_all.begin();it!=_lstg->obj_list_all.end();it++)
	{
		pobj=_lstg->obj.ptr(*it);
		if(pobj)
		{
			pobj->dx=pobj->x-pobj->lastx;
			pobj->dy=pobj->y-pobj->lasty;
			pobj->lastx=pobj->x;
			pobj->lasty=pobj->y;
			if(pobj->navi&&(pobj->dx!=0||pobj->dy!=0))
				pobj->r=atan2(pobj->dy,pobj->dx);
		}
	}
	return 0;
}
int BIF::AfterFrame(lua_State * L)
{
	lstgobj * pobj;
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_all.begin();it!=_lstg->obj_list_all.end();it++)
	{
		pobj=_lstg->obj.ptr(*it);
		pobj->timer++;
		pobj->ani_timer++;
		if(pobj&&(pobj->status!=STATUS_NORMAL))
		{
			if(pobj->img)
			{
				delete[] pobj->img;
				pobj->img=0;
			}
			if(pobj->pps)
			{
				delete pobj->pps;
				pobj->pps=0;
			}
			_lstg->obj.freeid(*it);
		}
	}
	return 0;
}
int BIF::New(lua_State * L)
{
	if lua_istable(L,1)
	{
		lua_getfield(L,1,"is_class");
		if(!lua_toboolean(L,-1))
			luaL_error(L,"Invalid class.");
		else
			lua_pop(L,1);
	}
	else
		luaL_error(L,"Invalid class.");

	unsigned int id=_lstg->obj.newid();
	if(id==-1) luaL_error(L,"Object pool is full.");
	lstgobj * pobj=_lstg->obj.ptr(id);
	if(id==POOL_MEM_FAIL)
	{
		luaL_error(L,"Memory allocation error.");
		return 1;
	}
	pobj->reset();
	pobj->uniq_id=_lstg->id_counter++;
	lua_pushlightuserdata(L,(void *)_lstg);
	lua_gettable(L,LUA_REGISTRYINDEX);
	//stack status: class ... obj_table
	lua_createtable(L,2,0);
	//stack status: class ... obj_table {nil,nil}
	lua_pushvalue(L,1);
	//stack status: class ... obj_table {nil,nil} class
	lua_rawseti(L,-2,1);
	//stack status: class ... obj_table {class,nil}
	lua_pushnumber(L,id);
	//stack status: class ... obj_table {class,nil} id
	lua_rawseti(L,-2,2);
	//stack status: class ... obj_table {class,id}
	lua_getfield(L,-2,"mt");
	//stack status: class ... obj_table {class,id} metatable
	lua_setmetatable(L,-2);
	//stack status: class ... obj_table {class,id}
	lua_pushvalue(L,-1);
	//stack status: class ... obj_table {class,id} {class,id}
	lua_rawseti(L,-3,id+1);
	//stack status: class ... obj_table(*) {class,id}
	lua_insert(L,1);
	//stack status: {class,id} class ... obj_table(*)
	lua_pop(L,1);
	//stack status: {class,id} class ...
	lua_rawgeti(L,2,FUNC_INIT);
	//stack status: {class,id} class ... init_func
	lua_insert(L,3);
	//stack status: {class,id} class init_func ... 
	lua_pushvalue(L,1);
	//stack status: {class,id} class init_func ... {class,id}
	lua_insert(L,4);
	//stack status: {class,id} class init_func {class,id} ...
	_lstg->Lcall(L,lua_gettop(L)-3,0);
	//stack status: {class,id} class
	lua_pop(L,1);
	//stack status: {class,id}
	pobj->lastx=pobj->x;pobj->lasty=pobj->y;
	return 1;
}
int BIF::Del(lua_State * L)
{
	if(lua_gettop(L)!=1) luaL_error(L,"Del takes exactly 1 arguement(s), got %d.",lua_gettop(L));
	if(!lua_istable(L,1)) luaL_error(L,"Invalid lstg object.");
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,2));
	lua_pop(L,1);
	if(pobj)
	{
		if(pobj->status==STATUS_NORMAL)
		{
			pobj->status=STATUS_DEL;
			lua_rawgeti(L,1,1);
			//stack status: obj class
			lua_rawgeti(L,2,FUNC_DEL);
			//stack status: obj class del_func
			lua_insert(L,1);
			//stack status: del_func obj class
			lua_pop(L,1);
			//stack status: del_func obj
			_lstg->Lcall(L,1,0);
		}
	}
	else luaL_error(L,"Invalid lstg object.");
	return 0;
}
int BIF::Kill(lua_State * L)
{
	if(lua_gettop(L)!=1) luaL_error(L,"Kill takes exactly 1 arguement(s), got %d.",lua_gettop(L));
	if(!lua_istable(L,1)) luaL_error(L,"Invalid lstg object.");
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,2));
	lua_pop(L,1);
	if(pobj)
	{
		if(pobj->status==STATUS_NORMAL)
		{
			pobj->status=STATUS_KILL;
			lua_rawgeti(L,1,1);
			//stack status: obj class
			lua_rawgeti(L,2,FUNC_KILL);
			//stack status: obj class kill_func
			lua_insert(L,1);
			//stack status: del_func obj class
			lua_pop(L,1);
			//stack status: del_func obj
			_lstg->Lcall(L,1,0);
		}
	}
	else luaL_error(L,"Invalid lstg object.");
	return 0;
}
int BIF::IsValid(lua_State * L)
{
	if(lua_gettop(L)!=1) luaL_error(L,"IsValid takes exactly 1 arguement(s), got %d.",lua_gettop(L));
	if(!lua_istable(L,1)){lua_pushboolean(L,0);return 1;}
	lua_rawgeti(L,1,2);
	if(!lua_isnumber(L,2)){lua_pushboolean(L,0);return 1;}
	int i=(int)lua_tonumber(L,2);
	if(_lstg->obj.ptr(i))
	{
		lua_pushlightuserdata(L,(void *)_lstg);
		lua_gettable(L,LUA_REGISTRYINDEX);
		lua_rawgeti(L,3,i+1);
		if(lua_rawequal(L,1,4)) lua_pushboolean(L,1);
		else lua_pushboolean(L,0);
	}
	else lua_pushboolean(L,0);
	return 1;
}
int BIF::SetV(lua_State * L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,-1));
	lua_pop(L,1);
	if(pobj)
	{
		lua_Number v=luaL_checknumber(L,2);
		lua_Number a=luaL_checknumber(L,3)*DEGREE2RAD;
		pobj->vx=v*cos(a);
		pobj->vy=v*sin(a);
		if(lua_toboolean(L,4)) pobj->r=a;
	}
	else luaL_error(L,"Invalid lstg object.");
	return 0;
}
int BIF::SetImgState(lua_State * L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,-1));
	lua_pop(L,1);
	if(pobj)
	{
		DWORD color=ARGB(luaL_checknumber(L,3),luaL_checknumber(L,4),luaL_checknumber(L,5),luaL_checknumber(L,6));
		if(pobj->pimage)
		{
			pobj->pimage->SetBlendMode(TranslateBlendMode(L,2));
			pobj->pimage->SetColor(color);
		}
		else if(pobj->panimation)
		{

			pobj->panimation->quad.blend=TranslateBlendMode(L,2);
			pobj->panimation->quad.v[0].col=color;
			pobj->panimation->quad.v[1].col=color;
			pobj->panimation->quad.v[2].col=color;
			pobj->panimation->quad.v[3].col=color;
		}
	}
	else luaL_error(L,"Invalid lstg object.");
	return 0;
}
int BIF::BoxCheck(lua_State * L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,-1));
	lua_pop(L,1);
	if(pobj)
	{
		lua_pushboolean(L,(pobj->x>luaL_checknumber(L,2))&&(pobj->x<luaL_checknumber(L,3))&&(pobj->y>luaL_checknumber(L,4))&&(pobj->y<luaL_checknumber(L,5)));
	}
	else luaL_error(L,"Invalid lstg object.");
	return 1;
}
int BIF::ResetPool(lua_State * L)
{
	lstgobj * pobj;
	for(std::vector<unsigned int>::iterator it=_lstg->obj_list_all.begin();it!=_lstg->obj_list_all.end();it++)
	{
		pobj=_lstg->obj.ptr(*it);
		if(pobj)
		{
			if(pobj->img)
			{
				delete[] pobj->img;
				pobj->img=0;
			}
			if(pobj->pps)
			{
				delete pobj->pps;
				pobj->pps=0;
			}
		}
	}
	_lstg->obj.reset();
	_lstg->obj_list_all.clear();
	for(int i=0;i<GROUP_NUM_OF_GROUP;i++)
		_lstg->obj_list_type[i].clear();
	return 0;
}
int BIF::ObjMetaIndex(lua_State * L)
{
	//t k
	lua_rawgeti(L,1,2);
	//t k i
	unsigned int i=(unsigned int)lua_tonumber(L,3);
	lua_pop(L,1);
	//t k
	lstgobj * pobj=_lstg->obj.ptr(i);
	if(pobj==0) luaL_error(L,"Invalid lstg object");
	else
	{
		const char * key=luaL_checkstring(L,2);
		if(strcmp(key,"x")==0)
			lua_pushnumber(L,pobj->x);
		else if(strcmp(key,"y")==0)
			lua_pushnumber(L,pobj->y);
		else if(strcmp(key,"rot")==0)
			lua_pushnumber(L,pobj->r*RAD2DEGREE);
		else if(strcmp(key,"img")==0)
		{
			if(pobj->img==0) lua_pushstring(L,"");
			else lua_pushstring(L,pobj->img);
		}
		else if(strcmp(key,"timer")==0)
			lua_pushnumber(L,pobj->timer);
		else if(strcmp(key,"vx")==0)
			lua_pushnumber(L,pobj->vx);
		else if(strcmp(key,"vy")==0)
			lua_pushnumber(L,pobj->vy);
		else if(strcmp(key,"omiga")==0)
			lua_pushnumber(L,pobj->omiga*RAD2DEGREE);
		else if(strcmp(key,"layer")==0)
			lua_pushnumber(L,pobj->layer);
		else if(strcmp(key,"group")==0)
			lua_pushnumber(L,pobj->group);
		else if(strcmp(key,"hide")==0)
			lua_pushboolean(L,pobj->hide);
		else if(strcmp(key,"bound")==0)
			lua_pushboolean(L,pobj->bound);
		else if(strcmp(key,"navi")==0)
			lua_pushboolean(L,pobj->navi);
		else if(strcmp(key,"colli")==0)
			lua_pushboolean(L,pobj->colli);
		else if(strcmp(key,"dx")==0)
			lua_pushnumber(L,pobj->dx);
		else if(strcmp(key,"dy")==0)
			lua_pushnumber(L,pobj->dy);
		else if(strcmp(key,"status")==0)
		{
			if(pobj->status==STATUS_DEL) lua_pushstring(L,"del");
			else if(pobj->status==STATUS_KILL) lua_pushstring(L,"kill");
			else lua_pushstring(L,"normal");
		}
		else if(strcmp(key,"hscale")==0)
			lua_pushnumber(L,pobj->hscale);
		else if(strcmp(key,"vscale")==0)
			lua_pushnumber(L,pobj->vscale);
		else if(strcmp(key,"class")==0)
			lua_rawgeti(L,1,1);
		else if(strcmp(key,"a")==0)
			lua_pushnumber(L,pobj->a/_lstg->image_scale);
		else if(strcmp(key,"b")==0)
			lua_pushnumber(L,pobj->b/_lstg->image_scale);
		else if(strcmp(key,"rect")==0)
			lua_pushboolean(L,pobj->rect);
		else if(strcmp(key,"ani")==0)
			lua_pushnumber(L,pobj->ani_timer);
		else
			lua_pushnil(L);
	}
	return 1;
}
int BIF::ObjMetaNewIndex(lua_State * L)
{
	//t k v
	lua_rawgeti(L,1,2);
	//t k v i
	unsigned int i=(unsigned int)lua_tonumber(L,4);
	lua_pop(L,1);
	//t k v
	lstgobj * pobj=_lstg->obj.ptr(i);
	if(pobj==0) luaL_error(L,"Invalid lstg object");
	else
	{
		const char * key=luaL_checkstring(L,2);
		if(strcmp(key,"x")==0)
			pobj->x=luaL_checknumber(L,3);
		else if(strcmp(key,"y")==0)
			pobj->y=luaL_checknumber(L,3);
		else if(strcmp(key,"rot")==0)
			pobj->r=luaL_checknumber(L,3)*DEGREE2RAD;
		else if(strcmp(key,"img")==0)
		{
			if(pobj->img) delete[] pobj->img;
			size_t sz=strlen(luaL_checkstring(L,3));
			pobj->img=new char[sz+1];
			strcpy_s(pobj->img,sz+1,luaL_checkstring(L,3));
			lstgPSI * ppsi;
			if((pobj->pimage=_lstg->img[1].find(pobj->img))||(pobj->pimage=_lstg->img[0].find(pobj->img)))
			{
				if(pobj->pps){delete pobj->pps;pobj->pps=0;}
				pobj->panimation=0;
				pobj->a=pobj->pimage->_a*_lstg->image_scale;
				pobj->b=pobj->pimage->_b*_lstg->image_scale;
				pobj->rect=pobj->pimage->_rect;
			}
			else if((pobj->panimation=_lstg->ani[1].find(pobj->img))||(pobj->panimation=_lstg->ani[0].find(pobj->img)))
			{
				if(pobj->pps){delete pobj->pps;pobj->pps=0;}
				pobj->pimage=0;
				pobj->a=pobj->panimation->_a*_lstg->image_scale;
				pobj->b=pobj->panimation->_b*_lstg->image_scale;
				pobj->rect=pobj->panimation->_rect;
			}
			else if((ppsi=_lstg->psi[1].find(pobj->img))||(ppsi=_lstg->psi[0].find(pobj->img)))
			{
				pobj->pimage=0;
				pobj->panimation=0;
				if(pobj->pps)
				{
					memcpy(&pobj->pps->info,ppsi->psi,sizeof(hgeParticleSystemInfo));
				}
				else
				{
					pobj->pps=new hgeParticleSystem(ppsi->psi);
				}
				pobj->pps->SetScale(pobj->hscale*_lstg->image_scale);
				pobj->a=ppsi->_a*_lstg->image_scale;
				pobj->b=ppsi->_b*_lstg->image_scale;
				pobj->rect=ppsi->_rect;
			}
			else
				luaL_error(L,"Image/Animation/ParticleSystem \'%s\' not found",pobj->img);
		}
		else if(strcmp(key,"timer")==0)
			pobj->timer=luaL_checknumber(L,3);
		else if(strcmp(key,"vx")==0)
			pobj->vx=luaL_checknumber(L,3);
		else if(strcmp(key,"vy")==0)
			pobj->vy=luaL_checknumber(L,3);
		else if(strcmp(key,"omiga")==0)
			pobj->omiga=luaL_checknumber(L,3)*DEGREE2RAD;
		else if(strcmp(key,"layer")==0)
			pobj->layer=luaL_checknumber(L,3);
		else if(strcmp(key,"group")==0)
			pobj->group=luaL_checkinteger(L,3);
		else if(strcmp(key,"hide")==0)
			pobj->hide=lua_toboolean(L,3);
		else if(strcmp(key,"bound")==0)
			pobj->bound=lua_toboolean(L,3);
		else if(strcmp(key,"navi")==0)
			pobj->navi=lua_toboolean(L,3);
		else if(strcmp(key,"colli")==0)
			pobj->colli=lua_toboolean(L,3);
		else if(strcmp(key,"dx")==0||strcmp(key,"dy")==0)
			luaL_error(L,"Property \'dx\' \'dy\' is read-only.");
		else if(strcmp(key,"status")==0)
		{
			if(strcmp(luaL_checkstring(L,3),"normal")==0) pobj->status=STATUS_NORMAL;
			else if(strcmp(luaL_checkstring(L,3),"del")==0) pobj->status=STATUS_DEL;
			else if(strcmp(luaL_checkstring(L,3),"kill")==0) pobj->status=STATUS_KILL;
			else luaL_error(L,"Invalid argument.");
		}
		else if(strcmp(key,"hscale")==0)
			pobj->hscale=luaL_checknumber(L,3);
		else if(strcmp(key,"vscale")==0)
			pobj->vscale=luaL_checknumber(L,3);
		else if(strcmp(key,"class")==0)
			lua_rawseti(L,1,1);
		else if(strcmp(key,"a")==0)
			pobj->a=luaL_checknumber(L,3)*_lstg->image_scale;
		else if(strcmp(key,"b")==0)
			pobj->b=luaL_checknumber(L,3)*_lstg->image_scale;
		else if(strcmp(key,"rect")==0)
			pobj->rect=lua_toboolean(L,3);
		else if(strcmp(key,"ani")==0)
			luaL_error(L,"Property \'ani\' is read-only.");
		else
		{
			lua_rawset(L,1);
		}
	}	
	return 0;
}
int BIF::DefaultRenderFunc(lua_State * L)
{
	lua_rawgeti(L,1,2);
	unsigned int i=(unsigned int)lua_tonumber(L,2);
	lstgobj * pobj=_lstg->obj.ptr(i);
	if(pobj)
	{
		if(pobj->pimage)
			pobj->pimage->RenderEx(pobj->x,pobj->y,pobj->r,_lstg->image_scale*pobj->hscale,_lstg->image_scale*pobj->vscale);
		else if(pobj->panimation)
			pobj->panimation->RenderEx(pobj->ani_timer,pobj->x,pobj->y,pobj->r,_lstg->image_scale*pobj->hscale,_lstg->image_scale*pobj->vscale);
		else if(pobj->pps)
			pobj->pps->Render();
		/*
		else
			luaL_error(L,"A image/animation must be set before calling default render function.");
		*/
	}
	else
		luaL_error(L,"Invalid lstg object");
	return 0;
}
int BIF::NextObject(lua_State * L)
{
	int t=luaL_checkint(L,1);
	unsigned int i=(unsigned int)luaL_checkint(L,2)+1;
	if(t<0||t>=GROUP_NUM_OF_GROUP)
	{
		if(i<=0||i>_lstg->obj_list_all.size()) return 0;
		else
		{
			// i t
			lua_pushnumber(L,i);
			// i t i+1
			lua_pushlightuserdata(L,(void *)_lstg);
			lua_gettable(L,LUA_REGISTRYINDEX);
			// i t i+1 obj_table
			lua_rawgeti(L,4,_lstg->obj_list_all[i-1]+1);
			// i t i+1 obj_table obj
			lua_insert(L,4);
			// i t i+1 obj obj_table
			lua_pop(L,1);
			// i t i+1 obj
			return 2;
		}
	}
	else
	{
		if(i<=0||i>_lstg->obj_list_type[t].size()) return 0;
		else
		{
			// i t
			lua_pushnumber(L,i);
			// i t i+1
			lua_pushlightuserdata(L,(void *)_lstg);
			lua_gettable(L,LUA_REGISTRYINDEX);
			// i t i+1 obj_table
			lua_rawgeti(L,4,_lstg->obj_list_type[t][i-1]+1);
			// i t i+1 obj_table obj
			lua_insert(L,4);
			// i t i+1 obj obj_table
			lua_pop(L,1);
			// i t i+1 obj
			return 2;
		}
	}
}
int BIF::ObjList(lua_State * L)
{
	lua_pushcfunction(L,BIF::NextObject);
	lua_insert(L,-2);
	lua_pushnumber(L,0);
	return 3;
}
int BIF::LoadTexture(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		//if(_lstg->tex[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"Texture \'%s\' already exists.",luaL_checkstring(L,1));
		if(_lstg->tex[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
		if(_lstg->tex[_lstg->resource_status].insert(luaL_checkstring(L,1),new lstgTexture(luaL_checkstring(L,2),lua_toboolean(L,3))))
			luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::LoadImage_(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		lstgTexture * ptex;
		if((ptex=_lstg->tex[1].find(luaL_checkstring(L,2)))||(ptex=_lstg->tex[0].find(luaL_checkstring(L,2))))
		{
			//if(_lstg->img[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"Image \'%s\' already exists.",luaL_checkstring(L,1));
			if(_lstg->img[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
			lstgImage * pimg=new lstgImage(ptex,luaL_checknumber(L,3),luaL_checknumber(L,4),luaL_checknumber(L,5),luaL_checknumber(L,6),luaL_optnumber(L,7,0.0f),luaL_optnumber(L,8,0.0f),lua_toboolean(L,9));
			if(_lstg->img[_lstg->resource_status].insert(luaL_checkstring(L,1),pimg))
				luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
		}
		else luaL_error(L,"Texture \'%s\' not found",luaL_checkstring(L,2));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::LoadAnimation(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		lstgTexture * ptex;
		if((ptex=_lstg->tex[1].find(luaL_checkstring(L,2)))||(ptex=_lstg->tex[0].find(luaL_checkstring(L,2))))
		{
			//if(_lstg->ani[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"Animation \'%s\' already exists.",luaL_checkstring(L,1));
			if(_lstg->ani[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
			lstgAnimation * pani=new lstgAnimation(ptex,luaL_checknumber(L,3),luaL_checknumber(L,4),luaL_checknumber(L,5),luaL_checknumber(L,6),luaL_checkinteger(L,7),luaL_checkinteger(L,8),luaL_checkinteger(L,9),luaL_optnumber(L,10,0.0f),luaL_optnumber(L,11,0.0f),lua_toboolean(L,12));
			if(_lstg->ani[_lstg->resource_status].insert(luaL_checkstring(L,1),pani))
				luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
		}
		else luaL_error(L,"Texture \'%s\' not found",luaL_checkstring(L,2));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::LoadPS(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		lstgImage * pimg;
		if((pimg=_lstg->img[1].find(luaL_checkstring(L,3)))||(pimg=_lstg->img[0].find(luaL_checkstring(L,3))))
		{
			//if(_lstg->psi[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"Particle system \'%s\' already exists.",luaL_checkstring(L,1));
			if(_lstg->psi[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
			if(_lstg->psi[_lstg->resource_status].insert(luaL_checkstring(L,1),new lstgPSI(luaL_checkstring(L,2),pimg,luaL_optnumber(L,4,0.0f),luaL_optnumber(L,5,0.0f),lua_toboolean(L,6))))
				luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
		}
		else luaL_error(L,"Image \'%s\' not found",luaL_checkstring(L,3));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::LoadSound(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		//if(_lstg->snd[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"Sound \'%s\' already exists.",luaL_checkstring(L,1));
		if(_lstg->snd[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
		if(_lstg->snd[_lstg->resource_status].insert(luaL_checkstring(L,1),new lstgSound(luaL_checkstring(L,2))))
			luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::LoadMusic(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		//if(_lstg->bgm[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"Music \'%s\' already exists.",luaL_checkstring(L,1));
		if(_lstg->bgm[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
		if(_lstg->bgm[_lstg->resource_status].insert(luaL_checkstring(L,1),new lstgBGM(luaL_checkstring(L,2),luaL_checknumber(L,3),luaL_checknumber(L,4))))
			luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::LoadFont(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		//if(_lstg->fnt[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"Font \'%s\' already exists.",luaL_checkstring(L,1));
		if(_lstg->fnt[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
		if(_lstg->fnt[_lstg->resource_status].insert(luaL_checkstring(L,1),new hgeFont(luaL_checkstring(L,2),lua_toboolean(L,3))))
			luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::LoadTTF(lua_State * L)
{
	if(_lstg->resource_status!=RESOURCE_NONE)
	{
		//if(_lstg->ttf[_lstg->resource_status].find(luaL_checkstring(L,1))) luaL_error(L,"TTF \'%s\' already exists.",luaL_checkstring(L,1));
		if(_lstg->ttf[_lstg->resource_status].find(luaL_checkstring(L,1))) return 0;
		if(_lstg->ttf[_lstg->resource_status].insert(luaL_checkstring(L,1),new lstgTTF(luaL_checkstring(L,2),(LONG)luaL_checknumber(L,3),(LONG)luaL_checknumber(L,4),(LONG)luaL_checknumber(L,5),(LONG)luaL_checknumber(L,6),(LONG)luaL_checknumber(L,7))))
			luaL_error(L,"Fail to load resource \'%s\'.",luaL_checkstring(L,1));
	}
	else luaL_error(L,"Can not load resource at this time.");
	return 0;
}
int BIF::RemoveResource(lua_State * L)
{
	int t;
	if(strcmp(luaL_checkstring(L,1),"global")==0) t=RESOURCE_GLOBAL;
	else if (strcmp(luaL_checkstring(L,1),"stage")==0) t=RESOURCE_STAGE;
	else t=RESOURCE_NONE;
	if(t==RESOURCE_GLOBAL||t==RESOURCE_STAGE)
	{
		_lstg->tex[t].clear();
		_lstg->img[t].clear();
		_lstg->ani[t].clear();
		_lstg->bgm[t].clear();
		_lstg->snd[t].clear();
		_lstg->psi[t].clear();
		_lstg->fnt[t].clear();
		_lstg->ttf[t].clear();
	}
	else
		luaL_error(L,"Invalid argument.");
	return 0;
}
int BIF::CheckRes(lua_State * L)
{
	int t=luaL_checkint(L,1);
	switch(t)
	{
	case RES_TYPE_TEX:
		if(_lstg->tex[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->tex[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	case RES_TYPE_IMG:
		if(_lstg->img[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->img[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	case RES_TYPE_ANI:
		if(_lstg->ani[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->ani[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	case RES_TYPE_BGM:
		if(_lstg->bgm[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->bgm[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	case RES_TYPE_SND:
		if(_lstg->snd[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->snd[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	case RES_TYPE_PSI:
		if(_lstg->psi[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->psi[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	case RES_TYPE_FNT:
		if(_lstg->fnt[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->fnt[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	case RES_TYPE_TTF:
		if(_lstg->ttf[0].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"global");
		else if(_lstg->ttf[1].find(luaL_checkstring(L,2)))
			lua_pushstring(L,"stage");
		else
			lua_pushnil(L);
		break;
	default:
		luaL_error(L,"Invalid resource type %d .",t);
	}
	return 1;
}
int BIF::EnumRes(lua_State * L)
{
	int t=luaL_checkint(L,1);
	std::map<char *,lstgTexture *,charcmp>::iterator it_tex;
	std::map<char *,lstgImage *,charcmp>::iterator it_img;
	std::map<char *,lstgAnimation *,charcmp>::iterator it_ani;
	std::map<char *,lstgBGM *,charcmp>::iterator it_bgm;
	std::map<char *,lstgSound *,charcmp>::iterator it_snd;
	std::map<char *,lstgPSI *,charcmp>::iterator it_psi;
	std::map<char *,hgeFont *,charcmp>::iterator it_fnt;
	std::map<char *,lstgTTF *,charcmp>::iterator it_ttf;
	lua_newtable(L);
	//... {}
	lua_newtable(L);
	//... {} {}
	switch(t)
	{
	case RES_TYPE_TEX:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_tex=_lstg->tex[k].map.begin();it_tex!=_lstg->tex[k].map.end();it_tex++)
			{
				lua_pushstring(L,it_tex->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	case RES_TYPE_IMG:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_img=_lstg->img[k].map.begin();it_img!=_lstg->img[k].map.end();it_img++)
			{
				lua_pushstring(L,it_img->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	case RES_TYPE_ANI:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_ani=_lstg->ani[k].map.begin();it_ani!=_lstg->ani[k].map.end();it_ani++)
			{
				lua_pushstring(L,it_ani->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	case RES_TYPE_BGM:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_bgm=_lstg->bgm[k].map.begin();it_bgm!=_lstg->bgm[k].map.end();it_bgm++)
			{
				lua_pushstring(L,it_bgm->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	case RES_TYPE_SND:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_snd=_lstg->snd[k].map.begin();it_snd!=_lstg->snd[k].map.end();it_snd++)
			{
				lua_pushstring(L,it_snd->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	case RES_TYPE_PSI:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_psi=_lstg->psi[k].map.begin();it_psi!=_lstg->psi[k].map.end();it_psi++)
			{
				lua_pushstring(L,it_psi->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	case RES_TYPE_FNT:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_fnt=_lstg->fnt[k].map.begin();it_fnt!=_lstg->fnt[k].map.end();it_fnt++)
			{
				lua_pushstring(L,it_fnt->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	case RES_TYPE_TTF:
		for(int k=0;k<2;k++)
		{
			int i=1;
			for(it_ttf=_lstg->ttf[k].map.begin();it_ttf!=_lstg->ttf[k].map.end();it_ttf++)
			{
				lua_pushstring(L,it_ttf->first);
				lua_rawseti(L,-3+k,i);
				i++;
			}
		}
		break;
	default:
		luaL_error(L,"Invalid resource type %d .",t);
	}
	return 2;
}
int BIF::BeginScene(lua_State * L)
{
	_lstg->hge->Gfx_BeginScene();
	return 0;
}
int BIF::EndScene(lua_State * L)
{
	_lstg->hge->Gfx_EndScene();
	return 0;
}
int BIF::GetTextureSize(lua_State * L)
{
	lstgTexture * ptex;
	if((ptex=_lstg->tex[1].find(luaL_checkstring(L,1)))||(ptex=_lstg->tex[0].find(luaL_checkstring(L,1))))
	{
		lua_pushnumber(L,_lstg->hge->Texture_GetWidth(ptex->tex));
		lua_pushnumber(L,_lstg->hge->Texture_GetHeight(ptex->tex));
	}
	else luaL_error(L,"Texture \'%s\' not found",luaL_checkstring(L,2));
	return 2;
}
int BIF::Render(lua_State * L)
{
	lstgImage * pimg;
	if((pimg=_lstg->img[1].find(luaL_checkstring(L,1)))||(pimg=_lstg->img[0].find(luaL_checkstring(L,1))))
		pimg->RenderEx(luaL_checknumber(L,2),luaL_checknumber(L,3),luaL_optnumber(L,4,0.0)*DEGREE2RAD,luaL_optnumber(L,5,1.0)*_lstg->image_scale,luaL_optnumber(L,6,luaL_optnumber(L,5,1.0))*_lstg->image_scale,luaL_optnumber(L,7,0.5));
	else
		luaL_error(L,"Image \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::RenderRect(lua_State * L)
{
	lstgImage * pimg;
	if((pimg=_lstg->img[1].find(luaL_checkstring(L,1)))||(pimg=_lstg->img[0].find(luaL_checkstring(L,1))))
		pimg->RenderStretch(luaL_checknumber(L,2),luaL_checknumber(L,5),luaL_checknumber(L,3),luaL_checknumber(L,4));
	else
		luaL_error(L,"Image \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::Render4V(lua_State * L)
{
	lstgImage * pimg;
	if((pimg=_lstg->img[1].find(luaL_checkstring(L,1)))||(pimg=_lstg->img[0].find(luaL_checkstring(L,1))))
		pimg->Render4V(luaL_checknumber(L,2),luaL_checknumber(L,3),luaL_checknumber(L,4),
					   luaL_checknumber(L,5),luaL_checknumber(L,6),luaL_checknumber(L,7),
					   luaL_checknumber(L,8),luaL_checknumber(L,9),luaL_checknumber(L,10),
					   luaL_checknumber(L,11),luaL_checknumber(L,12),luaL_checknumber(L,13));
	else
		luaL_error(L,"Image \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::RenderText(lua_State * L)
{
	hgeFont * pfnt;
	if((pfnt=_lstg->fnt[1].find(luaL_checkstring(L,1)))||(pfnt=_lstg->fnt[0].find(luaL_checkstring(L,1))))
	{
		pfnt->SetScale(_lstg->image_scale*luaL_optnumber(L,5,1.0));
		pfnt->Render(luaL_checknumber(L,3),luaL_checknumber(L,4),luaL_optint(L,6,HGETEXT_CENTER+HGETEXT_MIDDLE),luaL_checkstring(L,2));
	}
	else
		luaL_error(L,"Font \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::RenderTexture(lua_State * L)
{
	lstgTexture * ptex;
	if((ptex=_lstg->tex[1].find(luaL_checkstring(L,1)))||(ptex=_lstg->tex[0].find(luaL_checkstring(L,1))))
	{
		hgeQuad q;
		q.tex=ptex->tex;
		q.blend=TranslateBlendMode(L,2);
		for(int i=0;i<4;i++)
		{
			lua_pushinteger(L,1);
			lua_gettable(L,3+i);
			q.v[i].x=lua_tonumber(L,-1);
			lua_pop(L,1);

			lua_pushinteger(L,2);
			lua_gettable(L,3+i);
			q.v[i].y=lua_tonumber(L,-1);
			lua_pop(L,1);

			lua_pushinteger(L,3);
			lua_gettable(L,3+i);
			q.v[i].z=lua_tonumber(L,-1);
			lua_pop(L,1);

			lua_pushinteger(L,4);
			lua_gettable(L,3+i);
			q.v[i].tx=lua_tonumber(L,-1)/_lstg->hge->Texture_GetWidth(ptex->tex);
			lua_pop(L,1);

			lua_pushinteger(L,5);
			lua_gettable(L,3+i);
			q.v[i].ty=lua_tonumber(L,-1)/_lstg->hge->Texture_GetHeight(ptex->tex);
			lua_pop(L,1);

			lua_pushinteger(L,6);
			lua_gettable(L,3+i);
			q.v[i].col=*((DWORD *)luaL_checkudata(L,-1,COLOR_TYPENAME));
			lua_pop(L,1);
		}
		_lstg->hge->Gfx_RenderQuad(&q);
	}
	else luaL_error(L,"Texture \'%s\' not found",luaL_checkstring(L,2));
	return 0;
}
int BIF::RenderClear(lua_State * L)
{
	DWORD * c=(DWORD *)luaL_checkudata(L,1,COLOR_TYPENAME);
	_lstg->hge->Gfx_Clear(*c);
	return 0;
}
int BIF::RenderTTF(lua_State * L)
{
	//return 0;
	lstgTTF * pttf;
	if((pttf=_lstg->ttf[1].find(luaL_checkstring(L,1)))||(pttf=_lstg->ttf[0].find(luaL_checkstring(L,1))))
		_lstg->hge->TTF_Draw(pttf->font,luaL_checkstring(L,2),(LONG)luaL_checknumber(L,3),(LONG)luaL_checknumber(L,4),(LONG)luaL_checknumber(L,5),(LONG)luaL_checknumber(L,6),(LONG)luaL_checknumber(L,7),*((DWORD *)luaL_checkudata(L,8,COLOR_TYPENAME)));
	else
		luaL_error(L,"TTF \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::SetViewport(lua_State * L)
{
	_lstg->hge->Gfx_SetViewport(luaL_checkinteger(L,1),luaL_checkinteger(L,2),luaL_checkinteger(L,3),luaL_checkinteger(L,4));
	return 0;
}
int BIF::SetOrtho(lua_State *L)
{
	_lstg->hge->Gfx_SetOrtho(luaL_checknumber(L,1),luaL_checknumber(L,2),luaL_checknumber(L,3),luaL_checknumber(L,4));
	return 0;
}
int BIF::SetPerspective(lua_State * L)
{
	_lstg->hge->Gfx_SetPerspective(luaL_checknumber(L,1),luaL_checknumber(L,2),luaL_checknumber(L,3),
								   luaL_checknumber(L,4),luaL_checknumber(L,5),luaL_checknumber(L,6),
								   luaL_checknumber(L,7),luaL_checknumber(L,8),luaL_checknumber(L,9),
								   luaL_checknumber(L,10),luaL_checknumber(L,11),luaL_checknumber(L,12),luaL_checknumber(L,13));
	return 0;
}
int BIF::SetImageScale(lua_State * L)
{
	_lstg->image_scale=luaL_checknumber(L,1);
	return 0;
}

int BIF::SetImageState(lua_State * L)
{
	lstgImage * pimg;
	if((pimg=_lstg->img[1].find(luaL_checkstring(L,1)))||(pimg=_lstg->img[0].find(luaL_checkstring(L,1))))
	{
		pimg->SetBlendMode(TranslateBlendMode(L,2));
		if(lua_gettop(L)==3)
		{
			pimg->SetColor(*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME)));
		}
		else if(lua_gettop(L)==6)
		{
			pimg->SetColor(*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME)),0);
			pimg->SetColor(*((DWORD *)luaL_checkudata(L,4,COLOR_TYPENAME)),1);
			pimg->SetColor(*((DWORD *)luaL_checkudata(L,5,COLOR_TYPENAME)),2);
			pimg->SetColor(*((DWORD *)luaL_checkudata(L,6,COLOR_TYPENAME)),3);
		}
	}
	else
		luaL_error(L,"Image \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::SetFontState(lua_State * L)
{
	hgeFont * pfnt;
	if((pfnt=_lstg->fnt[1].find(luaL_checkstring(L,1)))||(pfnt=_lstg->fnt[0].find(luaL_checkstring(L,1))))
	{
		pfnt->SetBlendMode(TranslateBlendMode(L,2));
		if(lua_gettop(L)==3) pfnt->SetColor(*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME)));
	}
	else
		luaL_error(L,"Font \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::SetFontState2(lua_State * L)
{
	hgeFont * pfnt;
	if((pfnt=_lstg->fnt[1].find(luaL_checkstring(L,1)))||(pfnt=_lstg->fnt[0].find(luaL_checkstring(L,1))))
	{
		pfnt->SetProportion(luaL_optnumber(L,2,1.0));
		pfnt->SetRotation(luaL_optnumber(L,3,0.0)*DEGREE2RAD);
		pfnt->SetSpacing(luaL_optnumber(L,4,1.0));
		pfnt->SetTracking(luaL_optnumber(L,5,0.0));
		
	}
	else
		luaL_error(L,"Font \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::SetAnimationState(lua_State * L)
{
	lstgAnimation * pani;
	if((pani=_lstg->ani[1].find(luaL_checkstring(L,1)))||(pani=_lstg->ani[0].find(luaL_checkstring(L,1))))
	{
		pani->quad.blend=TranslateBlendMode(L,2);
		if(lua_gettop(L)==3)
		{
			pani->quad.v[0].col=*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME));
			pani->quad.v[1].col=*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME));
			pani->quad.v[2].col=*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME));
			pani->quad.v[3].col=*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME));
		}
		else if(lua_gettop(L)==6)
		{
			pani->quad.v[0].col=*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME));
			pani->quad.v[1].col=*((DWORD *)luaL_checkudata(L,4,COLOR_TYPENAME));
			pani->quad.v[2].col=*((DWORD *)luaL_checkudata(L,5,COLOR_TYPENAME));
			pani->quad.v[3].col=*((DWORD *)luaL_checkudata(L,6,COLOR_TYPENAME));
		}
	}
	else
		luaL_error(L,"Animation \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::SetImageCenter(lua_State *L)
{
	lstgImage * pimg;
	if((pimg=_lstg->img[1].find(luaL_checkstring(L,1)))||(pimg=_lstg->img[0].find(luaL_checkstring(L,1))))
		pimg->SetHotSpot(luaL_checknumber(L,2),luaL_checknumber(L,3));
	else
		luaL_error(L,"Image \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::SetAnimationCenter(lua_State *L)
{
	lstgAnimation * pani;
	if((pani=_lstg->ani[1].find(luaL_checkstring(L,1)))||(pani=_lstg->ani[0].find(luaL_checkstring(L,1))))
	{
		pani->hotX=luaL_checknumber(L,2);
		pani->hotY=luaL_checknumber(L,3);
	}
	else
		luaL_error(L,"Animation \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::SetFog(lua_State *L)
{
	if(lua_gettop(L)==3)
		_lstg->hge->Gfx_SetFog((float)luaL_checknumber(L,1),(float)luaL_checknumber(L,2),*((DWORD *)luaL_checkudata(L,3,COLOR_TYPENAME)));
	else if(lua_gettop(L)==2)
		_lstg->hge->Gfx_SetFog((float)luaL_checknumber(L,1),(float)luaL_checknumber(L,2),0x00FFFFFF);
	else
		_lstg->hge->Gfx_SetFog(0.0f,0.0f,0x00FFFFFF);
	return 0;
}
int BIF::ParticleStop(lua_State *L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,2));
	lua_pop(L,1);
	if(pobj) pobj->fireps=0;
	return 0;
}
int BIF::ParticleFire(lua_State *L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,2));
	lua_pop(L,1);
	if(pobj) pobj->fireps=1;
	return 0;
}
int BIF::ParticleGetn(lua_State *L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,2));
	lua_pop(L,1);
	if(pobj&&pobj->pps) lua_pushnumber(L,pobj->pps->GetParticlesAlive());
	else lua_pushnumber(L,0);
	return 1;
}
int BIF::ParticleGetEmission(lua_State *L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,2));
	lua_pop(L,1);
	if(pobj&&pobj->pps) lua_pushnumber(L,pobj->pps->info.nEmission);
	else lua_pushnumber(L,0);
	return 1;
}
int BIF::ParticleSetEmission(lua_State *L)
{
	lua_rawgeti(L,1,2);
	lstgobj * pobj=_lstg->obj.ptr(luaL_checkint(L,3));
	lua_pop(L,1);
	if(pobj&&pobj->pps)
	{
		lua_pushnumber(L,pobj->pps->info.nEmission=max(luaL_checknumber(L,2),0));
	}
	return 0;
}
int BIF::Snapshot(lua_State *L)
{
	_lstg->hge->System_Snapshot(luaL_checkstring(L,1));
	return 0;
}
int BIF::PlaySound_(lua_State *L)
{
	lstgSound * psnd;
	if((psnd=_lstg->snd[1].find(luaL_checkstring(L,1)))||(psnd=_lstg->snd[0].find(luaL_checkstring(L,1))))
		psnd->play(luaL_checknumber(L,2),luaL_optnumber(L,3,0.0));
	else
		luaL_error(L,"Sound \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::PlayMusic(lua_State *L)
{
	lstgBGM * pbgm;
	if((pbgm=_lstg->bgm[1].find(luaL_checkstring(L,1)))||(pbgm=_lstg->bgm[0].find(luaL_checkstring(L,1))))
		pbgm->play(luaL_optnumber(L,2,1.0),luaL_optnumber(L,3,0.0));
	else
		luaL_error(L,"Music \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::StopMusic(lua_State *L)
{
	lstgBGM * pbgm;
	if((pbgm=_lstg->bgm[1].find(luaL_checkstring(L,1)))||(pbgm=_lstg->bgm[0].find(luaL_checkstring(L,1))))
		pbgm->stop();
	else
		luaL_error(L,"Music \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::PauseMusic(lua_State *L)
{
	lstgBGM * pbgm;
	if((pbgm=_lstg->bgm[1].find(luaL_checkstring(L,1)))||(pbgm=_lstg->bgm[0].find(luaL_checkstring(L,1))))
		pbgm->pause();
	else
		luaL_error(L,"Music \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::ResumeMusic(lua_State *L)
{
	lstgBGM * pbgm;
	if((pbgm=_lstg->bgm[1].find(luaL_checkstring(L,1)))||(pbgm=_lstg->bgm[0].find(luaL_checkstring(L,1))))
		pbgm->resume();
	else
		luaL_error(L,"Music \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::GetMusicState(lua_State *L)
{
	lstgBGM * pbgm;
	if((pbgm=_lstg->bgm[1].find(luaL_checkstring(L,1)))||(pbgm=_lstg->bgm[0].find(luaL_checkstring(L,1))))
	{
		if(pbgm->ch)
		{
			if(pbgm->paused) lua_pushstring(L,"paused");
			else lua_pushstring(L,"playing");
			lua_pushnumber(L,_lstg->hge->Channel_GetPos(pbgm->ch));
			return 2;
		}
		else
		{
			lua_pushstring(L,"stopped");
				return 1;
		}
	}
	else
		luaL_error(L,"Music \'%s\' not found",luaL_checkstring(L,1));
	return 0;
}
int BIF::UpdateSound(lua_State *L)
{
	for(lstgSound * psnd=_lstg->snd[0].begin();psnd!=0;psnd=_lstg->snd[0].next())
		psnd->update();
	for(lstgSound * psnd=_lstg->snd[1].begin();psnd!=0;psnd=_lstg->snd[1].next())
		psnd->update();
	for(lstgBGM * pbgm=_lstg->bgm[0].begin();pbgm!=0;pbgm=_lstg->bgm[0].next())
		pbgm->update();
	for(lstgBGM * pbgm=_lstg->bgm[1].begin();pbgm!=0;pbgm=_lstg->bgm[1].next())
		pbgm->update();
	return 0;
}
int BIF::SetSEVolume(lua_State *L)
{
	_lstg->se_volume=luaL_checkint(L,1);
	return 0;
}
int BIF::SetBGMVolume(lua_State *L)
{
	_lstg->bgm_volume=luaL_checkint(L,1);
	return 0;
}
int BIF::GetKeyState(lua_State *L)
{
	lua_pushboolean(L,_lstg->hge->Input_GetKeyState(luaL_checkint(L,1)));
	return 1;
}
int BIF::GetLastKey(lua_State *L)
{
	lua_pushinteger(L,_lstg->hge->Input_GetKey());
	return 1;
}
int BIF::GetLastChar(lua_State *L)
{
	lua_pushinteger(L,_lstg->hge->Input_GetChar());
	return 1;
}
int BIF::Angle(lua_State *L)
{
	if(lua_gettop(L)==2)
	{
		if((!lua_istable(L,1))||(!lua_istable(L,2))) luaL_error(L,"Invalid lstg object.");
		lua_rawgeti(L,1,2);
		int i=lua_tointeger(L,-1);
		lua_rawgeti(L,2,2);
		int j=lua_tointeger(L,-1);
		lstgobj * pobj1=_lstg->obj.ptr(i);
		lstgobj * pobj2=_lstg->obj.ptr(j);
		if(pobj1&&pobj2)
			lua_pushnumber(L,RAD2DEGREE*atan2(pobj2->y-pobj1->y,pobj2->x-pobj1->x));
		else luaL_error(L,"Invalid lstg object.");
	}
	else
	{
		lua_pushnumber(L,RAD2DEGREE*atan2(luaL_checknumber(L,4)-luaL_checknumber(L,2),luaL_checknumber(L,3)-luaL_checknumber(L,1)));
	}
	return 1;
}
int BIF::Dist(lua_State *L)
{
	if(lua_gettop(L)==2)
	{
		if((!lua_istable(L,1))||(!lua_istable(L,2))) luaL_error(L,"Invalid lstg object.");
		lua_rawgeti(L,1,2);
		int i=lua_tointeger(L,-1);
		lua_rawgeti(L,2,2);
		int j=lua_tointeger(L,-1);
		lstgobj * pobj1=_lstg->obj.ptr(i);
		lstgobj * pobj2=_lstg->obj.ptr(j);
		if(pobj1&&pobj2)
		{
			lua_Number dx,dy;
			dx=pobj2->x-pobj1->x;
			dy=pobj2->y-pobj1->y;
			lua_pushnumber(L,sqrt(dx*dx+dy*dy));
		}
		else luaL_error(L,"Invalid lstg object.");
	}
	else
	{
		lua_Number dx,dy;
		dx=luaL_checknumber(L,3)-luaL_checknumber(L,1);
		dy=luaL_checknumber(L,4)-luaL_checknumber(L,2);
		lua_pushnumber(L,sqrt(dx*dx+dy*dy));
	}
	return 1;
}
int BIF::ObjTable(lua_State * L)
{
	lua_pushlightuserdata(L,(void *)_lstg);
	lua_gettable(L,LUA_REGISTRYINDEX);
	return 1;
}
int BIF::Registry(lua_State * L)
{
	lua_pushvalue(L,LUA_REGISTRYINDEX);
	return 1;
}

DWORD * Color::Push(lua_State *L)
{
	DWORD * ud=(DWORD *)lua_newuserdata(L,sizeof(DWORD));
	luaL_getmetatable(L,COLOR_TYPENAME);
	lua_setmetatable(L,-2);
	return ud;
}
int Color::New(lua_State *L)
{
	DWORD * ud=Color::Push(L);
	if(lua_gettop(L)==2)
		* ud=(DWORD)luaL_checknumber(L,1);
	else
		* ud=ARGB(max(min(luaL_checkint(L,1),255),0),max(min(luaL_checkint(L,2),255),0),max(min(luaL_checkint(L,3),255),0),max(min(luaL_checkint(L,4),255),0));
	return 1;
}
int Color::ToARGB(lua_State *L)
{
	DWORD * ud=(DWORD *)luaL_checkudata(L,1,COLOR_TYPENAME);
	lua_pushnumber(L,GETA(*ud));
	lua_pushnumber(L,GETR(*ud));
	lua_pushnumber(L,GETG(*ud));
	lua_pushnumber(L,GETB(*ud));
	return 4;
}
int Color::Eq(lua_State *L)
{
	DWORD * lhs=(DWORD *)luaL_checkudata(L,1,COLOR_TYPENAME);
	DWORD * rhs=(DWORD *)luaL_checkudata(L,2,COLOR_TYPENAME);
	lua_pushboolean(L,(*lhs)==(*rhs));
	return 1;
}
int Color::Add(lua_State *L)
{
	DWORD * lhs=(DWORD *)luaL_checkudata(L,1,COLOR_TYPENAME);
	DWORD * rhs=(DWORD *)luaL_checkudata(L,2,COLOR_TYPENAME);
	DWORD * result=Color::Push(L);
	* result=ARGB(min(GETA(*lhs)+GETA(*rhs),255),min(GETR(*lhs)+GETR(*rhs),255),min(GETG(*lhs)+GETG(*rhs),255),min(GETB(*lhs)+GETB(*rhs),255));
	return 1;
}
int Color::Mul(lua_State *L)
{
	DWORD * c;
	lua_Number n;
	if(lua_isnumber(L,1))
	{
		n=luaL_checknumber(L,1);
		c=(DWORD *)luaL_checkudata(L,2,COLOR_TYPENAME);
	}
	else
	{
		n=luaL_checknumber(L,2);
		c=(DWORD *)luaL_checkudata(L,1,COLOR_TYPENAME);
	}
	DWORD * result=Color::Push(L);
	* result=ARGB((DWORD)min(GETA(*c)*n,255),(DWORD)min(GETR(*c)*n,255),(DWORD)min(GETG(*c)*n,255),(DWORD)min(GETB(*c)*n,255));
	return 1;
}
int Color::ToString(lua_State *L)
{
	DWORD * ud=(DWORD *)luaL_checkudata(L,1,COLOR_TYPENAME);
	lua_pushfstring(L,"lstg.Color(%d,%d,%d,%d)",GETA(*ud),GETR(*ud),GETG(*ud),GETB(*ud));
	return 1;
}
void Color::reg(lua_State *L)
{
	luaL_Reg methods[]=
	{
		{"ARGB",&Color::ToARGB},
		{NULL,NULL}
	};
	luaL_Reg meta[]=
	{
		{"__eq",&Color::Eq},
		{"__add",&Color::Add},
		{"__mul",&Color::Mul},
		{"__tostring",&Color::ToString},
		{NULL,NULL}
	};
	luaL_openlib(L,COLOR_TYPENAME,methods,0);
	luaL_newmetatable(L,COLOR_TYPENAME);
	luaL_openlib(L,0,meta,0);
	lua_pushliteral(L,"__index");
	lua_pushvalue(L,-3);
	lua_rawset(L,-3);
	lua_pushliteral(L,"__metatable");
	lua_pushvalue(L,-3);
	lua_rawset(L,-3);
	lua_pop(L,2);
}

rand_gen * RandGen::Push(lua_State *L)
{
	rand_gen * ud=(rand_gen *)lua_newuserdata(L,sizeof(rand_gen));
	luaL_getmetatable(L,RANDGEN_TYPENAME);
	lua_setmetatable(L,-2);
	return ud;
}
int RandGen::New(lua_State *L)
{
	rand_gen * ud=RandGen::Push(L);
	ud->Seed(0);
	return 1;
}
int RandGen::Seed(lua_State *L)
{
	rand_gen * ud=(rand_gen *)luaL_checkudata(L,1,RANDGEN_TYPENAME);
	ud->Seed(unsigned int(luaL_checknumber(L,2)));
	return 0;
}
int RandGen::Int(lua_State *L)
{
	rand_gen * ud=(rand_gen *)luaL_checkudata(L,1,RANDGEN_TYPENAME);
	lua_pushinteger(L,ud->Int((int)luaL_checknumber(L,2),(int)luaL_checknumber(L,3)));
	return 1;
}
int RandGen::Float(lua_State *L)
{
	rand_gen * ud=(rand_gen *)luaL_checkudata(L,1,RANDGEN_TYPENAME);
	lua_pushnumber(L,ud->Float((float)luaL_checknumber(L,2),(float)luaL_checknumber(L,3)));
	return 1;
}
int RandGen::Sign(lua_State *L)
{
	rand_gen * ud=(rand_gen *)luaL_checkudata(L,1,RANDGEN_TYPENAME);
	lua_pushinteger(L,ud->Sign());
	return 1;
}
int RandGen::ToString(lua_State *L)
{
	rand_gen * ud=(rand_gen *)luaL_checkudata(L,1,RANDGEN_TYPENAME);
	lua_pushfstring(L,"lstg.Rand object");
	return 1;
}
void RandGen::reg(lua_State *L)
{
	luaL_Reg methods[]=
	{
		{"Seed",&RandGen::Seed},
		{"Int",&RandGen::Int},
		{"Float",&RandGen::Float},
		{"Sign",&RandGen::Sign},
		{NULL,NULL}
	};
	luaL_Reg meta[]=
	{
		{"__tostring",&RandGen::ToString},
		{NULL,NULL}
	};
	luaL_openlib(L,RANDGEN_TYPENAME,methods,0);
	luaL_newmetatable(L,RANDGEN_TYPENAME);
	luaL_openlib(L,0,meta,0);
	lua_pushliteral(L,"__index");
	lua_pushvalue(L,-3);
	lua_rawset(L,-3);
	lua_pushliteral(L,"__metatable");
	lua_pushvalue(L,-3);
	lua_rawset(L,-3);
	lua_pop(L,2);
}

bool RenderPrio(unsigned int i,unsigned int j)
{
        lstgobj * pobj1;
        lstgobj * pobj2;
        pobj1=_lstg->obj.ptr(i);
        pobj2=_lstg->obj.ptr(j);
		return (pobj1->layer<pobj2->layer)||((pobj1->layer==pobj2->layer)&&(pobj1->uniq_id<pobj2->uniq_id));
}
bool FramePrio(unsigned int i,unsigned int j)
{
        lstgobj * pobj1;
        lstgobj * pobj2;
        pobj1=_lstg->obj.ptr(i);
        pobj2=_lstg->obj.ptr(j);
		return pobj1->uniq_id<pobj2->uniq_id;
}

bool colli_check(lstgobj * o1,lstgobj * o2)
{
	static double a,b,r,l,dx,dy,x,y;
	if((!o1->colli)||(!o2->colli)) return false;
	a=o2->a;
	b=o2->b;
	r=o1->a;
	l=a+b+r;
	dx=o2->x-o1->x;
	dy=o2->y-o1->y;
	if(fabs(dx)>l||fabs(dy)>l)
		return false;
	x= dx*cos(o1->r)+dy*sin(o1->r);
    y=-dx*sin(o1->r)+dy*cos(o1->r);
    a+=r;
    b+=r;
    a=a*a;b=b*b;
    x=x*x;y=y*y;
    if(o2->rect) return (x<a && y<b);
    else return ((x*b+y*a)<a*b);
}

void print_stack(lua_State * L)
{
	for(int i=1;i<=lua_gettop(L);i++)
		_lstg->Log("%s,",lua_typename(L,lua_type(L,i)));
	_lstg->Log("\n");
}