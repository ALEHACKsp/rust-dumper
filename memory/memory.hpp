#pragma once

#include <Windows.h>
#include <utility>
#include <string>
#include <iostream>

namespace memory::functions
{
	std::pair<std::uintptr_t, std::uintptr_t> get_section(const char* const module_name, const char* const section_name);
}