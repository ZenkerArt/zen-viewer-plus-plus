#include "ImageGridComp.h"
#include <vector>

#include "math/Math.h"
#include "core/image/ImageLoader.h"

void ui::ImageGridComp::onUpdate()
{
	int colsIterate = 0;
	int rowIterate = 0;

	std::vector<std::vector<float>> sizes;

	const float width = (parent()->absoluteSize().x / columnCount_);

	for (float i = 0; i < columnCount_; ++i)
	{
		sizes.emplace_back();
	}
	int ids = 0;
	for (const auto image : images_)
	{
		if (image->isVisible())
		{
			ids += image->image()->id;
		}
		const auto natureSize = image->getNatureSize();
		const auto height = width * (natureSize.y / natureSize.x);

		float y;

		if (sizes[colsIterate].empty()) {
			y = 0;
		}
		else {
			y = sizes[colsIterate][rowIterate - 1];
		}

		image->size(width, height);
		image->pos(width * colsIterate, y);
		image->update();
		sizes[colsIterate].push_back(y + height);

		colsIterate++;
		if (static_cast<float>(colsIterate) >= columnCount_) {
			colsIterate = 0;
			rowIterate++;
		}
	}

	if (hash_ != ids)
	{
		imageLoader->loadImages();
		hash_ = ids;
	}
}

float ui::ImageGridComp::columnCount()
{
	return columnCount_;
}

void ui::ImageGridComp::columnCount(int value)
{

	if (value >= 1)
	{
		columnCount_ = value;
	}
}

