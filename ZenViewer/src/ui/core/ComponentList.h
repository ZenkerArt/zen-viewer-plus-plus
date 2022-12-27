#pragma once
#include <list>

#include "Component.h"

namespace ui
{
	class ComponentWithChildren : public Component
	{

	protected:
		std::list<Component*> components_;
		void onMount() override;
		void onDestroy() override;
		void onUpdate() override;
		void onRender(SDL_Renderer* renderer) override;
		void onLateUpdate() override;
	public:
		~ComponentWithChildren() override;
		void isModified(bool state) override;
		[[nodiscard]] bool isModified() const override;

		virtual std::list<Component*> components();

		virtual Component* add(Component* component);
		virtual Component* remove(Component* component);
		void destroy() override;
		
	};
	class ComponentList final : public ComponentWithChildren {};
}

