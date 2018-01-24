#include "StdInc.h"

void (__thiscall *const CVector::Vtbl::Normalise)(CVector *self) = (decltype(Normalise))_CVector__Normalise;

void CVector::Normalise(void)
{
	Vtbl::Normalise(this);
}
