#pragma once

#include "../memory/memory.hpp"

namespace il2cpp::values
{
	extern HMODULE game_assembly;
}

namespace il2cpp::functions
{
	void initiate();

	void* get_class(const std::string& class_name);
}