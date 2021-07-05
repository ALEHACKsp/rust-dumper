#include <thread>

#include "il2cpp/il2cpp.hpp"

void open_console(const char* const console_name)
{
	AllocConsole();

	FILE* file;

	freopen_s(&file, "CONIN$", "r", stdin);
	freopen_s(&file, "CONOUT$", "w", stdout);
	freopen_s(&file, "CONOUT$", "w", stderr);

	SetConsoleTitleA(console_name);
}

void core()
{
	open_console("rust-dumper");

	il2cpp::functions::initiate();

	auto [data_begin, data_end] = memory::functions::get_section("GameAssembly.dll", ".data");

	std::printf
	(
		"[rust-dumper] data_begin => 0x%p\n"
		"[rust-dumper] data_end => 0x%p\n\n",

		data_begin,
		data_end
	);

	std::printf("[rust-dumper] insert class name => ");

	std::string class_name;
	std::getline(std::cin, class_name);

	const auto class_instance = il2cpp::functions::get_class(class_name);

	for (; data_begin < data_end; ++data_begin)
	{
		const auto current_class = *reinterpret_cast<void**>(data_begin);

		if (current_class == class_instance)
		{
			std::printf("[rust-dumper] %s => 0x%p\n", class_name.c_str(), data_begin - reinterpret_cast<std::uintptr_t>(il2cpp::values::game_assembly));

			break;
		}
	}
}

bool __stdcall DllMain(HINSTANCE, const std::uint32_t reason, void*)
{
	if (reason == DLL_PROCESS_ATTACH)
		std::thread{ core }.detach();
}