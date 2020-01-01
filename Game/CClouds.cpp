#include "../StdInc.h"

void (__cdecl *const CClouds::Vtbl::SetUpOneSkyPoly)(CVector topLeft, CVector topRight, CVector botLeft, CVector botRight, unsigned char ucTopRed, unsigned char ucTopGreen, unsigned char ucTopBlue, unsigned char ucBotRed, unsigned char ucBotGreen, unsigned char ucBotBlue) = (decltype(SetUpOneSkyPoly))_CClouds__SetUpOneSkyPoly;
void (__cdecl *const CClouds::Vtbl::RenderOutGeometryBuffer)(void) = (decltype(RenderOutGeometryBuffer))_CClouds__RenderOutGeometryBuffer;

inline void CClouds::SetUpOneSkyPoly(CVector topLeft, CVector topRight, CVector botLeft, CVector botRight, unsigned char ucTopRed, unsigned char ucTopGreen, unsigned char ucTopBlue, unsigned char ucBotRed, unsigned char ucBotGreen, unsigned char ucBotBlue)
{
	Vtbl::SetUpOneSkyPoly(topLeft, topRight, botLeft, botRight, ucTopRed, ucTopGreen, ucTopBlue, ucBotRed, ucBotGreen, ucBotBlue);
}

inline void CClouds::RenderOutGeometryBuffer(void)
{
	Vtbl::RenderOutGeometryBuffer();
}

void CClouds::SetUpNthSkyPoly(CVector botLeft, CVector botRight, unsigned char ucBotRed, unsigned char ucBotGreen, unsigned char ucBotBlue)
{
	unsigned int uiStartVertex, uiColor;
	int iStartIndex;

	uiStartVertex = *g_uiTempBufferVerticesStored;
	iStartIndex = *g_iTempBufferIndicesStored;

	(*g_aTempRenderIndexList)[iStartIndex + 0] = uiStartVertex - 2;
	(*g_aTempRenderIndexList)[iStartIndex + 1] = uiStartVertex + 0;
	(*g_aTempRenderIndexList)[iStartIndex + 2] = uiStartVertex - 1;
	(*g_aTempRenderIndexList)[iStartIndex + 3] = uiStartVertex - 1;
	(*g_aTempRenderIndexList)[iStartIndex + 4] = uiStartVertex + 0;
	(*g_aTempRenderIndexList)[iStartIndex + 5] = uiStartVertex + 1;

	uiColor = 0xFF000000 | (ucBotRed << 16) | (ucBotGreen << 8) | ucBotBlue;

	(*g_aTempVertexBuffer)[uiStartVertex + 0].objVertex = botLeft.m_rw;
	(*g_aTempVertexBuffer)[uiStartVertex + 0].color = uiColor;
	(*g_aTempVertexBuffer)[uiStartVertex + 0].u = 0.0f;
	(*g_aTempVertexBuffer)[uiStartVertex + 0].v = 0.0f;

	(*g_aTempVertexBuffer)[uiStartVertex + 1].objVertex = botRight.m_rw;
	(*g_aTempVertexBuffer)[uiStartVertex + 1].color = uiColor;
	(*g_aTempVertexBuffer)[uiStartVertex + 1].u = 0.0f;
	(*g_aTempVertexBuffer)[uiStartVertex + 1].v = 0.0f;

	*g_uiTempBufferVerticesStored += 2;
	*g_iTempBufferIndicesStored += 6;
}

void CClouds::FixUpOneSkyPoly(float fTopLeftU, float fTopLeftV, float fTopRightU, float fTopRightV, float fBotLeftU, float fBotLeftV, float fBotRightU, float fBotRightV)
{
	unsigned int uiThisVertex = *g_uiTempBufferVerticesStored;

	(*g_aTempVertexBuffer)[uiThisVertex - 4].u = fTopLeftU;
	(*g_aTempVertexBuffer)[uiThisVertex - 4].v = fTopLeftV;
	(*g_aTempVertexBuffer)[uiThisVertex - 3].u = fTopRightU;
	(*g_aTempVertexBuffer)[uiThisVertex - 3].v = fTopRightV;
	(*g_aTempVertexBuffer)[uiThisVertex - 2].u = fBotLeftU;
	(*g_aTempVertexBuffer)[uiThisVertex - 2].v = fBotLeftV;
	(*g_aTempVertexBuffer)[uiThisVertex - 1].u = fBotRightU;
	(*g_aTempVertexBuffer)[uiThisVertex - 1].v = fBotRightV;
}

void CClouds::FixUpNthSkyPoly(float fBotLeftU, float fBotLeftV, float fBotRightU, float fBotRightV)
{
	unsigned int uiThisVertex = *g_uiTempBufferVerticesStored;

	(*g_aTempVertexBuffer)[uiThisVertex - 2].u = fBotLeftU;
	(*g_aTempVertexBuffer)[uiThisVertex - 2].v = fBotLeftV;
	(*g_aTempVertexBuffer)[uiThisVertex - 1].u = fBotRightU;
	(*g_aTempVertexBuffer)[uiThisVertex - 1].v = fBotRightV;
}

