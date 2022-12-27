#pragma once
#include <any>

#include "Image.h"
#include <vector>
#include <wtypes.h>
#include <mutex>
#include <condition_variable>

#include "ui/layout/ImageLayout.h"

using namespace std;
namespace fs = filesystem;

class ImageLoader
{
	mutex imageLoaderMtx_;
	condition_variable imageLoaderCv_{};

	mutex originalLoaderMtx_;
	condition_variable originalLoaderCv_{};
	Uint32 lastUpdate_ = 0;
	Uint32 lastMemoryClear_ = 0;
	unsigned int idCounter_ = 0;
	bool isImageLoad_ = false;

	TCHAR* path_{};
	vector<TCHAR*> filesPath_;
	SDL_Renderer* render_;
	bool isLoading_ = false;
	bool isUpdate_ = false;

protected:
	void threadImageLoader();
	void threadOriginalLoader();
	void addImage(Image* image);
public:
	ui::ImageLayout* images = nullptr;

	ImageLoader();
	~ImageLoader();
	bool loadFolder(TCHAR* path);
	void loadFiles(const std::vector<TCHAR*>& files);
	void loadImages();
	void update();
	

	void destroy();
};


