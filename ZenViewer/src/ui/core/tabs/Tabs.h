#pragma once
#include "Tab.h"
#include "ui/core/Component.h"

class Tabs final: public ui::Component
{
	list<Tab*> tabs_;

	void onRender(SDL_Renderer* renderer) override;
public:
	void addTab(Tab* tab);
};

