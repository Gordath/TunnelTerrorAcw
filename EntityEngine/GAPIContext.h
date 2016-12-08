#ifndef GAPI_CONTEXT_H_
#define GAPI_CONTEXT_H_

class GAPIContext {
public:
	virtual ~GAPIContext() = default;
	virtual bool Create() = 0;
};

#endif //GAPI_CONTEXT_H_
