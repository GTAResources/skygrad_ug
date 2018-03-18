#pragma once

#include <stdint.h>

class CColourSet
{
public:
	float			m_fAmbientRed, m_fAmbientGreen, m_fAmbientBlue;
	float			m_fAmbientRed_Obj, m_fAmbientGreen_Obj, m_fAmbientBlue_Obj;
	float			m_fAmbientRed_Bl, m_fAmbientGreen_Bl, m_fAmbientBlue_Bl;
	float			m_fAmbientRed_Obj_Bl, m_fAmbientGreen_Obj_Bl, m_fAmbientBlue_Obj_Bl;
	float			m_fDirectionalRed, m_fDirectionalGreen, m_fDirectionalBlue;
	float			m_fAmbBeforeBrightnessRed, m_fAmbBeforeBrightnessGreen, m_fAmbBeforeBrightnessBlue;
	float			m_fAmbBlBeforeBrightnessRed, m_fAmbBlBeforeBrightnessGreen, m_fAmbBlBeforeBrightnessBlue;
	uint16_t		m_nSkyTopRed, m_nSkyTopGreen, m_nSkyTopBlue;
	uint16_t		m_nSkyBottomRed, m_nSkyBottomGreen, m_nSkyBottomBlue;
	uint16_t		m_nSunCoreRed, m_nSunCoreGreen, m_nSunCoreBlue;
	uint16_t		m_nSunCoronaRed, m_nSunCoronaGreen, m_nSunCoronaBlue;
	float			m_fSunSize;
	float			m_fSpriteSize;
	float			m_fSpriteBrightness;
	uint16_t		m_nShadowStrength;
	uint16_t		m_nLightShadowStrength;
	uint16_t		m_nPoleShadowStrength;
	float			m_fFarClip;
	float			m_fFogStart;
	float			m_fLightsOnGroundBrightness;
	uint16_t		m_nLowCloudsRed, m_nLowCloudsGreen, m_nLowCloudsBlue;
	uint16_t		m_nFluffyCloudsBottomRed, m_nFluffyCloudsBottomGreen, m_nFluffyCloudsBottomBlue;
	uint16_t		m_nFluffyCloudsTopRed, m_nFluffyCloudsTopGreen, m_nFluffyCloudsTopBlue;
	float			m_fWaterRed, m_fWaterGreen, m_fWaterBlue, m_fWaterAlpha;
	float			m_fPostFx1Red, m_fPostFx1Green, m_fPostFx1Blue, m_fPostFx1Alpha;
	float			m_fPostFx2Red, m_fPostFx2Green, m_fPostFx2Blue, m_fPostFx2Alpha;
	float			m_fCloudAlpha;
	uint32_t		m_nRadiosityIntensityLimit, m_nRadiosityIntensity;
	uint16_t		m_nWaterFogAlpha;
	float			m_fDirectionalMult;
	float			m_fLodDistMult;
	float			m_fBlurOffset;
};