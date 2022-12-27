#pragma once
#include "MoveDocument.h"
#include "core/Window.h"
#include "core/image/ImageLoader.h"
#include "ui/components/ImageGridComp.h"
#include "ui/components/TextComp.h"
#include "ui/core/Document.h"

class Tab final: public ui::Component
{
	Window* window_ = nullptr;
	SDL_Renderer* render_ = nullptr;
	ui::Document document_ = ui::Document{};
	DWORD lastUpdate_ = 0;
	ui::ImageGridComp imageGrid_{};
	MoveDocument* moveDocument_ = nullptr;

	void onMount() override;
	void onUpdate() override;
	void onDestroy() override;
	void onRender(SDL_Renderer* renderer) override;
public:
	ui::TextComp text{};
	explicit Tab(Window* win, ImageLoader* imageLoader);
	void event(const SDL_Event* e);
	bool isModified() const override;
};

