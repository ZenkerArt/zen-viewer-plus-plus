#pragma once
#include <SDL_events.h>

#include "math/Vector2D.h"
#include "ui/core/Document.h"

class MoveDocument
{
	bool mouseIsDown_ = false;
	math::Vector2D pos_;
	math::Vector2D mousePos_;

	math::Vector2D move_;
	bool zoomChange_;
	math::Vector2D zoom_;

	ui::Document* document_;

public:
	explicit MoveDocument(ui::Document* document) : document_(document) {}

	void eventHandler(const SDL_Event* e);
	void gamePad(const SDL_Event* e);
	void update();


};
