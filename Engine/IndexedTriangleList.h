#pragma once

#include <vector>
#include <cassert>
#include "Vec3.h"

struct IndexedTriangleList
{
	IndexedTriangleList( std::vector<Vec3> verts_in,std::vector<size_t> indices_in )
		:
		vertices( std::move( verts_in ) ),
		indices( std::move( indices_in ) )
	{
      // Ensure we have at least three vertices to form a triangle.
		// `verts_in` was moved into the member `vertices` in the initializer,
		// so check `vertices` here (not the undefined `verts`).
		assert( vertices.size() > 2 ); // Assert vertices
		assert( indices.size() % 3 == 0 ); // Assert indices ensuring they make sense (3 indices for triangle)
		cullFlags.resize( indices.size() / 3,false ); // These flags indicate what triangles shouldn't be drawn
	}
	std::vector<Vec3> vertices;
	std::vector<size_t> indices;
	std::vector<bool> cullFlags;
};