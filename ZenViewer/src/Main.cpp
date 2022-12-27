#include <SDL.h>
#include "DropManager.h"
#include "InitWindow.h"
#include "ui/core/Component.h"
#include "core/image/ImageLoader.h"
#include "math/Math.h"
#include "ui/core/tabs/Tab.h"
#include "ui/core/tabs/Tabs.h"

using namespace std;
#undef main

class SDLMoveWindow
{
	bool mouseIsDown_ = false;
	bool isMoveWindow_ = false;
	math::Vector2D mouse_;
	math::Vector2D offset_;

	math::Vector2D windowPos_;
	math::Vector2D windowPosOffset_;

	math::Vector2D newWindowPos_;
	math::Vector2D newWindowPosAnim_;

	math::Vector2D newWindowSize_;
	math::Vector2D newWindowSizeAnim_;

	void onWindowMove(math::Vector2D pos)
	{
		const auto index = SDL_GetWindowDisplayIndex(window->getWindow());
		SDL_Rect screenRect{};
		SDL_GetDisplayBounds(index, &screenRect);
		const math::Vector2D screenSize{
		static_cast<float>(screenRect.w),
		static_cast<float>(screenRect.h),
		};

		const math::Vector2D screenPos{
			static_cast<float>(screenRect.x),
			static_cast<float>(screenRect.y),
		};

		const auto y = pos.y - screenPos.y;
		math::Vector2D size;

		if (y < 20)
		{
			size = screenSize;
			newWindowPos_ = screenPos;
		}
		else
		{
			size = screenSize / 2;
			
		}
		if (newWindowSize_ != size)
		{
			windowPosOffset_ = (newWindowSize_ - size) / 2;
			newWindowSize_ = size;
		}
	}
public:
	Window* window;

	explicit SDLMoveWindow(Window* win) : window(win)
	{
		const auto index = SDL_GetWindowDisplayIndex(window->getWindow());
		SDL_Rect screenRect{};
		SDL_GetDisplayBounds(index, &screenRect);

		newWindowSize_.x = screenRect.w / 2;
		newWindowSize_.y = screenRect.h / 2;

		newWindowPos_.x = screenRect.w / 4;
		newWindowPos_.y = screenRect.h / 4;
	}

	void eventHandler(SDL_Event* e)
	{
		int x, y;
		int wx, wy;

		SDL_GetWindowPosition(window->getWindow(), &wx, &wy);
		SDL_GetGlobalMouseState(&x, &y);

		mouse_.x = static_cast<float>(x);
		mouse_.y = static_cast<float>(y);

		windowPos_.x = static_cast<float>(wx);
		windowPos_.y = static_cast<float>(wy);

		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			mouseIsDown_ = true;
		}
		if (e->type == SDL_MOUSEBUTTONUP)
		{
			mouseIsDown_ = false;
			isMoveWindow_ = false;
		}
		if (mouseIsDown_ && e->button.button == 4)
		{
			isMoveWindow_ = true;
		}

		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			offset_ = mouse_ - windowPos_;
			windowPosOffset_ = { 0, 0 };
		}

		if ((e->type == SDL_MOUSEMOTION) && isMoveWindow_)
		{
			newWindowPos_ = (mouse_ - offset_) + windowPosOffset_;
			onWindowMove(mouse_);
		}
	}

	void update()
	{
		newWindowPosAnim_ = math::aLerp(newWindowPosAnim_, newWindowPos_, .4);
		newWindowSizeAnim_ = math::aLerp(newWindowSizeAnim_, newWindowSize_, .4);
		SDL_SetWindowPosition(window->getWindow(), newWindowPosAnim_.x, newWindowPosAnim_.y);
		SDL_SetWindowSize(window->getWindow(), newWindowSizeAnim_.x, newWindowSizeAnim_.y);
	}
};

int main(int argc, char* args) {
	auto win = *initWindow();
	const auto render = win.getRender();
	SDLMoveWindow mw{ &win };

	SDL_RenderClear(win.getRender());

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	ImageLoader imageLoader;
	Tab tab(&win, &imageLoader);



	tab.window(&win);
	tab.mount();

	bool quit = false;
	SDL_Event e;
	SDL_SetWindowBordered(win.getWindow(), SDL_FALSE);


	while (!quit)
	{
		SDL_SetRenderDrawColor(render, 37, 37, 37, 255);
		imageLoader.update();
		while (SDL_PollEvent(&e))
		{
			SDL_GetRendererOutputSize(render, &win.width, &win.height);

			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (const auto dm = win.dropManager; e.type == dm->FileDrop) {

				if (!dm->files.empty() && fs::is_directory(dm->files[0])) {
					imageLoader.loadFolder(dm->files[0]);
				}
			}
			mw.eventHandler(&e);
			tab.event(&e);
		}

		mw.update();
		tab.update();
		if (tab.isModified()) {
			SDL_RenderClear(render);
			tab.render(render);
			SDL_RenderPresent(render);
		}
		SDL_Delay(16);
	}

	SDL_Quit();
	return 0;
}