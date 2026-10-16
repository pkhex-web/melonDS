/*
    Copyright 2016-2026 melonDS team

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#ifndef ARMJIT_GLOBAL_H
#define ARMJIT_GLOBAL_H

#include "types.h"

#include <stdlib.h>

namespace melonDS
{

namespace ARMJIT_Global
{

static constexpr size_t CodeMemorySliceSize = 1024*1024*32;

void Init();
void DeInit();

enum class CodeMemoryMode
{
    Own,
    WXToggle,
    DualMap,
};

// Where only the frontend can get executable memory, as on iOS, it hands out the code memory.
// rx and rw are the same for WXToggle. The allocator returns false when it has none, and the JIT must stay off.
using CodeMemoryAllocator = bool (*)(size_t size, void** rx, void** rw);
using CodeMemoryFreer = void (*)(void* rx);
void SetCodeMemoryAllocator(CodeMemoryMode mode, CodeMemoryAllocator allocate, CodeMemoryFreer free);
CodeMemoryMode GetCodeMemoryMode();

// Returns the address to run code from. rw, when given, receives the address to write it through.
void* AllocateCodeMem(void** rw = nullptr);
void FreeCodeMem(void* codeMem);

}

}

#endif