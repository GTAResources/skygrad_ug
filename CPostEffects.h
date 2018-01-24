#include "RenderWare.h"

#ifndef _CPOSTEFFECTS_H_
#define _CPOSTEFFECTS_H_

//#define POSTFX_DEBUG_GRID

#define POSTFX_GRAIN_SIZE	256

class CPostEffects
{
public:
	struct Vtbl
	{
#define _CPostEffects__Close		0x007010C0
		static void (__cdecl *const Close)(void);
#define _CPostEffects__Initialise	0x00704630
		static void (__cdecl *const Initialise)(void);
	};

#define _CPostEffects__ms_pGrainRaster	0x00C402B0
	static RwRaster **const ms_pGrainRaster;

	WINEXP static RwRaster *ms_pGrainRaster8;
#ifdef POSTFX_DEBUG_GRID
	WINEXP static RwRaster *ms_pGridRaster;
#endif
	WINEXP static void *ms_pVSSkyGrad;
	WINEXP static void *ms_pPSSkyGrad;

	static void Close(void);
	static void Initialise(void);

	WINEXP static void CreateGrainRaster(void);
};

#endif //_CPOSTEFFECTS_H_
