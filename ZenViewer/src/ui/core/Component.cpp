#include "Component.h"
#include "math/Math.h"

namespace ui
{
	void Component::onMount()
	{
	}

	void Component::onDestroy()
	{
	}

	void Component::onEnable()
	{
	}

	void Component::onDisable()
	{
	}

	void Component::onUpdate()
	{
	}

	void Component::onRender(SDL_Renderer* renderer)
	{
	}

	void Component::onLateUpdate()
	{
	}

	void Component::onVisible()
	{
	}

	void Component::onInvisible()
	{
	}

	Component::~Component()
	{
		Component::destroy();
	}

	void Component::mount()
	{
		onMount();
	}

	void Component::destroy()
	{
		onDestroy();
	}

	void Component::update()
	{
		if (!isEnable_) return;
		onUpdate();
	}

	void Component::render(SDL_Renderer* renderer)
	{
		if (!isEnable_) return;
		onRender(renderer);
	}

	void Component::lateUpdate()
	{
		onLateUpdate();
		isModified_ = false;
	}

	void Component::isEnable(const bool state)
	{
		if (state == isEnable_) return;
		isEnable_ = state;
		state ? onEnable() : onDisable();
	}

	bool Component::isEnable() const
	{
		return isEnable_;
	}

	void Component::isVisible(const bool state)
	{
		if (state == isVisible_) return;
		isVisible_ = state;
		state ? onVisible() : onInvisible();
	}

	bool Component::isVisible() const
	{
		return isVisible_;
	}

	void Component::isModified(const bool state)
	{
		isModified_ = true;
	}

	bool Component::isModified() const
	{
		return isModified_;
	}

	void Component::parent(const Component* p)
	{
		parent_ = p;
	}

	const Component* Component::parent() const
	{
		return parent_;
	}

	math::Rect Component::rect() const
	{
		return rect_;
	}

	math::Rect Component::absoluteRect() const
	{
		if (parent_ != nullptr)
		{
			const auto sscale = absoluteScale();
			return math::Rect{
			rect_.x + parent_->rect().x,
			rect_.y + parent_->rect().y,
			rect_.w * sscale.x,
			rect_.h * sscale.y
			};
		}
		return rect_ * scale_;
	}

	math::Vector2D Component::absoluteSize() const
	{
		const auto r = absoluteRect();
		return math::Vector2D{ r.w, r.h };
	}

	math::Vector2D Component::size() const
	{
		const auto r = rect();
		return math::Vector2D{ r.w, r.h };
	}

	void Component::size(const math::Vector2D newSize)
	{
		isModified(
			static_cast<int>(rect_.w) != static_cast<int>(newSize.x) &&
			static_cast<int>(rect_.h) != static_cast<int>(newSize.y));

		rect_.w = newSize.x;
		rect_.h = newSize.y;
	}

	void Component::size(const float w, const float h)
	{
		isModified(
			static_cast<int>(rect_.w) != static_cast<int>(w) &&
			static_cast<int>(rect_.h) != static_cast<int>(h));

		rect_.w = w;
		rect_.h = h;
	}

	math::Vector2D Component::absolutePos() const
	{
		const auto r = absoluteRect();
		return math::Vector2D{ r.x, r.y };
	}

	math::Vector2D Component::pos() const
	{
		const auto r = rect();
		return math::Vector2D{ r.x, r.y };
	}

	void Component::pos(const math::Vector2D newPos)
	{
		isModified(
			static_cast<int>(rect_.x) != static_cast<int>(newPos.x) &&
			static_cast<int>(rect_.y) != static_cast<int>(newPos.y));

		rect_.x = newPos.x;
		rect_.y = newPos.y;
	}

	void Component::pos(const float x, const float y)
	{
		isModified(static_cast<int>(rect_.x) != static_cast<int>(x) &&
			static_cast<int>(rect_.y) != static_cast<int>(y));

		rect_.x = x;
		rect_.y = y;
	}

	math::Vector2D Component::absoluteScale() const
	{
		return parent_->scale() + (scale_ - 1);
	}

	math::Vector2D Component::scale() const
	{
		return scale_;
	}

	void Component::scale(const math::Vector2D newScale)
	{
		isModified(scale_ != newScale);
		scale_.x = newScale.x;
		scale_.y = newScale.y;
	}

	void Component::scale(const float x, const float y)
	{
		isModified(scale_ != math::Vector2D{ x, y });
		scale_.x = x;
		scale_.y = y;
	}

	Window* Component::window()
	{
		return window_;
	}

	void Component::window(Window* window)
	{
		window_ = window;
	}
}
