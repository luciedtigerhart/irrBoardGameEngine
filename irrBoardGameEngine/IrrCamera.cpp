#include "IrrCamera.h"

using namespace IrrBoardGameEngine;

IrrCamera::IrrCamera(ICameraSceneNode *n){
	this->node = n;

	vector3df origin(0,0,0);
	vector3df xz_origin(0,0,1);
	vector3df xy_origin(0,1,0);
	vector3df pos(n->getTarget().X, n->getTarget().Y, n->getTarget().Z);
	vector3df xz_pos(n->getAbsolutePosition().X, n->getTarget().Y, n->getAbsolutePosition().Z);
	vector3df xy_pos(n->getTarget().X, n->getAbsolutePosition().Y, n->getAbsolutePosition().Z);

	vector3df vec_xz_origin = xz_origin - origin;
	vector3df vec_xy_origin = xy_origin - origin;
	vector3df vec_xz_pos = xz_pos - pos;
	vector3df vec_xy_pos = xy_pos - pos;

	f32 norm_vec_xz_origin = sqrt((vec_xz_origin.X * vec_xz_origin.X) + (vec_xz_origin.Y * vec_xz_origin.Y) + (vec_xz_origin.Z * vec_xz_origin.Z));
	f32 norm_vec_xy_origin = sqrt((vec_xy_origin.X * vec_xy_origin.X) + (vec_xy_origin.Y * vec_xy_origin.Y) + (vec_xy_origin.Z * vec_xy_origin.Z));
	f32 norm_vec_xz_pos = sqrt((vec_xz_pos.X * vec_xz_pos.X) + (vec_xz_pos.Y * vec_xz_pos.Y) + (vec_xz_pos.Z * vec_xz_pos.Z));
	f32 norm_vec_xy_pos = sqrt((vec_xy_pos.X * vec_xy_pos.X) + (vec_xy_pos.Y * vec_xy_pos.Y) + (vec_xy_pos.Z * vec_xy_pos.Z));
		
	m_Rot.Y = acosf( vec_xz_origin.dotProduct(vec_xz_pos) / (norm_vec_xz_origin * norm_vec_xz_pos) );
	if (n->getAbsolutePosition().X < 0.0f) m_Rot.Y = 6.28f - m_Rot.Y;

	m_Rot.X = acosf( vec_xy_origin.dotProduct(vec_xy_pos) / (norm_vec_xy_origin * norm_vec_xy_pos) );

	m_Rad = n->getAbsolutePosition().getDistanceFrom(n->getTarget());
    m_Dragging = false;
}


IrrCamera::~IrrCamera(void)
{
}

vector3df IrrCamera::getPositionOnSphere( f32 angleH, f32 angleV, f32 radius )
{
	//std::cout << angleH << " " << angleV << " " << radius << std::endl;
	
	//Limit Y angle
	if(angleV > 1.4f)
	{
		angleV = 1.4f;
		m_Rot.X = angleV;
	}
	else if (angleV < 0.2f)
	{
		angleV = 0.2f;
		m_Rot.X = angleV;
	}

	//Limit radius (zooming)
	if (radius < 8.5f)
	{
		radius = 8.5f;
		m_Rad = radius;
	}
	else if (radius > 35.0f)
	{
		radius = 35.0f;
		m_Rad = radius;
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

	//std::cout<<"after: "<<camPos.X<<", "<<camPos.Y<<", "<<camPos.Z<<std::endl;

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