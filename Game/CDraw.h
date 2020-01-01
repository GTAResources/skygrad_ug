#include "RenderWare.h"

#ifndef _CDRAW_H_
#define _CDRAW_H_

class CDraw
{
public:
#define _CDraw__ms_fFOV			0x008D5038
	static float *const ms_fFOV;
#define _CDraw__ms_fAspectRatio	0x00C3EFA4
	static float *const ms_fAspectRatio;
};

#endif //_CDRAW_H_
