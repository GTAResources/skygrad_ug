#include "StdInc.h"
#include "Inject.h"
#include "CTimeCycle.h"

VOID WINAPI InstallAllHooks(void)
{
	CTimeCycle::m_CurrentColours = Hook::ReadMemory<int, CColourSet*>(0x560241);

	Hook::InstallHookNearOffset((LPVOID)0x0053BBCC, DeleteShaders);

	Hook::InstallHookNearOffset((LPVOID)0x0053D81D, CClouds::RenderSkyPolys);

	Hook::InstallHookNearOffset((LPVOID)0x005BD766, CreateShaders);

	Hook::InstallHookNearJump((LPVOID)0x007010C6, HOOK_7010C6_CPostEffects__Close);
#ifndef POSTFX_DEBUG_GRID
	Hook::WriteProtectedMemory<unsigned char>((LPVOID)0x007010D2, 8);
#else
	Hook::WriteProtectedMemory<unsigned char>((LPVOID)0x007010D2, 0x0C);
#endif
	Hook::InstallHookNearJump((LPVOID)0x00704635, CPostEffects::CreateGrainRaster);

	Hook::SkipProtectedMemory((PBYTE)RxD3D9SubmitNoLightBody + 0x56, (PBYTE)RxD3D9SubmitNoLightBody + 0x62);
	Hook::InstallHookNearJump((PBYTE)RxD3D9SubmitNoLightBody + 0x12F, HOOK_RxD3D9SubmitNoLightBody_12F);
}

void __declspec(naked) HOOK_7010C6_CPostEffects__Close(void)
{
#define _7010CB_CPostEffects__Close	0x007010CB
	__asm
	{
		call	RwRasterDestroy
		mov		eax, CPostEffects::ms_pGrainRaster8
		push	eax
		call	RwRasterDestroy
#ifdef POSTFX_DEBUG_GRID
		mov		ecx, CPostEffects::ms_pGridRaster
		push	ecx
		call	RwRasterDestroy
#endif
		mov		edx, _7010CB_CPostEffects__Close
		jmp		edx
	}
#undef _7010CB_CPostEffects__Close
}

void __declspec(naked) HOOK_RxD3D9SubmitNoLightBody_12F(void)
{
	__asm
	{
		mov		ebp, _rwD3D9CustomVertexShader
		test	ebp, ebp
		jz		set_ltm_matrix
		mov		eax, _rwD3D9VSCustomWorldMatrix
		push	eax
		call	_rwD3D9VSSetActiveWorldMatrix
		push	__rxD3D9VertexShaderConstants
		call	_rwD3D9VSGetComposedTransformMatrix
		push	16
		push	__rxD3D9VertexShaderConstants
		push	0
		call	_rwD3D9SetVertexShaderConstant
		add		esp, 14h
		jmp		set_custom_vshader
set_ltm_matrix:
		mov		eax, [edi]_rwIm3DPoolStash.ltm
		push	eax
		call	RwD3D9SetTransformWorld
		add		esp, 4
set_custom_vshader:
		cmp		ds:[__rwD3D9LastVertexShaderUsed], ebp
		je		set_custom_pshader
		mov		ds:[__rwD3D9LastVertexShaderUsed], ebp
		push	ebp
		mov		eax, ds:[__RwD3DDevice]
		push	eax
		mov		ecx, [eax]IDirect3DDevice9.lpVtbl
		call	dword ptr [ecx]IDirect3DDevice9Vtbl.SetVertexShader
set_custom_pshader:
		mov		eax, _rwD3D9CustomPixelShader
		cmp		ds:[__rwD3D9LastPixelShaderUsed], eax
		je		rwim3d_pipeline
		mov		ds:[__rwD3D9LastPixelShaderUsed], eax
		push	eax
		mov		ecx, ds:[__RwD3DDevice]
		push	ecx
		mov		edx, [ecx]IDirect3DDevice9.lpVtbl
		call	dword ptr [edx]IDirect3DDevice9Vtbl.SetPixelShader
rwim3d_pipeline:
		jmp		JMP_RxD3D9SubmitNoLightBody_169
	}
}
