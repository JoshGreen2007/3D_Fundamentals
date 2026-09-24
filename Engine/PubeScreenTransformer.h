#pragma once
#include "Vec3.h"
#include "Graphics.h"

class PubeScreenTransformer
{
public:
	PubeScreenTransformer()
		:
		xFactor( float( Graphics::ScreenWidth ) / 2.0f ),
		yFactor( float( Graphics::ScreenHeight ) / 2.0f )
	{}
	Vec3& Transform( Vec3& v ) const
	{
		// We add 1 to go from [-1, 1] to [0, 1] screen format
		v.x = (v.x + 1.0f) * xFactor;
		v.y = (-v.y + 1.0f) * yFactor; // y is negative in 2D
		return v;
	}
	Vec3 GetTransformed( const Vec3& v ) const
	{
		return Transform( Vec3( v ) );
	}
private:
	float xFactor;
	float yFactor;
};