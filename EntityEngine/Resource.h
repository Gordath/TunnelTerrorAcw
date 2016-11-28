#ifndef RESOURCE_H_
#define RESOURCE_H_
#include <string>

class Resource {
private:
	unsigned int _id;

public:
	Resource(unsigned int id) : _id(id) { }
	virtual ~Resource() = default;

	unsigned int GetId() const { return _id; }
	void SetId(unsigned int id) { _id = id; }

	virtual bool Load(const std::string& fileName);
};

#endif //RESOURCE_H_