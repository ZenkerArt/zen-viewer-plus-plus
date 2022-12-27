#include "ComponentList.h"


void ui::ComponentWithChildren::onMount()
{
	Component::onMount();
	for (auto const component : components_)
	{
		component->mount();
	}
}

void ui::ComponentWithChildren::onDestroy()
{
	Component::onDestroy();
	for (auto const component : components_)
	{
		component->destroy();
		//remove(component);
	}
}

void ui::ComponentWithChildren::onUpdate()
{
	Component::onUpdate();

	for (auto const component : components_)
	{
		component->update();
	}
}

void ui::ComponentWithChildren::onRender(SDL_Renderer* renderer)
{
	Component::onRender(renderer);
	for (auto const component : components_)
	{
		component->render(renderer);
	}
}

void ui::ComponentWithChildren::onLateUpdate()
{
	Component::onLateUpdate();
	for (auto const component : components_)
	{
		component->lateUpdate();
	}
}

ui::ComponentWithChildren::~ComponentWithChildren()
{
	Component::destroy();
	for (auto const component : components_)
	{
		delete component;
	}
}

void ui::ComponentWithChildren::isModified(bool state)
{
	Component::isModified(state);
}

bool ui::ComponentWithChildren::isModified() const
{
	for (auto const component : components_)
	{
		if (component->isModified())
		{
			return true;
		}
	}

	return Component::isModified();
}

std::list<ui::Component*> ui::ComponentWithChildren::components()
{
	return components_;
}


ui::Component* ui::ComponentWithChildren::add(Component* component)
{
	components_.push_back(component);
	component->window(window_);
	component->parent(parent() != nullptr ? parent() : this);
	component->mount();
	return component;
}


ui::Component* ui::ComponentWithChildren::remove(Component* component)
{
	components_.remove(component);
	component->parent(nullptr);
	return component;
}

void ui::ComponentWithChildren::destroy()
{
	Component::destroy();
	onDestroy();
}
