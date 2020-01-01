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

#include "Game/CCamera.h"
#include "Game/CClouds.h"
#include "Game/CDraw.h"
#include "Game/CGame.h"
#include "Game/CMatrix.h"
#include "Game/CMatrixLink.h"
#include "Game/CPlaceable.h"
#include "Game/CPostEffects.h"
#include "Game/CRGBA.h"
#include "Game/CSimpleTransform.h"
#include "Game/CTimeCycle.h"
#include "Game/CVector.h"
#include "Game/CVector2D.h"
#include "Game/CWeather.h"
#include "Game/RenderWare.h"

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

extern void GetTimeCycleColours();

#endif //_STDINC_H_
