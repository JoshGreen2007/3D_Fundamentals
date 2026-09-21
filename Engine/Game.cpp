/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Mat2.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
    // Build the base star shape in model (local) space.
	// The star is represented as a sequence of 2D points (`Vec2`) stored in `star`.
	// We create `nflares * 2` vertices where points alternate between an outer
	// radius and an inner radius to produce the flared star spikes.
	// `dTheta` is the angular step between consecutive vertices around the circle.
	const float dTheta = 2.0f * PI / float( nflares * 2 );
	for( int i = 0; i < nflares * 2; i++ )
	{
		// Alternate between outer and inner radius to form the star points.
		const float rad = (i % 2 == 0) ? radOuter : radInner;
		// Place the vertex on the circle at angle (i * dTheta).
		star.emplace_back(
			rad * cos( float( i ) * dTheta ),
			rad * sin( float( i ) * dTheta )
		);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if( !wnd.kbd.KeyIsPressed( VK_SPACE ) )
	{
		theta += vRot;
	}
}

void Game::ComposeFrame()
{
	const Vec2 trl = { float( gfx.ScreenWidth ) / 2.0f,float( gfx.ScreenHeight ) / 2.0f };
	const Mat2 trf = Mat2::Rotation( theta ) * Mat2::Scaling( size );
	auto vtx( star );
	for( auto& v : vtx )
	{
        // Transform each model-space vertex by the combined transform `trf`.
		// `trf` first scales the star (by `size`) then rotates it (by `theta`).
		// After the linear transform we translate the vertex to screen center `trl`.
		v *= trf;
		v += trl;
	}
    // Draw the star by connecting each transformed vertex to the next.
	// The loop iterates from the first vertex to the second-last (`std::prev(vtx.cend())`)
	// and draws a line to the next vertex. Finally, we close the polygon by
	// drawing a line between the last and the first vertex.
	for( auto i = vtx.cbegin(),end = std::prev( vtx.cend() ); i != end; i++ )
	{
		gfx.DrawLine( *i,*std::next( i ),Colors::White );
	}
	gfx.DrawLine( vtx.front(),vtx.back(),Colors::White );
}