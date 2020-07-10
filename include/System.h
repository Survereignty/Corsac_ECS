#pragma once

#include "Types.h"
#include "EASTL/set.h"

///////////////////////////////////////////////////
//
//	Класс родитель для систем
//
///////////////////////////////////////////////////
class CRSC_System
{
public:
	eastl::set<Object> Objects;
};