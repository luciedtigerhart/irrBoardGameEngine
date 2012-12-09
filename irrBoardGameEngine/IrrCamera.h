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
		vector3df init_Trans;
		vector3df init_LookAt;

		vector3df getPositionOnSphere( f32 angleH, f32 angleV, f32 radius );
		void dumpVector( const vector3df &vec );

	public:
		IrrCamera(ICameraSceneNode *, bool isManager = false);
		void lookAt(Vector&);

		ICameraSceneNode *node;
		~IrrCamera(void);

		//
		// Atualizações de valores
		//
		void updateVectors();
		void update();
		void reset();

		//
		// Responsavel pela movimentação
		//
		void moveForward(f32 speed);
		void moveBackward(f32 speed);
		void moveRight(f32 speed);
		void moveLeft(f32 speed);
		void moveUp(f32 speed);
		void moveDown(f32 speed);
		void setFocus(vector3df position, vector3df lookAt);

		//
		// Controle de estado
		//
		bool is_move;
		bool is_manager;
		bool is_focused;
		bool is_reset;
		bool m_Dragging;

		//
		// Usado para o calculo do posicionamento da camera
		//
		f32 m_Rad;
		vector2df m_DragStart;
		vector3df focus_Trans;
		vector3df focus_LookAt;
		vector3df m_Trans;
		vector3df m_LookAt;
		vector3df m_Rot;		
		vector3df m_DragStartRotation;

		vector3df forwardVector;
		vector3df backwardVector;
		vector3df rightVector;
		vector3df leftVector;
		vector3df upVector;
		vector3df downVector;
	};
}