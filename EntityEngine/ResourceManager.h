#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <map>
#include <iostream>
#include "Resource.h"

static const std::wstring MODELS_PATH{ L"data\\models\\" };
static const std::wstring TEXTURE_PATH{ L"data\\textures\\" };

class ResourceManager {
private:
	std::map<std::wstring, Resource*> _resourcesByName;
	std::map<unsigned int, Resource*> _resourcesById;

public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	~ResourceManager()
	{
		for (auto resource : _resourcesByName) {
			delete resource.second;
		}
		_resourcesByName.clear();
		_resourcesById.clear();
	}

	template<typename T>
	bool Load(const std::wstring& fileName) 
	{
		static int id = 0;
		T* resource{ new T };
		
		if(resource->Load(fileName)) {
			_resourcesByName[fileName] = resource;
			resource->SetId(id);
			_resourcesById[id++] = resource;
			return true;
		}

		return false;
	}

	template<typename T>
	T* Get(const std::wstring& fileName) 
	{
		Resource* resource{ _resourcesByName[fileName] };
		
		if(!resource) {
			Load<T>(fileName);
			resource = _resourcesByName[fileName];
		}

		T* res{ dynamic_cast<T*>(resource) };
		if(!res) {
			std::cerr << "The file you asked for does not represent the type you are requesting!" << std::endl;
			return nullptr;
		}

		return res;
	}
};

#endif //RESOURCE_MANAGER_H_
