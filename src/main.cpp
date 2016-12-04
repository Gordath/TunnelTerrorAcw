#include "TunnelTerrorGame.h"
#include "Window_DX.h"

#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	TunnelTerrorGame game;

	Window_DX window{&game, 1024, 768};
	window.Initialise();

	return 0;
}

#if defined(_MSC_VER)
#  pragma comment(linker, "/ENTRY:mainCRTStartup")
#  if !defined(NDEBUG)
#    pragma comment(linker, "/SUBSYSTEM:console ")
#    pragma message(__FILE__ ": /SUBSYSTEM:console /ENTRY:mainCRTStartup")
#  else
#    pragma comment(linker, "/SUBSYSTEM:windows")
#    pragma message(__FILE__ ": /SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#  endif
#endif
