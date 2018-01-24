#include "CVector.h"

#ifndef _CCLOUDS_H_
#define _CCLOUDS_H_

// Prevent blocky sky gradients if defined.
#define SKYP_SMOOTH_GRADIENT

#define SKYP_ABOVE_HORIZON_Z	0.5f
#define SKYP_HORIZON_Z			0.0f
#define SKYP_SEA_HORIZON_Z		-0.1f
#define SKYP_BELOW_HORIZON_Z	-0.3f

//#define SKYP_WIDTH_MULT	1.4f
#define SKYP_SQ_DIST	1.25f	// 1.0f + pow(max(SKYP_ABOVE_HORIZON_Z, -SKYP_BELOW_HORIZON_Z), 2.0f)
#define SKYP_CAM_DIST	30.0f

class CClouds
{
public:
	struct Vtbl
	{
#define _CClouds__SetUpOneSkyPoly			0x00713060
		static void (__cdecl *const SetUpOneSkyPoly)(CVector topLeft, CVector topRight, CVector botLeft, CVector botRight, unsigned char ucTopRed, unsigned char ucTopGreen, unsigned char ucTopBlue, unsigned char ucBotRed, unsigned char ucBotGreen, unsigned char ucBotBlue);
/*#define _CClouds__RenderSkyPolys			0x00714650
		static void (__cdecl *const RenderSkyPolys)(void);*/
#define _CClouds__RenderOutGeometryBuffer	0x00722150
		static void (__cdecl *const RenderOutGeometryBuffer)(void);
	};

	static void SetUpOneSkyPoly(CVector topLeft, CVector topRight, CVector botLeft, CVector botRight, unsigned char ucTopRed, unsigned char ucTopGreen, unsigned char ucTopBlue, unsigned char ucBotRed, unsigned char ucBotGreen, unsigned char ucBotBlue);
	static void RenderOutGeometryBuffer(void);

	WINEXP static void SetUpNthSkyPoly(CVector botLeft, CVector botRight, unsigned char ucBotRed, unsigned char ucBotGreen, unsigned char ucBotBlue);
	WINEXP static void FixUpOneSkyPoly(float fTopLeftU, float fTopLeftV, float fTopRightU, float fTopRightV, float fBotLeftU, float fBotLeftV, float fBotRightU, float fBotRightV);
	WINEXP static void FixUpNthSkyPoly(float fBotLeftU, float fBotLeftV, float fBotRightU, float fBotRightV);
	WINEXP static void RenderSkyPolys(void);
};

#endif //_CCLOUDS_H_