void CClouds::RenderSkyPolys(void)
{
	CMatrixLink *pMatrixLink;
	CVector pos, norm, invNorm, aVertices[4];
	CVector2D scale, aPos2D[4];
	float fHeading, fWidthMult, fHeightMult, fBlendFactor, aPosZ[6];
	CRGBA belowHorizonGrey;

	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, false);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, false);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, false);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, false);
	RwRenderStateSet(rwRENDERSTATECULLMODE, rwCULLMODECULLNONE);

	*g_uiTempBufferVerticesStored = 0;
	*g_iTempBufferIndicesStored = 0;

	if(pMatrixLink = g_TheCamera->m_placeable.m_pMatrix)
	{
		pos = pMatrixLink->m_matrix.m_pos;
		norm.m_fX = pMatrixLink->m_matrix.m_up.m_fX;
		norm.m_fY = pMatrixLink->m_matrix.m_up.m_fY;
	}
	else
	{
		pos = g_TheCamera->m_placeable.m_placement.m_translate;
		fHeading = g_TheCamera->m_placeable.m_placement.m_fHeading;
		norm.m_fX = -sinf(fHeading);
		norm.m_fY = cosf(fHeading);
	}

	norm.m_fZ = 0.0f;
	norm.Normalise();

	invNorm = -norm;

#ifndef SKYP_WIDTH_MULT
	fHeightMult = tan(DEGTORAD(*CDraw::ms_fFOV * 0.5f));
	fWidthMult = fHeightMult * SKYP_SQ_DIST;
#else
	fWidthMult = SKYP_WIDTH_MULT;
	fHeightMult = 1.0f;
#endif

	scale.m_fX = norm.m_fY * fWidthMult;
	scale.m_fY = invNorm.m_fX * fWidthMult;

	aPos2D[0].m_fX = pos.m_fX + (invNorm.m_fX - scale.m_fX) * SKYP_CAM_DIST;
	aPos2D[0].m_fY = pos.m_fY + (invNorm.m_fY - scale.m_fY) * SKYP_CAM_DIST;
	aPos2D[1].m_fX = pos.m_fX + (invNorm.m_fX + scale.m_fX) * SKYP_CAM_DIST;
	aPos2D[1].m_fY = pos.m_fY + (invNorm.m_fY + scale.m_fY) * SKYP_CAM_DIST;
	aPos2D[2].m_fX = pos.m_fX + (norm.m_fX - scale.m_fX) * SKYP_CAM_DIST;
	aPos2D[2].m_fY = pos.m_fY + (norm.m_fY - scale.m_fY) * SKYP_CAM_DIST;
	aPos2D[3].m_fX = pos.m_fX + (norm.m_fX + scale.m_fX) * SKYP_CAM_DIST;
	aPos2D[3].m_fY = pos.m_fY + (norm.m_fY + scale.m_fY) * SKYP_CAM_DIST;

	aPosZ[0] = pos.m_fZ + (invNorm.m_fZ + SKYP_ABOVE_HORIZON_Z) * SKYP_CAM_DIST;
	aPosZ[1] = pos.m_fZ + (norm.m_fZ + SKYP_ABOVE_HORIZON_Z) * SKYP_CAM_DIST;
	aPosZ[2] = pos.m_fZ + (norm.m_fZ + SKYP_HORIZON_Z) * SKYP_CAM_DIST;
	aPosZ[3] = pos.m_fZ + (norm.m_fZ + SKYP_SEA_HORIZON_Z) * SKYP_CAM_DIST;
	aPosZ[4] = pos.m_fZ + (norm.m_fZ + SKYP_BELOW_HORIZON_Z) * SKYP_CAM_DIST;
	aPosZ[5] = pos.m_fZ + (invNorm.m_fZ + SKYP_BELOW_HORIZON_Z) * SKYP_CAM_DIST;

	fBlendFactor = (pos.m_fZ - 25.0f) * (1.0f / 80.0f);
	fBlendFactor = fBlendFactor > 1.0f ? 1.0f : (fBlendFactor <= 0.0f ? 0.0f : fBlendFactor);
	fBlendFactor = fBlendFactor <= *CWeather::ms_fFoggyness ? *CWeather::ms_fFoggyness : fBlendFactor;

	belowHorizonGrey = *CTimeCycle::ms_belowHorizonGrey;
	belowHorizonGrey.m_ucRed +=
		(unsigned char)(fBlendFactor * static_cast<float>(CTimeCycle::m_CurrentColours->m_nSkyBottomRed - belowHorizonGrey.m_ucRed));
	belowHorizonGrey.m_ucGreen +=
		(unsigned char)(fBlendFactor * static_cast<float>(CTimeCycle::m_CurrentColours->m_nSkyBottomGreen - belowHorizonGrey.m_ucGreen));
	belowHorizonGrey.m_ucBlue +=
		(unsigned char)(fBlendFactor * static_cast<float>(CTimeCycle::m_CurrentColours->m_nSkyBottomBlue - belowHorizonGrey.m_ucBlue));

