#include "GAPIContextLocator.h"


GAPIContext* GAPIContextLocator::_context;

GAPIContext* GAPIContextLocator::GetGAPIContext()
{
	return _context;
}

void GAPIContextLocator::Provide(GAPIContext* context)
{
	_context = context;
}
