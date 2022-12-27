#include "ImageLayout.h"

#include <iostream>

#include "ui/components/ImageComp.h"


std::list<ui::ImageComp*> ui::ImageLayout::images()
{
	return images_;
}

ui::Component* ui::ImageLayout::addImage(ImageComp* image)
{
	add(image);
	images_.push_back(image);
	return image;
}

void ui::ImageLayout::removeImage(ImageComp* image)
{
	remove(image);
	images_.remove(image);
}