#ifdef SKYP_SMOOTH_GRADIENT
	float fMaxSampleU, fMaxSampleV, aSampleV[3];
	RwRaster *pTextureRaster;

	fMaxSampleU = ((float)(*RsGlobal).maximumWidth * SKYP_SQ_DIST) / POSTFX_GRAIN_SIZE;
	fMaxSampleV = ((float)(*RsGlobal).maximumHeight * ((*CDraw::ms_fAspectRatio / fHeightMult) * 0.5f)) / POSTFX_GRAIN_SIZE;

	aSampleV[0] = fMaxSampleV * SKYP_ABOVE_HORIZON_Z;
	aSampleV[1] = aSampleV[0] + (fMaxSampleV * -SKYP_SEA_HORIZON_Z);
	aSampleV[2] = aSampleV[0] + (fMaxSampleV * -SKYP_BELOW_HORIZON_Z);

#ifndef POSTFX_DEBUG_GRID
	pTextureRaster = CPostEffects::ms_pGrainRaster8;
#else
	pTextureRaster = CPostEffects::ms_pGridRaster;
#endif

	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, pTextureRaster);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, rwFILTERNEAREST);

	aVertices[0].m_fX = aPos2D[2].m_fX;
	aVertices[0].m_fY = aPos2D[2].m_fY;
	aVertices[0].m_fZ = aPosZ[1];
	aVertices[1].m_fX = aPos2D[3].m_fX;
	aVertices[1].m_fY = aPos2D[3].m_fY;
	aVertices[1].m_fZ = aPosZ[1];
	aVertices[2].m_fX = aPos2D[2].m_fX;
	aVertices[2].m_fY = aPos2D[2].m_fY;
	aVertices[2].m_fZ = aPosZ[2];
	aVertices[3].m_fX = aPos2D[3].m_fX;
	aVertices[3].m_fY = aPos2D[3].m_fY;
	aVertices[3].m_fZ = aPosZ[2];

	// SkyMid
	SetUpOneSkyPoly
	(
		aVertices[0], aVertices[1],
		aVertices[2], aVertices[3],
#ifndef POSTFX_DEBUG_GRID
		CTimeCycle::m_CurrentColours->m_nSkyTopRed,
		CTimeCycle::m_CurrentColours->m_nSkyTopGreen,
		CTimeCycle::m_CurrentColours->m_nSkyTopBlue,
		CTimeCycle::m_CurrentColours->m_nSkyBottomRed,
		CTimeCycle::m_CurrentColours->m_nSkyBottomGreen,
		CTimeCycle::m_CurrentColours->m_nSkyBottomBlue
#else
		255, 0, 0,
		255, 0, 0
#endif
	);

	FixUpOneSkyPoly(0.0f, 0.0f, fMaxSampleU, 0.0f, 0.0f, aSampleV[0], fMaxSampleU, aSampleV[0]);

	aVertices[2].m_fZ = aPosZ[3];
	aVertices[3].m_fZ = aPosZ[3];

	// SkySeaTop
	SetUpNthSkyPoly
	(
		aVertices[2], aVertices[3],
#ifndef POSTFX_DEBUG_GRID
		CTimeCycle::m_CurrentColours->m_nSkyBottomRed,
		CTimeCycle::m_CurrentColours->m_nSkyBottomGreen,
		CTimeCycle::m_CurrentColours->m_nSkyBottomBlue
#else
		0, 255, 0
#endif
	);

	FixUpNthSkyPoly(0.0f, aSampleV[1], fMaxSampleU, aSampleV[1]);
	
	aVertices[2].m_fZ = aPosZ[4];
	aVertices[3].m_fZ = aPosZ[4];

	// SkySeaBot
	SetUpNthSkyPoly
	(
		aVertices[2], aVertices[3],
#ifndef POSTFX_DEBUG_GRID
		belowHorizonGrey.m_ucRed, belowHorizonGrey.m_ucGreen, belowHorizonGrey.m_ucBlue
#else
		0, 0, 255
#endif
	);

	FixUpNthSkyPoly(0.0f, aSampleV[2], fMaxSampleU, aSampleV[2]);

#ifndef POSTFX_DEBUG_GRID
	_rwD3D9VSCustomWorldMatrix = NULL;
	_rwD3D9CustomVertexShader = CPostEffects::ms_pVSSkyGrad;
	_rwD3D9CustomPixelShader = CPostEffects::ms_pPSSkyGrad;
