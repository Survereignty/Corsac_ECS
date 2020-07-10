#pragma once

#include <EASTL/bitset.h>

// Размер сущности
#define OBJECTSIZE uint32_t

// Максимальное кол-во сущностей
#define OBJECTMAXCOUNT 1024

// Размер Компонента
#define COMPONENTSIZE uint8_t

// Максимальное кол-во компонентов в 1 сущности
#define COMPONENMAXCOUNT 32

// Размер события
#define EVENTSIZE uint32_t


// Сущность
using Object = OBJECTSIZE;
const Object MAX_OBJECTS = OBJECTMAXCOUNT;

// Компонент
using ComponentType = COMPONENTSIZE;
const ComponentType MAX_COMPONENTS = COMPONENMAXCOUNT;
using ListComponentId = eastl::bitset<MAX_COMPONENTS>;

// События
using EventId = EVENTSIZE;

///////////////////////////////////////////////////////////////////////////////
// operator new used by EASTL
///////////////////////////////////////////////////////////////////////////////

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
    return malloc(size);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
    return malloc(size);
}
