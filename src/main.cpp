#include "tunnel_terror_game.h"
#include "Window_DX.h"


int main(int argc, char *argv[])
{

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
