#include "MoveDocument.h"

#include <iostream>

#include "math/Math.h"

void MoveDocument::eventHandler(const SDL_Event* e)
{
	gamePad(e);
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		mouseIsDown_ = false;
	}

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		pos_.x = static_cast<float>(e->motion.x);
		pos_.y = static_cast<float>(e->motion.y);
		pos_ -= document_->pos();

		mouseIsDown_ = true;
	}

	if (e->type == SDL_MOUSEMOTION)
	{
		mousePos_.x = static_cast<float>(e->motion.x);
		mousePos_.y = static_cast<float>(e->motion.y);


		if (mouseIsDown_) {
			document_->pos(mousePos_ - pos_);
		}
	}

	if (e->type == SDL_MOUSEWHEEL) {
		const float oldScale = document_->scale().x;
		const float newScale = e->wheel.preciseY > 0 ? oldScale * 1.1f : oldScale / 1.1f;
		const float scaleDiff = newScale - oldScale;
		math::Vector2D pos = document_->pos();

		pos -= ((mousePos_ - pos) / oldScale) * scaleDiff;
		document_->scale({ newScale , newScale });
		document_->pos(pos);
		document_->isModified(true);
	}

}

void MoveDocument::gamePad(const SDL_Event* e)
{
	if (SDL_NumJoysticks() < 1)
	{
		return;
	}

	const auto gGameController = SDL_JoystickOpen(0);
	if (gGameController == nullptr)
	{
		printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
	}

	if (e->type == SDL_JOYAXISMOTION)
	{
		auto value = -(static_cast<float>(e->jaxis.value) / 32768);
		if (abs(value) < .1) value = 0;
		
		if (e->jaxis.axis == 0)
		{
			move_.x = value;
		}
		if (e->jaxis.axis == 1)
		{
			move_.y = value;
		}

		if (e->jaxis.axis == 3)
		{
			zoom_.y = value;
			zoomChange_ = true;
		}

	}
	else
	{
		zoomChange_ = false;
	}

}

void MoveDocument::update()
{
	math::Vector2D pos = document_->pos();
	math::Vector2D scale = document_->scale();


	const auto newScale = scale * (1 + zoom_.y / 20);
	const float scaleDiff = newScale.x - scale.x;

	const auto point = document_->size() / 2;

	pos += move_ / (scale / 20);
	pos -= ((point - pos) / scale) * scaleDiff;

	document_->pos(pos);
	document_->scale(newScale);

}
