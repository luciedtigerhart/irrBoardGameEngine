#include "IrrCamera.h"

using namespace IrrBoardGameEngine;

IrrCamera::IrrCamera(ICameraSceneNode *n, bool isManager){
	this->node = n;

	is_manager = isManager;

	if(is_manager)
	{
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
		is_move = false;
		is_focused = false;
		is_reset = false;
	}
	
	init_Trans = m_Trans = n->getAbsolutePosition();
	init_LookAt = m_LookAt = n->getTarget();
}

IrrCamera::~IrrCamera(void)
{
}

vector3df IrrCamera::getPositionOnSphere( f32 angleH, f32 angleV, f32 radius )
{
	//std::cout << angleH << " " << angleV << " " << radius << std::endl;
	
	//Limit Y angle to avoid Z-axis flipping
	if(angleV > 1.4f)
	{
		angleV = 1.4f;
		m_Rot.X = angleV;
	}
	else if (angleV < -1.4f)
	{
		angleV = -1.4f;
		m_Rot.X = angleV;
	}

	//Limit radius (zooming) to avoid Z-axis flipping
	//and to prevent camera from going too far
	if (radius < 2.0f)
	{
		radius = 2.0f;
		m_Rad = radius;
	}
	else if (radius > 25.0f)
	{
		radius = 25.0f;
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
	m_LookAt.Y = v.y;
	m_LookAt.Z = v.z;

	this->node->setTarget(m_LookAt);
}

void IrrCamera::updateVectors()
{
    vector3df camTarget = this->node->getTarget();
    vector3df camPosition = this->node->getAbsolutePosition();
    vector3df camDirection = camTarget - camPosition;

	vector3df worldDownVector(0.0f, -1.0f, 0.0f);
	vector3df worldUpVector(0.0f, 1.0f, 0.0f);

    leftVector = worldDownVector.crossProduct(camDirection);
	rightVector = worldUpVector.crossProduct(camDirection);

	upVector = leftVector.crossProduct(camDirection);
	downVector = rightVector.crossProduct(camDirection);

	forwardVector = upVector.crossProduct(leftVector);
	backwardVector = upVector.crossProduct(rightVector);
}

void IrrCamera::update()
{
	if(is_manager)
	{
		updateVectors();

		if (is_focused) this->node->setTarget( focus_LookAt );
		else this->node->setTarget( m_LookAt );

		if (!is_move && !is_focused)
		{
			this->node->getParent()->setPosition(m_LookAt); //Parent node is the rotation sphere center

			m_Trans = getPositionOnSphere( m_Rot.Y, m_Rot.X, m_Rad );
		}
		else if (is_focused) this->node->getParent()->setPosition(focus_LookAt);

		if (is_focused) this->node->setPosition( focus_Trans );
		else this->node->setPosition( m_Trans );
		
		this->node->updateAbsolutePosition();
	}
}

void IrrCamera::reset()
{
	if (!is_reset)
	{
		m_Trans = init_Trans;
		m_LookAt = init_LookAt;

		is_reset = true;
	}
}

void IrrCamera::moveForward(f32 speed)
{
    vector3df camMovement = forwardVector.normalize();
    camMovement = camMovement * speed;
	
	m_Trans = this->node->getPosition() + camMovement;
	m_LookAt = this->node->getTarget() + camMovement;

	//Camera has moved, so enable resetting
	is_reset = false;
}

void IrrCamera::moveBackward(f32 speed)
{
    vector3df camMovement = backwardVector.normalize();
    camMovement = camMovement * speed;
	
	m_Trans = this->node->getPosition() + camMovement;
	m_LookAt = this->node->getTarget() + camMovement;

	//Camera has moved, so enable resetting
	is_reset = false;
}

void IrrCamera::moveRight(f32 speed)
{
	vector3df camMovement = rightVector.normalize();
    camMovement = camMovement * speed;
 
	m_Trans = this->node->getPosition() + camMovement;
	m_LookAt = this->node->getTarget() + camMovement;

	//Camera has moved, so enable resetting
	is_reset = false;
}

void IrrCamera::moveLeft(f32 speed)
{
	vector3df camMovement = leftVector.normalize();
    camMovement = camMovement * speed;
 
	m_Trans = this->node->getPosition() + camMovement;
	m_LookAt = this->node->getTarget() + camMovement;

	//Camera has moved, so enable resetting
	is_reset = false;
}

void IrrCamera::moveUp(f32 speed)
{
	vector3df camMovement = upVector.normalize();
	camMovement = camMovement * speed;

	m_Trans = this->node->getPosition() + camMovement;
	m_LookAt = this->node->getTarget() + camMovement;

	//Camera has moved, so enable resetting
	is_reset = false;
}

void IrrCamera::moveDown(f32 speed)
{
	vector3df camMovement = downVector.normalize();
	camMovement = camMovement * speed;

	m_Trans = this->node->getPosition() + camMovement;
	m_LookAt = this->node->getTarget() + camMovement;

	//Camera has moved, so enable resetting
	is_reset = false;
}

void IrrCamera::setFocus(vector3df position, vector3df lookAt)
{
	focus_Trans = position;
	focus_LookAt = lookAt;
}