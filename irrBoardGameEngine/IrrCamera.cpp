#include "IrrCamera.h"

using namespace IrrBoardGameEngine;

IrrCamera::IrrCamera(ICameraSceneNode *n){
	this->node = n;
	
	m_Rot.Y = n->getPosition().Y;
	m_Rot.X = n->getPosition().X;

	m_Rad = 32;
    m_Dragging = false;
}


IrrCamera::~IrrCamera(void)
{
}

vector3df IrrCamera::getPositionOnSphere( f32 angleH, f32 angleV, f32 radius )
{
	//std::cout << angleH << " " << angleV << " " << radius << std::endl;
	if(angleV > 20)
	{
		angleV = 20;
		m_Rot.X = angleV;
	}
	else if (angleV < 19)
	{
		angleV = 19;
		m_Rot.X = angleV;
	}
	// Get position on Z/Y Plane using conversion from polar
    // to cartesian coordinates
    f32 posZ = radius * cos( angleV );
    f32 posY = radius * sin( angleV );

    // Create a positional vector with X=0
    vector3df camPos( 0, posY, posZ );

    // Create a transformation matrix to rotate the vector 'camPos'
    // around the Y Axis
	m_Trans.X = 2;

    matrix4 yawMat;
    yawMat.setRotationRadians( vector3df( 0, angleH, 0 ));
	yawMat.transformVect( camPos );	

	//camPos.X += m_Trans.X;
	//camPos.Z += m_Trans.Z;
	//camPos.Y += m_Trans.Y;

    return camPos;
}

void IrrCamera::dumpVector( const vector3df &vec )
{
    //std::cout << "vec: [ X = " << vec.X << " Y = " << vec.Y << " Z = " << vec.Z << "]" << std::endl;
}

void IrrCamera::lookAt(Vector &v)
{
	m_LookAt.X = v.x;
	m_LookAt.X = v.y;
	m_LookAt.X = v.z;
}

void IrrCamera::update()
{
	this->node->setTarget(m_LookAt);
	this->node->setPosition( getPositionOnSphere( m_Rot.Y, m_Rot.X, m_Rad ));
}

void IrrCamera::move()
{
	this->node->setTarget(m_LookAt);
}