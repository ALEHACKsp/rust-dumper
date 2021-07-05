#include "il2cpp.hpp"

void* assembly_csharp_image;

HMODULE il2cpp::values::game_assembly;

void il2cpp::functions::initiate()
{
	values::game_assembly = GetModuleHandleA("GameAssembly.dll");

	using il2cpp_domain_get_t = void*(*)();
	const auto il2cpp_domain_get = reinterpret_cast<il2cpp_domain_get_t>(GetProcAddress(values::game_assembly, "il2cpp_domain_get"));

	const auto domain = il2cpp_domain_get();

	using il2cpp_domain_get_assemblies_t = std::uintptr_t*(*)(void* domain, std::size_t& assemblies_size);
	const auto il2cpp_domain_get_assemblies = reinterpret_cast<il2cpp_domain_get_assemblies_t>(GetProcAddress(values::game_assembly, "il2cpp_domain_get_assemblies"));

	std::size_t assemblies_size;
	const auto assemblies = il2cpp_domain_get_assemblies(domain, assemblies_size);

	for (auto i = 0ull; i < assemblies_size; ++i)
	{
		const auto current_assembly = assemblies[i];

		if (!std::memcmp(*reinterpret_cast<const void**>(current_assembly + 0x18), "Assembly-CSharp", 16))
		{
			assembly_csharp_image = *reinterpret_cast<void**>(current_assembly);

			break;
		}
	}

	std::printf
	(
		"[rust-dumper] game_assembly => 0x%p\n\n"

		"[rust-dumper] il2cpp_domain_get => 0x%p\n"
		"[rust-dumper] domain => 0x%p\n\n"

		"[rust-dumper] il2cpp_domain_get_assemblies => 0x%p\n"
		"[rust-dumper] assemblies => 0x%p\n"
		"[rust-dumper] assemblies_size => 0x%X\n"
		"[rust-dumper] assembly_csharp_image => 0x%p\n\n",

		values::game_assembly,

		il2cpp_domain_get,
		domain,

		il2cpp_domain_get_assemblies,
		assemblies,
		assemblies_size,
		assembly_csharp_image
	);
}

void* il2cpp::functions::get_class(const std::string& class_name)
{
	using il2cpp_class_from_name_t = void*(*)(void* image, const char* class_namespace, const char* class_name);
	const auto il2cpp_class_from_name = reinterpret_cast<il2cpp_class_from_name_t>(GetProcAddress(values::game_assembly, "il2cpp_class_from_name"));

	const auto class_instance = il2cpp_class_from_name(assembly_csharp_image, "", class_name.c_str());

	std::printf
	(
		"\n[rust-dumper] il2cpp_class_from_name => 0x%p\n"
		"[rust-dumper] class_instance => 0x%p\n\n",

		il2cpp_class_from_name,
		class_instance
	);

	return class_instance;
}