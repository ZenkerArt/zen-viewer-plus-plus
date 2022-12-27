#include "Tab.h"

#include <iostream>

void visibleRect(ui::ComponentWithChildren* doc)
{
	const auto docSize = doc->window()->getSize();

	for (const auto component : doc->components())
	{
		constexpr float clipping = 0;
		const auto pos = component->absolutePos();
		const auto size = component->size();

		const float top = pos.y;
		const float bottom = top + size.y;

		const float left = pos.x;
		const float right = pos.x + size.x;

		const bool isX = docSize.x - clipping > left && clipping < right;
		const bool isY = bottom > clipping && top < docSize.y - clipping;

		const auto child = dynamic_cast<ui::ComponentWithChildren*>(component);

		component->isVisible(isX && isY);

		if (child)
		{
			visibleRect(child);
		}
	}
}

void Tab::onMount()
{
	document_.add(&imageGrid_);
	text.window(window());
	text.fontSize(16);
	text.clip(100);
	text.text("adawdafafwadawdawdadwdawd");
}

void Tab::onUpdate()
{
	document_.update();
	moveDocument_->update();

	if (document_.isModified())
	{
		lastUpdate_ = GetTickCount();
	}

	document_.lateUpdate();
	visibleRect(&document_);

}

void Tab::onDestroy()
{
	document_.destroy();
}


void Tab::onRender(SDL_Renderer* renderer)
{
	document_.render(render_);
	Component::onRender(renderer);
}

bool Tab::isModified() const
{
	return GetTickCount() < lastUpdate_ + 5000;
}

Tab::Tab(Window* win, ImageLoader* imageLoader)
{
	render_ = win->getRender();
	document_.window(win);
	document_.size(static_cast<float>(win->width), static_cast<float>(win->height));
	window_ = win;
	imageGrid_.imageLoader = imageLoader;
	moveDocument_ = new MoveDocument{ &document_ };
	imageLoader->images = &imageGrid_;
}

void Tab::event(const SDL_Event* e)
{
	if(e->type == SDL_JOYBUTTONUP)
	{
		cout << (int)e->jbutton.button << endl;
		const auto cols = imageGrid_.columnCount();
		if (e->jbutton.button == 2) imageGrid_.columnCount(cols - 1);
		if (e->jbutton.button == 1) imageGrid_.columnCount(cols + 1);
	}

	if(e->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		document_.size(static_cast<float>(window_->width), static_cast<float>(window_->height));
	}
	moveDocument_->eventHandler(e);
}
