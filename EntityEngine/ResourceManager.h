#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <map>
#include <iostream>
#include "Resource.h"

class ResourceManager {
private:
	std::map<std::string, Resource*> _resourcesByName;
	std::map<unsigned int, Resource*> _resourcesById;

public:
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
	bool Load(const std::string& fileName) 
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
	T* Get(const std::string& fileName) 
	{
		Resource* resource{ _resourcesByName[fileName] };
		
		if(!resource) {
			resource->Load(fileName);
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
