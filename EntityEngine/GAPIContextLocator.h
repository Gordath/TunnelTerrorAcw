#ifndef GAPI_CONTEXT_LOCATOR_H_
#define GAPI_CONTEXT_LOCATOR_H_
#include "GAPIContext.h"

class GAPIContextLocator {
private:
	static GAPIContext* _context;

protected:
	static GAPIContext* GetGAPIContext();

public:
	static void Provide(GAPIContext* context);
};

#endif //GAPI_CONTEXT_LOCATOR_H_
