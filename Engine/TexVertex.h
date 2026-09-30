#pragma once

#include "Vec2.h"
#include "Vec3.h"

// TexVertex
// A small POD used to carry per-vertex data needed for textured rendering.
//
// This class holds the 3D position of a vertex (`pos`) and a 2D texture
// coordinate (`tc`, often called U,V or S,T). During rasterization the
// pipeline will interpolate instances of `TexVertex` across the surface of
// a triangle to produce per-pixel values used by the fragment/shader stage.
//
// Important notes about texture mapping (conceptual, handled elsewhere):
// - Interpolation: `InterpolateTo` linearly interpolates both position and
//   texture coordinates. For correct perspective-correct texturing the
//   rasterizer should perform interpolation in screen space using 1/w
//   (i.e. interpolate tc/w and 1/w, then divide). This class only provides
//   a convenience for simple linear interpolation between two vertices.
// - Sampling: How a texture is sampled (nearest/linear filtering, mipmaps,
//   wrapping or clamping) is the responsibility of the texture sampling code
//   (texture class or shader). `tc` simply carries the texture coordinate
//   to that stage.
// - Coordinate convention: `tc.x` is typically U (horizontal) and `tc.y` is
//   typically V (vertical). Depending on the texture system an origin may be
//   top-left or bottom-left; the rest of the engine must use a consistent
//   convention.
class TexVertex
{
public:
	// Create a TexVertex from a 3D position and 2D texture coordinate.
	TexVertex( const Vec3& pos,const Vec2& tc )
		:
		pos( pos ),
		tc( tc )
	{}

	// Linearly interpolate this vertex towards `dest` by `alpha` in range
	// [0,1]. Returns a new TexVertex whose fields are the per-component
	// interpolations of `pos` and `tc`.
	//
	// Note: This is plain linear interpolation. For correct texture mapping
	// across a projected triangle you typically need perspective-correct
	// interpolation which must be implemented at the rasterization stage.
	TexVertex InterpolateTo( const TexVertex& dest,float alpha ) const
	{
		return {
			pos.InterpolateTo( dest.pos,alpha ),
			tc.InterpolateTo( dest.tc,alpha )
		};
	}

	Vec3 pos; // 3D position in whatever space the pipeline expects (model/view/clip)
	Vec2 tc;  // 2D texture coordinate (U,V) passed to the sampler
};
