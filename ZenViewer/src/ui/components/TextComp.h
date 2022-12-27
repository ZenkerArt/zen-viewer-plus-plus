#pragma once
#include <SDL_ttf.h>

#include "ui/core/Component.h"

namespace ui
{
	class TextComp final : public Component
	{
	protected:
		void onMount() override;
		void onRender(SDL_Renderer* renderer) override;
		void onDestroy() override;
		void onVisible() override;
		void onInvisible() override;

		TTF_Font* font_ = nullptr;
		SDL_Texture* texture_ = nullptr;
		int fz_ = 10;
		std::string* text_ = nullptr;
		int clip_ = 0;
	public:
		[[nodiscard]] int clip() const;
		void clip(int width);

		[[nodiscard]] int fontSize() const;
		void fontSize(int fz);

		[[nodiscard]] std::string text() const;
		void text(std::string* ftext);
		void text(std::string ftext);
	};
}

