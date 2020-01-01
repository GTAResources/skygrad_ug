#include "../StdInc.h"

RwRaster **const CPostEffects::ms_pGrainRaster = (decltype(ms_pGrainRaster))_CPostEffects__ms_pGrainRaster;
RwRaster *CPostEffects::ms_pGrainRaster8;
#ifdef POSTFX_DEBUG_GRID
RwRaster *CPostEffects::ms_pGridRaster;
#endif
void *CPostEffects::ms_pVSSkyGrad;
void *CPostEffects::ms_pPSSkyGrad;

bool CPostEffects::CloseCB(void* pData)
{
	UNREFERENCED_PARAMETER(pData);

	if (ms_pGrainRaster8)
	{
		RwRasterDestroy(ms_pGrainRaster8);
		ms_pGrainRaster8 = nullptr;
	}

	return true;
}

bool CPostEffects::InitialiseCB(void* pData)
{
	UNREFERENCED_PARAMETER(pData);

	CreateGrainRaster();

	return true;
}

void CPostEffects::CreateGrainRaster(void)
{
	GetTimeCycleColours();

	RwUInt8 *pRgba, *pLum8, ucGrayScale;

	*ms_pGrainRaster = RwRasterCreate(POSTFX_GRAIN_SIZE, POSTFX_GRAIN_SIZE, 32, rwRASTERFORMAT8888 | rwRASTERTYPETEXTURE);
	ms_pGrainRaster8 = RwRasterCreate(POSTFX_GRAIN_SIZE, POSTFX_GRAIN_SIZE, 8, rwRASTERFORMATLUM8 | rwRASTERTYPETEXTURE);

	if(*ms_pGrainRaster && ms_pGrainRaster8)
	{
		pRgba = RwRasterLock(*ms_pGrainRaster, 0, rwRASTERLOCKWRITE);
		pLum8 = RwRasterLock(ms_pGrainRaster8, 0, rwRASTERLOCKWRITE);

		for(int iPix = 0; iPix < POSTFX_GRAIN_SIZE * POSTFX_GRAIN_SIZE * 4; iPix += 4)
		{
			ucGrayScale = rand();

			pRgba[iPix + 0] = ucGrayScale;
			pRgba[iPix + 1] = ucGrayScale;
			pRgba[iPix + 2] = ucGrayScale;
			pRgba[iPix + 3] = ucGrayScale;

			*pLum8++ = ucGrayScale;
		}

		RwRasterUnlock(ms_pGrainRaster8);
		RwRasterUnlock(*ms_pGrainRaster);
	}

#ifdef POSTFX_DEBUG_GRID
	RwUInt8 *pGridLum;
	int iPix, iScanLinePix;

	ms_pGridRaster = RwRasterCreate(POSTFX_GRAIN_SIZE, POSTFX_GRAIN_SIZE, 8, rwRASTERFORMATLUM8);
	pGridLum = RwRasterLock(ms_pGridRaster, 0, rwRASTERLOCKWRITE);

	for(iPix = 0; iPix < POSTFX_GRAIN_SIZE; iPix++)
		pGridLum[iPix] = 0;

	for
	(
		iScanLinePix = POSTFX_GRAIN_SIZE;
		iPix < (POSTFX_GRAIN_SIZE * POSTFX_GRAIN_SIZE * 1) - POSTFX_GRAIN_SIZE;
		iPix++, iScanLinePix += POSTFX_GRAIN_SIZE
	)
	{
		pGridLum[iPix] = 0;

		for(iPix++; iPix < (iScanLinePix - 1); iPix++)
			pGridLum[iPix] = 255;

		pGridLum[iPix] = 0;
	}

	for(; iPix < POSTFX_GRAIN_SIZE * POSTFX_GRAIN_SIZE * 1; iPix++)
		pGridLum[iPix] = 0;

	RwRasterUnlock(ms_pGridRaster);
#endif
}
