#include "IrrCamera.h"

using namespace IrrBoardGameEngine;

IrrCamera::IrrCamera(ICameraSceneNode *n){
	this->node = n;
	
	m_Rot.Y = -50;
	m_Rot.X = -50;

	m_Rad = 32;
    m_Dragging = false;
}


IrrCamera::~IrrCamera(void)
{
}

vector3df IrrCamera::getPositionOnSphere( f32 angleH, f32 angleV, f32 radius )
{
	// Get position on Z/Y Plane using conversion from polar
    // to cartesian coordinates
    f32 posZ = radius * cos( angleV );
    f32 posY = radius * sin( angleV );

    // Create a positional vector with X=0
    vector3df camPos( 0, posY, posZ );

    // Create a transformation matrix to rotate the vector 'camPos'
    // around the Y Axis
    matrix4 yawMat;
    yawMat.setRotationRadians( vector3df( 0, angleH, 0 ));
    yawMat.transformVect( camPos );

    //dumpVector( camPos );

    return camPos;
}

void IrrCamera::dumpVector( const vector3df &vec )
{
    std::cout << "vec: [ X = " << vec.X << " Y = " << vec.Y << " Z = " << vec.Z << "]" << std::endl;
}

void IrrCamera::lookAt(Vector &v)
{
	this->node->setTarget(vector3df(v.x,v.y,v.z));
}

void IrrCamera::update()
{	
	this->node->setPosition( getPositionOnSphere( m_Rot.Y, m_Rot.X, m_Rad ));
}