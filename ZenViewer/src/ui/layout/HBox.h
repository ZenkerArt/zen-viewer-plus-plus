#pragma once
#include "ui/core/ComponentList.h"

namespace ui
{
	class HBox final : public ComponentWithChildren
	{
		void onUpdate() override;
		float spacing_ = 0;
	public:
		[[nodiscard]] float spacing() const;
		void spacing(float space);
	};
}

