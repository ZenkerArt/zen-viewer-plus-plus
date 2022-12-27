#include "HBox.h"

void ui::HBox::onUpdate()
{
	float height = 0;
	float width = 0;
	for (const auto component : components_)
	{
		const auto scale = component->absoluteScale();
		const auto size = component->size();
		const auto w = size.x * scale.x;

		component->pos(0, height);
		height += (size.y + spacing_) * scale.y;

		if (w > width)
			width = w;

		component->update();
	}
	//std::cout << width << std::endl;
	size(width, height);
}

float ui::HBox::spacing() const
{
	return spacing_;
}

void ui::HBox::spacing(const float space)
{
	spacing_ = space;
}
