#include "Public/SServiceManager.h"

using namespace std;

namespace SEngine {
	void SServiceManager::AddService(uint64_t typeId, void* service)
	{
		mServices.insert(std::pair<uint64_t, void*>(typeId, service));
	}

	void SServiceManager::RemoveService(uint64_t typeId)
	{
		mServices.erase(typeId);
	}

	void* SServiceManager::GetService(uint64_t typeId) const
	{
		std::map<uint64_t, void*>::const_iterator it = mServices.find(typeId);

		return (it != mServices.end() ? it->second : nullptr);
	}

}
