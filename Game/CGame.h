#ifndef _CGAME_H_
#define _CGAME_H_

class CGame
{
public:
	struct Vtbl
	{
#define _CGame__ShutdownRenderWare		0x0053BB80
		//static void (__cdecl *const ShutdownRenderWare)(void);
#define _CGame__InitialiseRenderWare	0x005BD600
		//static void (__cdecl *const InitialiseRenderWare)(void);
	};
};

#endif //_CGAME_H_
