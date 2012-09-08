#pragma once

namespace IrrBoardGameEngine {
	class Vector {
	public:
		float x,y,z;
		Vector(float x=0.0f,float y=0.0f,float z=0.0f){ this->x=x; this->y=y;this->z=z;}
	};
}
