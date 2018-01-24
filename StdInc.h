#ifndef _STDINC_H_
#define _STDINC_H_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define CINTERFACE
#include <d3d9.h>

#define WINEXP	__declspec(dllexport)

#define DEGTORAD(x) \
	((x) * (rwPI / 180.0f))
#define RADTODEG(x) \
	((x) * (180.0f / rwPI))

#include "CCamera.h"
#include "CClouds.h"
#include "CDraw.h"
#include "CGame.h"
#include "CMatrix.h"
#include "CMatrixLink.h"
#include "CPlaceable.h"
#include "CPostEffects.h"
#include "CRGBA.h"
#include "CSimpleTransform.h"
#include "CTimeCycle.h"
#include "CVector.h"
#include "CVector2D.h"
#include "CWeather.h"
#include "RenderWare.h"

#define _DoRWStuffStartOfFrame_Horizon	0x0053D7A0
//extern void (__cdecl *const DoRWStuffStartOfFrame_Horizon)(void);
#define _LittleTest						0x00541330
extern void (__cdecl *const LittleTest)(void);

WINEXP void CreateShaders(void);
WINEXP void DeleteShaders(void);
WINEXP CVector operator-(const CVector &rhs);

#define _g_TheCamera					0x00B6F028
extern CCamera *const g_TheCamera;
#define _g_uiTempBufferVerticesStored	0x00C4B950
extern RwUInt32 *const g_uiTempBufferVerticesStored;
#define _g_iTempBufferIndicesStored		0x00C4B954
extern RwInt32 *const g_iTempBufferIndicesStored;
#define _g_aTempRenderIndexList			0x00C4B958
extern RwImVertexIndex (*const g_aTempRenderIndexList)[4096];
#define _g_aTempVertexBuffer			0x00C4D958
extern RwIm3DVertex (*const g_aTempVertexBuffer)[2048];

extern WINEXP const RwUInt32 g_aVSSkyGradAsm[];
extern WINEXP const RwUInt32 g_aPSSkyGradAsm[];

#endif //_STDINC_H_
