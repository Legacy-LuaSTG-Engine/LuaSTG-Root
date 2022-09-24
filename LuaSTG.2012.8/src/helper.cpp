#include "helper.h"
#include "lstg.h"

lstgTexture::lstgTexture(const char *filename,int mipmap)
{
	tex=_lstg->hge->Texture_Load(filename,0,mipmap);
}

lstgTexture::~lstgTexture()
{
	_lstg->hge->Texture_Free(tex);
}

void lstgImage::Render4V(float x0,float y0,float z0,
				float x1,float y1,float z1,
				float x2,float y2,float z2,
				float x3,float y3,float z3)
{
	quad.v[0].x = x0; quad.v[0].y = y0; quad.v[0].z = z0;
	quad.v[1].x = x1; quad.v[1].y = y1; quad.v[1].z = z1;
	quad.v[2].x = x2; quad.v[2].y = y2; quad.v[2].z = z2;
	quad.v[3].x = x3; quad.v[3].y = y3; quad.v[3].z = z3;

	hge->Gfx_RenderQuad(&quad);
}

lstgAnimation::lstgAnimation(lstgTexture * ptex,float x,float y,float w,float h,int n,int m,int intv,float a,float b,bool rect)
{
	x+=0.5f;y+=0.5f;
	_a=a;_b=b;_rect=rect;
	quad.tex=ptex->tex;
	float tex_width,tex_height;
	if(quad.tex)
	{
		tex_width=(float)_lstg->hge->Texture_GetWidth(quad.tex);
		tex_height=(float)_lstg->hge->Texture_GetHeight(quad.tex);
	}
	else
	{
		tex_width=1.0f;
		tex_height=1.0f;
	}
	tx=x/tex_width;ty=y/tex_height;
	tw=w/tex_width;th=h/tex_height;
	width=w;height=h;
	hotX=w*0.5;hotY=h*0.5;
	_n=max(n,1),_m=max(m,1);_intv=max(intv,1);
	quad.blend=BLEND_DEFAULT;
	quad.v[0].z=quad.v[1].z=quad.v[2].z=quad.v[3].z=0.5f;
	quad.v[0].col=quad.v[1].col=quad.v[2].col=quad.v[3].col=0xffffffff;
}

void lstgAnimation::RenderEx(int n, float x, float y, float rot, float hscale, float vscale)
{
	float texx1,texx2,texy1,texy2;
	float tx1, ty1, tx2, ty2;
	float sint, cost;

	if(vscale==0) vscale=hscale;

	tx1 = -hotX*hscale;
	ty1 = (height-hotY)*vscale;
	tx2 = (width-hotX)*hscale;
	ty2 = -hotY*vscale;

	if (rot != 0.0f)
	{
		cost = cosf(rot);
		sint = sinf(rot);
			
		quad.v[0].x  = tx1*cost - ty1*sint + x;
		quad.v[0].y  = tx1*sint + ty1*cost + y;	

		quad.v[1].x  = tx2*cost - ty1*sint + x;
		quad.v[1].y  = tx2*sint + ty1*cost + y;	

		quad.v[2].x  = tx2*cost - ty2*sint + x;
		quad.v[2].y  = tx2*sint + ty2*cost + y;	

		quad.v[3].x  = tx1*cost - ty2*sint + x;
		quad.v[3].y  = tx1*sint + ty2*cost + y;	
	}
	else
	{
		quad.v[0].x = tx1 + x; quad.v[0].y = ty1 + y;
		quad.v[1].x = tx2 + x; quad.v[1].y = ty1 + y;
		quad.v[2].x = tx2 + x; quad.v[2].y = ty2 + y;
		quad.v[3].x = tx1 + x; quad.v[3].y = ty2 + y;
	}

	n=(n/_intv)%(_n*_m);
	texx1=tx+tw*(n%_n);
	texy1=ty+th*(n/_n);
	texx2=texx1+tw;
	texy2=texy1+th;
	quad.v[0].tx = texx1; quad.v[0].ty = texy1;
	quad.v[1].tx = texx2; quad.v[1].ty = texy1;
	quad.v[2].tx = texx2; quad.v[2].ty = texy2;
	quad.v[3].tx = texx1; quad.v[3].ty = texy2;

	_lstg->hge->Gfx_RenderQuad(&quad);
}

lstgPSI::lstgPSI(const char * filename, lstgImage * pimg,float a,float b,bool rect)
{
	DWORD sz;
	psi=(hgeParticleSystemInfo *)_lstg->hge->Resource_Load(filename,&sz);
	if(sz!=sizeof(hgeParticleSystemInfo)) _lstg->Err("Invalid psi file \'%s\'",filename);
	spr=new hgeSprite(* (hgeSprite *)pimg);
	spr->SetBlendMode((((DWORD)(psi->sprite))>>16)&0x00000003);
	_a=a;_b=b;_rect=rect;
	psi->sprite=spr;
}

lstgPSI::~lstgPSI(){_lstg->hge->Resource_Free(psi);delete spr;}

lstgSound::lstgSound(const char *filename)
{
	ch=0;
	v=0.0;
	se=_lstg->hge->Effect_Load(filename);
}
lstgSound::~lstgSound()
{
	if(ch) _lstg->hge->Channel_Stop(ch);
	_lstg->hge->Effect_Free(se);
}
void lstgSound::play(double volume, double pan)
{
	v+=exp(volume*SOUND_MIX);
	p+=pan*exp(volume*SOUND_MIX);
}
void lstgSound::update()
{
	if(v>0.0)
	{
		if(_lstg->hge->Channel_IsPlaying(ch))
		{
			_lstg->hge->Channel_SetPos(ch,0);
			_lstg->hge->Channel_SetVolume(ch,int(_lstg->se_volume*log(v)/SOUND_MIX));
			_lstg->hge->Channel_SetPanning(ch,int(100*p/v));
		}
		else
		ch=_lstg->hge->Effect_PlayEx(se,int(_lstg->se_volume*log(v)/SOUND_MIX),int(100*p/v));
	}
	v=0.0;
	p=0.0;
}

lstgBGM::lstgBGM(const char *filename, double end, double loop)
{
	se=_lstg->hge->Effect_Load(filename);
	_end=end;_loop=loop;
	ch=0;
	paused=false;
}
lstgBGM::~lstgBGM()
{
	if(ch) _lstg->hge->Channel_Stop(ch);
	_lstg->hge->Effect_Free(se);
}
void lstgBGM::play(float volume,float pos)
{
	stop();
	ch=_lstg->hge->Effect_PlayEx(se,int(_lstg->bgm_volume*volume));
	_lstg->hge->Channel_SetPos(ch,pos);
	paused=false;
}
void lstgBGM::stop()
{
	if(ch)
	{
		_lstg->hge->Channel_SlideTo(ch,1.0,0);
		ch=0;
	}
}
void lstgBGM::update()
{
	if(ch)
	{
		float pos=_lstg->hge->Channel_GetPos(ch);
		if(pos>_end) _lstg->hge->Channel_SetPos(ch,pos-_loop);
	}
}
void lstgBGM::pause()
{
	if(ch&&(!paused)){_lstg->hge->Channel_Pause(ch);paused=true;}
}
void lstgBGM::resume()
{
	if(ch&&paused){_lstg->hge->Channel_Resume(ch);paused=false;}
}

lstgTTF::lstgTTF(const char *fontname, LONG width, LONG height, LONG weight, LONG deco, LONG charset)
{
	font=_lstg->hge->TTF_Load(fontname,width,height, weight, deco, charset);
}

lstgTTF::~lstgTTF()
{
	_lstg->hge->TTF_Free(font);
}