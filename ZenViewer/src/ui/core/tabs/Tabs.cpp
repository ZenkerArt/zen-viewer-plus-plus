#include "Tabs.h"

void closeIcon(SDL_Renderer* render, const math::Vector2D pos, const float size)
{
	const auto s = pos + size;
	SDL_RenderDrawLineF(render, pos.x, pos.y, s.x, s.y);
	SDL_RenderDrawLineF(render, s.x, pos.x, pos.y, s.y);
}

void Tabs::onRender(SDL_Renderer* renderer)
{
	const auto pos = absolutePos();
	unsigned int tabIndex = 1;
	constexpr float tabWidth = 200;
	constexpr float paddingLeft = 16;
	constexpr float paddingTB = 16;

	for(const auto tab : tabs_)
	{
		const auto x = pos.x * (tabWidth * tabIndex);
		const auto y = pos.y;
		const auto fontSize = tab->text.size();

		const float tabHeight = fontSize.y + paddingTB * 2;
		SDL_FRect rect{
		x, pos.y,
		tabWidth, tabHeight
		};
		SDL_SetRenderDrawColor(renderer, 23, 23, 23, 255);
		SDL_RenderFillRectF(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		tab->text.pos(x + paddingLeft, y + ((tabHeight / 2) - fontSize.y / 2));
		tab->text.render(renderer);
		closeIcon(renderer, {0, 0}, fontSize.y);

		++tabIndex;
	}

}

void Tabs::addTab(Tab* tab)
{
	tabs_.push_back(tab);
}
