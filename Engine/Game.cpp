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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	cube( 1.0f )
{
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
}

// Renders 3D objects in 2D space
void Game::ComposeFrame()
{
	// Initalise cube vertices and indices
	// This effectively defines how lines connect
	auto lines = cube.GetLines();

	for( auto& v : lines.vertices )
	{
		// Transform the vertex into 2D
		pst.Transform( v );
	}
	for( auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance( i,2 ) ) // Iterate through every 2 indices (every line) (e.g 0,1, 1,2 etc)
	{
		gfx.DrawLine( lines.vertices[*i],lines.vertices[*std::next( i )],Colors::White );
	}
}