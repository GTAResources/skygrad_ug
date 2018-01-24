#include "CMatrixLink.h"
#include "CSimpleTransform.h"

#ifndef _CPLACEABLE_H_
#define _CPLACEABLE_H_

#pragma pack(push, 1)

class CPlaceable
{
public:
	char align_0[4];
	CSimpleTransform m_placement;
	CMatrixLink *m_pMatrix;
};

#pragma pack(pop)

#endif //_CPLACEABLE_H_
