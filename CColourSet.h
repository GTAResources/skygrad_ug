#pragma once

#include <stdint.h>

// NOTE: Emission colours aren't used
class CColourSet
{
public:
	float m_fAmbientRed, m_fAmbientGreen, m_fAmbientBlue;
	float m_fAmbientRed_Obj, m_fAmbientGreen_Obj, m_fAmbientBlue_Obj;
	float m_fAmbientRed_Bl, m_fAmbientGreen_Bl, m_fAmbientBlue_Bl;
	float m_fAmbientRed_Obj_Bl, m_fAmbientGreen_Obj_Bl, m_fAmbientBlue_Obj_Bl;
	float m_fEmissiveRed, m_fEmissiveGreen, m_fEmissiveBlue;
	float m_fDirectionalRed, m_fDirectionalGreen, m_fDirectionalBlue;
	float m_fAmbBeforeBrightnessRed, m_fAmbBeforeBrightnessGreen, m_fAmbBeforeBrightnessBlue;
	float m_fAmbBlBeforeBrightnessRed, m_fAmbBlBeforeBrightnessGreen, m_fAmbBlBeforeBrightnessBlue;
	float m_fEmissiveBeforeBrightnessRed, m_fEmissiveBeforeBrightnessGreen, m_fEmissiveBeforeBrightnessBlue;
	uint16_t m_nSkyTopRed, m_nSkyTopGreen, m_nSkyTopBlue;
	uint16_t m_nSkyBottomRed, m_nSkyBottomGreen, m_nSkyBottomBlue;
	uint16_t m_nSunCoreRed, m_nSunCoreGreen, m_nSunCoreBlue;
	uint16_t m_nSunCoronaRed, m_nSunCoronaGreen, m_nSunCoronaBlue;
	float m_fSunSize;
	float m_fSpriteSize;
	float m_fSpriteBrightness;
	uint16_t m_nShadowStrength;
	uint16_t m_nLightShadowStrength;
	uint16_t m_nPoleShadowStrength;
	float m_fFarClip;
	float m_fFogStart;
	float m_fLightsOnGroundBrightness;
	uint16_t m_nLowCloudsRed, m_nLowCloudsGreen, m_nLowCloudsBlue;
	uint16_t m_nFluffyCloudsBottomRed, m_nFluffyCloudsBottomGreen, m_nFluffyCloudsBottomBlue;
	float m_fWaterRed, m_fWaterGreen, m_fWaterBlue, m_fWaterAlpha;
	float m_fPostFx1Red, m_fPostFx1Green, m_fPostFx1Blue, m_fPostFx1Alpha;
	float m_fPostFx2Red, m_fPostFx2Green, m_fPostFx2Blue, m_fPostFx2Alpha;
	float m_fCloudAlpha;
	uint32_t m_nHighLightMinIntensity;
	uint16_t m_nWaterFogAlpha;
	float m_fDirectionalMult;
	float m_fLodDistMult;
	int8_t m_nColourFilter : 2; // 0-3, see eColourFilterType for info about the "sharptrail" overlay modes
	bool m_bRainyWeather : 1;  // Rainy weather, also uses wet roads effect
	bool m_bCloudyWeather : 1;  // Cloudy weather
	bool m_bFoggyWeather : 1; // Foggy weather, countryside variant
	bool m_bFoggyWeatherSF : 1; // Foggy weather, SF variant
	bool m_bHurricaneWeather : 1; // Hurricane weather, same as rainy
	bool m_bSnowyWeather : 1; // Snowy weather
	bool m_bSandstormWeather : 1; // Desert Storm!
	bool m_bEarthQuake : 1; // Unused, affects peds in base game
	bool m_bBeastie : 1; // I don't really know what R* planned with this effect
	bool m_bBlurringColours : 1;  // Ambient blurring colour, handled like in GTA:VC
	bool m_bEmissionColours : 1; // Use emission colours, disables m_bBlurringColours if set
	bool m_bHeatHazeFx : 1; // Hot-ness effect
	bool m_bSunGlareFx : 1; // Water vertices have a glow effect on them and so do vehicles
	bool m_bReducedCloudCoverage : 1; // Reduced cloud coverage
	bool m_bExtraSunnyNess : 1; // Lowers low clouds intensity, a bit like reduced cloud coverage but this affects the colours not the actual size of volumetric clouds
	bool m_bRainbows : 1; // When interpolating during the latter half of an in-game hour after rain a rainbow is drawn directly opposite of the sun
};