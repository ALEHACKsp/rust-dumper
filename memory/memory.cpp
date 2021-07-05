#include "memory.hpp"

std::pair<std::uintptr_t, std::uintptr_t> memory::functions::get_section(const char* const module_name, const char* const section_name)
{
	const auto process_base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(module_name));

	std::printf("[rust-dumper] process_base => 0x%p\n", process_base);

	const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(process_base);

	const auto nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(process_base + dos_header->e_lfanew);

	const auto sections = IMAGE_FIRST_SECTION(nt_headers);

	for (auto i = 0u; i < nt_headers->FileHeader.NumberOfSections; ++i)
	{
		if (!std::memcmp(sections[i].Name, section_name, IMAGE_SIZEOF_SHORT_NAME))
		{
			const auto& current_section = sections[i];

			const auto current_section_start = process_base + current_section.VirtualAddress;

			const auto current_section_end = current_section_start + current_section.Misc.VirtualSize;

			return { current_section_start, current_section_end };
		}
	}

	return {};
}