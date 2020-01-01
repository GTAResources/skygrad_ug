#include "CVector.h"
#include "RenderWare.h"

#ifndef _CMATRIX_H_
#define _CMATRIX_H_

#pragma pack(push, 1)

class CMatrix
{
public:
	/*union
	{
		struct
		{*/
			CVector m_right;
			unsigned int m_uiFlags;
			CVector m_up;
			unsigned int m_pad_1;
			CVector m_at;
			unsigned int m_pad_2;
			CVector m_pos;
			unsigned int m_pad_3;
		/*};
		RwMatrix m_rw;
	};*/
};

#pragma pack(pop)

#endif //_CMATRIX_H_
