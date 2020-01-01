#include "RenderWare.h"

#ifndef _CVECTOR_H_
#define _CVECTOR_H_

#pragma pack(push, 1)

class CVector
{
public:
	struct Vtbl
	{
#define _CVector__Normalise	0x0059C910
		static void (__thiscall *const Normalise)(CVector *self);
	};

	union
	{
		struct
		{
			float m_fX;
			float m_fY;
			float m_fZ;
		};
		RwV3d m_rw;
	};

	void Normalise(void);
};

#pragma pack(pop)

#endif //_CVECTOR_H_
