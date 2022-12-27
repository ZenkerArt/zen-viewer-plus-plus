#include "ImageLoader.h"

#include <filesystem>
#include <iostream>

#include <exiv2/image.hpp>
#include <windows.h>

bool isSupportFormat(const string& ext)
{
	const vector<std::string> formats{ ".png", ".jpg", ".jpeg", ".tga", ".tiff", ".webp" };
	bool isSupport = false;
	for (const std::string& format : formats) {
		if (!ext.compare(format))
		{
			isSupport = true;
			break;
		}
	}
	return isSupport;
}

ImageLoader::ImageLoader()
{
	thread th(&ImageLoader::threadImageLoader, this);
	th.detach();

	thread th1(&ImageLoader::threadOriginalLoader, this);
	th1.detach();
}

ImageLoader::~ImageLoader()
{
	destroy();
}

void ImageLoader::addImage(Image* image)
{
	image->id = ++idCounter_;
	images->addImage(new ui::ImageComp(image));
}

void ImageLoader::threadImageLoader()
{
	while (true) {
		std::unique_lock lock(imageLoaderMtx_);
		imageLoaderCv_.wait(lock, [this]() {return isLoading_; });
		if (path_)
		{
			for (const auto& entry : fs::directory_iterator(path_)) {
				if (!isSupportFormat(entry.path().extension().string())) continue;
				const auto img = new Image();
				img->setPath(entry);
				addImage(img);
			}

		}
		else
		{
			for (const auto& path : filesPath_) {
				auto entry = fs::directory_entry(path);
				if (!isSupportFormat(entry.path().extension().string())) continue;

				const auto img = new Image();
				img->setPath(fs::directory_entry(entry));
				addImage(img);
			}
		}


		isLoading_ = false;
		cout << images->images().size() << endl;
		for (const auto img : images->images()) {
			img->loadResolution();
			img->isEnable(true);

		}
		cout << "Stop loading" << endl;
	}
}

void ImageLoader::threadOriginalLoader()
{
	while (true) {
		std::unique_lock lock(originalLoaderMtx_);
		originalLoaderCv_.wait(lock);
		cout << "Start Loading" << endl;

		for (const auto& img : images->images()) {
			if (img->isVisible() && !img->hasImage)
			{
				img->isEnable(false);
				img->image()->destroy();
				img->image()->loadOriginal();

				img->hasImage = true;
				img->isModified(true);
				img->isEnable(true);
			}
		}
	}
}

void ImageLoader::loadFiles(const std::vector<TCHAR*>& files)
{
	this->filesPath_ = files;
	isLoading_ = true;
	imageLoaderCv_.notify_one();
}

bool ImageLoader::loadFolder(TCHAR* path)
{
	if (isLoading_) {
		return false;
	}
	destroy();
	this->path_ = path;
	isLoading_ = true;
	imageLoaderCv_.notify_one();
	return true;
}

void ImageLoader::loadImages()
{
	lastUpdate_ = SDL_GetTicks();
	isImageLoad_ = true;
}

void ImageLoader::update()
{
	if (SDL_GetTicks() > lastMemoryClear_ + 2000)
	{
		for (const auto image : images->images())
		{
			if (image->isEnable()) continue;

			image->destroy();
		}

		lastMemoryClear_ = SDL_GetTicks();
	}

	if (SDL_GetTicks() > lastUpdate_ + 100 && isImageLoad_)
	{
		originalLoaderCv_.notify_all();
		isImageLoad_ = false;
	}
}

void ImageLoader::destroy()
{
	for (const auto& image : images->images())
	{
		image->destroy();
		images->removeImage(image);
	}
	idCounter_ = 0;
}

