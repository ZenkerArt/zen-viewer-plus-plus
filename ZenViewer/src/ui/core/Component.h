#pragma once
#include "SDL.h"
#include "core/Window.h"
#include "math/Rect.h"

namespace ui {
	class Component
	{
		bool isEnable_ = true;
		bool isVisible_ = true;
		bool isModified_ = false;
		const Component* parent_ = nullptr;
		math::Vector2D scale_{ 1, 1 };
		math::Rect rect_{ 0, 0, 0, 0 };
	protected:
		Window* window_ = nullptr;

		virtual void onMount();
		virtual void onDestroy();

		virtual void onEnable();
		virtual void onDisable();

		virtual void onUpdate();
		virtual void onRender(SDL_Renderer* renderer);
		virtual void onLateUpdate();

		virtual void onVisible();
		virtual void onInvisible();
	public:
		Component() = default;

		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;

		Component(Component&&) = delete;
		Component& operator=(Component&&) = delete;

		virtual ~Component();

		virtual void mount();
		virtual void destroy();

		virtual void update();
		virtual void render(SDL_Renderer* renderer);
		virtual void lateUpdate();

		virtual void isEnable(bool state);
		[[nodiscard]] bool isEnable() const;

		virtual void isVisible(bool state);
		[[nodiscard]] bool isVisible() const;

		virtual void isModified(bool state);
		[[nodiscard]] virtual bool isModified() const;

		virtual void parent(const Component* p);
		[[nodiscard]] const Component* parent() const;

		[[nodiscard]] math::Rect rect() const;
		[[nodiscard]] math::Rect absoluteRect() const;

		[[nodiscard]] math::Vector2D absoluteSize() const;
		[[nodiscard]] math::Vector2D size() const;
		void size(math::Vector2D newSize);
		void size(float w, float h);

		[[nodiscard]] math::Vector2D absolutePos() const;
		[[nodiscard]] math::Vector2D pos() const;
		void pos(math::Vector2D newPos);
		void pos(float x, float y);

		[[nodiscard]] math::Vector2D absoluteScale() const;
		[[nodiscard]] math::Vector2D scale() const;
		void scale(math::Vector2D newScale);
		void scale(float x, float y);

		[[nodiscard]] Window* window();
		void window(Window* window);
	};

}
