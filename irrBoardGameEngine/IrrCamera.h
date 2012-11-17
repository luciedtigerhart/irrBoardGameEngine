#pragma once
#include <iostream>
#include "irrlicht.h"
#include <string.h>
#include "Vector.h"

using namespace irr;
using namespace scene;
using namespace core;

namespace IrrBoardGameEngine {
	class IrrCamera
	{
	private:
		vector3df getPositionOnSphere( f32 angleH, f32 angleV, f32 radius );
		void dumpVector( const vector3df &vec );

	public:
		IrrCamera(ICameraSceneNode *, bool isManager = false);
		void lookAt(Vector&);

		ICameraSceneNode *node;
		~IrrCamera(void);

		void updateVectors();
		void update();
		void move();
		void moveForward(f32 speed);
		void moveBackward(f32 speed);
		void moveRight(f32 speed);
		void moveLeft(f32 speed);
		void moveUp(f32 speed);
		void moveDown(f32 speed);

		bool is_move;
		bool is_manager;

		vector3df m_Trans;
		vector3df m_LookAt;                // 
		vector3df m_Rot;                   // H/V Position of camera on sphere (only X/Y used)
		f32 m_Rad;                         // Radius of sphere
		bool m_Dragging;                   // Is currently dragging?
		vector2df m_DragStart;             // 2D Position on screen where the drag started
		vector3df m_DragStartRotation;     // Rotation when drag started

		vector3df forwardVector;
		vector3df backwardVector;
		vector3df rightVector;
		vector3df leftVector;
		vector3df upVector;
		vector3df downVector;
	};
}