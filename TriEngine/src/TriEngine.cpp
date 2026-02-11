#include "../include/TriEngine.h"
#include "../../lib/raylib/src/raylib.h"
#if defined(__EMSCRIPTEN__)
# include <emscripten/emscripten.h>
#elif defined(__APPLE__)
# include <CoreFoundation/CoreFoundation.h>
#endif

Tri::Engine::Engine()
{
	#if defined(__EMSCRIPTEN__)
	#elif defined(__APPLE__)
    	// Récupère le chemin vers le dossier "Resources" interne au .app
    	CFBundleRef mainBundle = CFBundleGetMainBundle();
    	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    	char path[PATH_MAX];
	
    	if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) {
    	    // Change le répertoire de travail vers ce dossier
    	    chdir(path);
    	}
	
    	CFRelease(resourcesURL);
	#endif
}

Tri::Engine::Engine(int width, int height, const char *windowName)
{
	#if defined(__EMSCRIPTEN__)
	#elif defined(__APPLE__)
    	// Récupère le chemin vers le dossier "Resources" interne au .app
    	CFBundleRef mainBundle = CFBundleGetMainBundle();
    	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    	char path[PATH_MAX];
	
    	if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) {
    	    // Change le répertoire de travail vers ce dossier
    	    chdir(path);
    	}
	
    	CFRelease(resourcesURL);
	#endif
    InitWindow(width, height, windowName);
	InitAudioDevice();
	this->_isInit = true;
}

Tri::Engine::~Engine()
{
	CloseAudioDevice();
    CloseWindow();
}

int	Tri::Engine::init(int width, int height, const char *windowName)
{
	if (!this->_isInit)
	{
		InitWindow(width, height, windowName);
		if (!IsWindowReady())
			return (1);
		InitAudioDevice();
		if (!IsAudioDeviceReady())
		{
			CloseWindow();
			return (1);
		}
	}
	this->_isInit = true;
	return (0);
}

void	Tri::Engine::_emscriptenLoop(void *arg)
{
	Tri::Engine	*engine = static_cast<Tri::Engine*>(arg);

	if (engine->_userLoop)
		engine->_userLoop();
}

void	Tri::Engine::loop(std::function<void()> userLoop)
{
	this->_userLoop = userLoop;
	#if defined(__EMSCRIPTEN__)
		emscripten_set_main_loop_arg(_emscriptenLoop, this, TRI_FPS, 1);
	#else
	while (!WindowShouldClose())
		userLoop();
	#endif
}