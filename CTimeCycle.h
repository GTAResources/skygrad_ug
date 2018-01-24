#ifndef _CTIMECYCLE_H_
#define _CTIMECYCLE_H_

#include "CColourSet.h"

class CTimeCycle
{
public:
	static CColourSet* m_CurrentColours;

#define _CTimeCycle__ms_belowHorizonGrey	0x00B7CB10
	static CRGBA *const CTimeCycle::ms_belowHorizonGrey;
};

#endif //_CTIMECYCLE_H_
