#include "StdInc.h"
#include "Imports.hpp"

CCamera *const g_TheCamera = (decltype(g_TheCamera))_g_TheCamera;
RwUInt32 *const g_uiTempBufferVerticesStored = (decltype(g_uiTempBufferVerticesStored))_g_uiTempBufferVerticesStored;
RwInt32 *const g_iTempBufferIndicesStored = (decltype(g_iTempBufferIndicesStored))_g_iTempBufferIndicesStored;
RwImVertexIndex (*const g_aTempRenderIndexList)[4096] = (decltype(g_aTempRenderIndexList))_g_aTempRenderIndexList;
RxObjSpace3DVertex (*const g_aTempVertexBuffer)[2048] = (decltype(g_aTempVertexBuffer))_g_aTempVertexBuffer;

const RwUInt32 g_aVSSkyGradAsm[] =
{
	0xFFFE0101, 0x0023FFFE, 0x42415443, 0x0000001C,
	0x00000053, 0xFFFE0101, 0x00000001, 0x0000001C,
	0x00000100, 0x0000004C, 0x00000030, 0x00000002,
	0x00020004, 0x0000003C, 0x00000000, 0x6A6F7270,
	0x7274614D, 0xAB007869, 0x00030003, 0x00040004,
	0x00000001, 0x00000000, 0x315F7376, 0x4D00315F,
	0x6F726369, 0x74666F73, 0x29522820, 0x44334420,
	0x53203958, 0x65646168, 0x6F432072, 0x6C69706D,
	0x39207265, 0x2E35312E, 0x2E393737, 0x30303030,
	0xABABAB00, 0x0000001F, 0x80000000, 0x900F0000,
	0x0000001F, 0x8000000A, 0x900F0001, 0x0000001F,
	0x80000005, 0x900F0002, 0x00000009, 0xC0010000,
	0x90E40000, 0xA0E40000, 0x00000009, 0xC0020000,
	0x90E40000, 0xA0E40001, 0x00000009, 0xC0040000,
	0x90E40000, 0xA0E40002, 0x00000009, 0xC0080000,
	0x90E40000, 0xA0E40003, 0x00000001, 0xD00F0000,
	0x90E40001, 0x00000001, 0xE0030000, 0x90E40002,
	0x0000FFFF
};

const RwUInt32 g_aPSSkyGradAsm[] =
{
	0xFFFF0200, 0x0023FFFE, 0x42415443, 0x0000001C,
	0x00000053, 0xFFFF0200, 0x00000001, 0x0000001C,
	0x00000100, 0x0000004C, 0x00000030, 0x00000003,
	0x00000001, 0x0000003C, 0x00000000, 0x69617267,
	0x7361526E, 0x00726574, 0x000C0004, 0x00010001,
	0x00000001, 0x00000000, 0x325F7370, 0x4D00305F,
	0x6F726369, 0x74666F73, 0x29522820, 0x44334420,
	0x53203958, 0x65646168, 0x6F432072, 0x6C69706D,
	0x39207265, 0x2E35312E, 0x2E393737, 0x30303030,
	0xABABAB00, 0x05000051, 0xA00F0000, 0x437F0000,
	0x00000000, 0x3F800000, 0x3B808081, 0x0200001F,
	0x80000000, 0x900F0000, 0x0200001F, 0x80000000,
	0xB0030000, 0x0200001F, 0x90000000, 0xA00F0800,
	0x03000042, 0x800F0001, 0xB0E40000, 0xA0E40800,
	0x03000005, 0x800F0000, 0x90E40000, 0xA0000000,
	0x02000013, 0x800F0000, 0x80E40000, 0x04000004,
	0x800F0000, 0x90E40000, 0xA0000000, 0x81E40000,
	0x04000004, 0x800F0002, 0x90E40000, 0xA0000000,
	0x81E40000, 0x03000002, 0x800F0001, 0x80E40001,
	0x81E40002, 0x04000058, 0x800F0001, 0x80E40001,
	0xA0550000, 0xA0AA0000, 0x03000002, 0x800F0000,
	0x80E40000, 0x80E40001, 0x03000005, 0x800F0000,
	0x80E40000, 0xA0FF0000, 0x02000001, 0x800F0800,
	0x80E40000, 0x0000FFFF
};

void (__cdecl *const LittleTest)(void) = (decltype(LittleTest))_LittleTest;

void CreateShaders(void)
{
	RwD3D9CreateVertexShader(g_aVSSkyGradAsm, &CPostEffects::ms_pVSSkyGrad);
	RwD3D9CreatePixelShader(g_aPSSkyGradAsm, &CPostEffects::ms_pPSSkyGrad);

	// Can't call this from DllMain because Underground_Core.asi would not be loaded yet
	Imports::hUndergroundCoreModule = GetModuleHandleA("Underground_Core.asi");

	Imports::RegisterEventCallback("EVENT_INITPOSTEFFECTS", &CPostEffects::InitialiseCB);
	Imports::RegisterEventCallback("EVENT_CLOSEPOSTEFFECTS", &CPostEffects::CloseCB);
}

void DeleteShaders(void)
{
	RwD3D9DeleteVertexShader(CPostEffects::ms_pVSSkyGrad);
	RwD3D9DeletePixelShader(CPostEffects::ms_pPSSkyGrad);
}

CVector operator-(const CVector &rhs)
{
	CVector res;
	
	res.m_fX = -rhs.m_fX;
	res.m_fY = -rhs.m_fY;
	res.m_fZ = -rhs.m_fZ;

	return res;
}
