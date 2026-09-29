#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Scene
{
public:
	// These functions act as game loop functions, classes can override them if needed
	virtual void Update( Keyboard& kbd,Mouse& mouse,float dt ) = 0;
	virtual void Draw( Graphics& gfx ) const = 0;
	virtual ~Scene() = default;
};