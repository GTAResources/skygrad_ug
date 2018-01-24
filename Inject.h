#include "StdInc.h"

#ifndef _INJECT_H_
#define _INJECT_H_

#include "Hook.h"

WINEXP VOID WINAPI InstallAllHooks(void);
WINEXP void HOOK_7010C6_CPostEffects__Close(void);
// 0x0080E39F
WINEXP void HOOK_RxD3D9SubmitNoLightBody_12F(void);

#endif //_INJECT_H_
