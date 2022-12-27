#pragma once
#include "ui/core/Component.h"
#include "core/image/Image.h"

class DropManager;

namespace ui {
	class ImageComp final : public Component
	{
		Image* image_ = nullptr;
		math::Vector2D size_;
		math::Vector2D pos_;

		void onRender(SDL_Renderer* renderer) override;
		void onDisable() override;
		void onVisible() override;
		void onInvisible() override;
		void onEnable() override;
		void onDestroy() override;
	public:
		bool hasImage = false;

		explicit ImageComp(Image* image) : image_(image)
		{
			size(image->getNatureSize());
		}

		void loadResolution();

		[[nodiscard]] math::Vector2D getNatureSize() const;
		[[nodiscard]] Image* image() const;
	};
}
