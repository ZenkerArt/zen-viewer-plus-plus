#pragma once
#include "ui/components/ImageComp.h"
#include "ui/core/ComponentList.h"

namespace ui
{
	class ImageLayout : public ui::ComponentWithChildren
	{
	protected:
		std::list<ImageComp*> images_;
	public:
		std::list<ImageComp*> images();
		Component* addImage(ImageComp* image);
		void removeImage(ImageComp* image);
	};
}

