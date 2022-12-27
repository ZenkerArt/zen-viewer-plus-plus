#pragma once
#include "ui/layout/ImageLayout.h"

class ImageLoader;

namespace ui {

	class ImageGridComp final : public ImageLayout
	{
		void onUpdate() override;
		unsigned int hash_ = 0;
		float columnCount_ = 4;
	public:
		float columnCount();
		void columnCount(int value);

		ImageLoader* imageLoader = nullptr;
	};
}

