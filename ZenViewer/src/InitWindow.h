#pragma once
#include <SDL_syswm.h>
#include <SDL_ttf.h>

#include "Utils.h"
#include "core/Window.h"

DropManager* initDrop(SDL_Window* win) {
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(win, &wmInfo);
	const auto hwnd = wmInfo.info.win.window;

	auto value = OleInitialize(nullptr);

	const auto dm = new DropManager();
	RegisterDragDrop(hwnd, dm);

	return dm;
}

inline Window* initWindow()
{
#ifdef EXV_ENABLE_BMFF
	Exiv2::enableBMFF();
#endif
	if (TTF_Init() != 0) {
		runtimeError("TTF_Init");
		SDL_Quit();
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		runtimeError(SDL_GetError());
	}

	auto win = new Window("ZenViewer");
	SDL_GetRendererOutputSize(win->getRender(), &win->width, &win->height);
	const auto dm = initDrop(win->getWindow());
	win->dropManager = dm;

	return win;
}
