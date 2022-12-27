#pragma once
#include "ui/core/ComponentList.h"

class DebugComponent final : ui::ComponentWithChildren
{
protected:
	void onRender(SDL_Renderer* renderer) override;
};

