#ifndef IBO_H_
#define IBO_H_

struct Vertex;
class Renderer;

class IBO {
protected:
	int _numIndices;

public:
	IBO() : _numIndices(0)
	{
	}

	virtual ~IBO() = default;

	virtual void Create(Renderer* renderer, unsigned int indices[], int numIndices) = 0;
	virtual void Bind(Renderer* renderer) = 0;
	virtual void Draw(Renderer* renderer) = 0;
};

#endif //IBO_H_ 