#endif

	RenderOutGeometryBuffer();

#ifndef POSTFX_DEBUG_GRID
	_rwD3D9CustomVertexShader = NULL;
	_rwD3D9CustomPixelShader = NULL;
#endif

	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, rwFILTERLINEAR);

	aVertices[0].m_fZ = aPosZ[1];
	aVertices[1].m_fZ = aPosZ[1];
	aVertices[2].m_fX = aPos2D[0].m_fX;
	aVertices[2].m_fY = aPos2D[0].m_fY;
	aVertices[2].m_fZ = aPosZ[0];
	aVertices[3].m_fX = aPos2D[1].m_fX;
	aVertices[3].m_fY = aPos2D[1].m_fY;
	aVertices[3].m_fZ = aPosZ[0];

	// SkyTop
	SetUpOneSkyPoly
	(
		aVertices[0], aVertices[1],
		aVertices[2], aVertices[3],
#ifndef POSTFX_DEBUG_GRID
		CTimeCycle::m_CurrentColours->m_nSkyTopRed,
		CTimeCycle::m_CurrentColours->m_nSkyTopGreen,
		CTimeCycle::m_CurrentColours->m_nSkyTopBlue,
		CTimeCycle::m_CurrentColours->m_nSkyTopRed,
		CTimeCycle::m_CurrentColours->m_nSkyTopGreen,
		CTimeCycle::m_CurrentColours->m_nSkyTopBlue
#else
		255, 255, 255,
		255, 255, 255
#endif
	);

	aVertices[0].m_fZ = aPosZ[4];
	aVertices[1].m_fZ = aPosZ[4];
	aVertices[2].m_fZ = aPosZ[5];
	aVertices[3].m_fZ = aPosZ[5];

	// SkyBot
	SetUpOneSkyPoly
	(
		aVertices[0], aVertices[1],
		aVertices[2], aVertices[3],
#ifndef POSTFX_DEBUG_GRID
		belowHorizonGrey.m_ucRed, belowHorizonGrey.m_ucGreen, belowHorizonGrey.m_ucBlue,
		belowHorizonGrey.m_ucRed, belowHorizonGrey.m_ucGreen, belowHorizonGrey.m_ucBlue
#else
		0, 0, 0,
		0, 0, 0
#endif
	);

	RenderOutGeometryBuffer();
#else
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);

	aVertices[0].m_fX = aPos2D[0].m_fX;
	aVertices[0].m_fY = aPos2D[0].m_fY;
	aVertices[0].m_fZ = aPosZ[0];
	aVertices[1].m_fX = aPos2D[1].m_fX;
	aVertices[1].m_fY = aPos2D[1].m_fY;
	aVertices[1].m_fZ = aPosZ[0];
	aVertices[2].m_fX = aPos2D[2].m_fX;
	aVertices[2].m_fY = aPos2D[2].m_fY;
	aVertices[2].m_fZ = aPosZ[1];
	aVertices[3].m_fX = aPos2D[3].m_fX;
	aVertices[3].m_fY = aPos2D[3].m_fY;
	aVertices[3].m_fZ = aPosZ[1];

	// SkyTop
	SetUpOneSkyPoly
	(
		aVertices[0], aVertices[1],
		aVertices[2], aVertices[3],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[36],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[38],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[40],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[36],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[38],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[40]
	);

	aVertices[2].m_fZ = aPosZ[2];
	aVertices[3].m_fZ = aPosZ[2];

	// SkyMid
	SetUpNthSkyPoly
	(
		aVertices[2], aVertices[3],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[42],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[44],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[46]
	);

	aVertices[2].m_fZ = aPosZ[3];
	aVertices[3].m_fZ = aPosZ[3];

	// SkySeaTop
	SetUpNthSkyPoly
	(
		aVertices[2], aVertices[3],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[42],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[44],
		(unsigned char)(*CTimeCycle::ms_aCurrentColours)[46]
	);
	
	aVertices[2].m_fZ = aPosZ[4];
	aVertices[3].m_fZ = aPosZ[4];

	// SkySeaBot
	SetUpNthSkyPoly
	(
		aVertices[2], aVertices[3],
		belowHorizonGrey.m_ucRed,
		belowHorizonGrey.m_ucGreen,
		belowHorizonGrey.m_ucBlue
	);

	aVertices[0].m_fZ = aPosZ[5];
	aVertices[1].m_fZ = aPosZ[5];
	
	// SkyBot
	SetUpNthSkyPoly
	(
		aVertices[0], aVertices[1],
		belowHorizonGrey.m_ucRed, belowHorizonGrey.m_ucGreen, belowHorizonGrey.m_ucBlue
	);

	RenderOutGeometryBuffer();
#endif
}
