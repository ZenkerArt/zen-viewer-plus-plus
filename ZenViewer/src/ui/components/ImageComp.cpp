#include "ImageComp.h"

#include "math/Math.h"

void ui::ImageComp::onRender(SDL_Renderer* renderer)
{
	size_ = aLerp(size_, size(), .3f);
	pos_ = aLerp(pos_, absolutePos(), .3f);
	if (size_ != size()) {
		isModified(true);
	}

	image_->draw(renderer, pos_, size_);
	image_->loadTexture(renderer);
}

void ui::ImageComp::onDisable()
{
	image_->destroy();
}

void ui::ImageComp::onVisible()
{
	Component::isEnable(true);
}

void ui::ImageComp::onInvisible()
{
	Component::isEnable(false);
	image_->destroy();
	hasImage = false;
}

void ui::ImageComp::onEnable()
{
	size_.y = 0;
	pos_ = absolutePos();
	pos_.y -= 100;
}

void ui::ImageComp::onDestroy()
{
	image_->destroy();
}

void ui::ImageComp::loadResolution()
{
	image_->loadResolution();
}

math::Vector2D ui::ImageComp::getNatureSize() const
{
	return image_->getNatureSize();
}

Image* ui::ImageComp::image() const
{
	return image_;
}
