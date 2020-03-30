#pragma once
#include <map>
#include <cstdint>
#include <memory>

namespace SEngine
{
	class SKeyboardComponent;
	class SMouseComponent;

	class  SServiceManager final
	{
	public:
		void AddService(std::uint64_t typeId, void* service);
		void RemoveService(std::uint64_t typeId);
		void* GetService(std::uint64_t typeId) const;

		std::map<std::uint64_t, void*>					mServices;
	};
}