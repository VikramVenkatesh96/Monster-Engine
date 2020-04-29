#include "RigidBody2D.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "Point2D.h"


RigidBody2D::RigidBody2D(GameObject* root, float mass, bool enableGravity, bool enableDrag)
	:mass(mass),
	 enableGravity(enableGravity),
	 enableDrag(enableDrag)
{
	gameObject = root;
	velocity = new Point2D(0, 0);
	netForce = new Point2D(0, 0);
	PhysicsSystem::AddRigidBody(this);
}


RigidBody2D::~RigidBody2D()
{
	delete velocity;
	delete netForce;
}

void RigidBody2D::AddForce(Point2D force)
{
	forces.push_back(force);
}


Point2D* RigidBody2D::GetNetForce()
{
	//Initialize with zero
	netForce->MakeZero();

	//Find resultant force and remove all elements in forces
	while (!forces.empty())
	{
		*netForce += forces.back();
		forces.pop_back();
	}

	return netForce;
}

Point2D * RigidBody2D::GetVelocity()
{
	return velocity;
}


Point2D * RigidBody2D::GetPosition()
{
	return gameObject->position;
}
void RigidBody2D::Start()
{
}
void RigidBody2D::Update()
{
}
void RigidBody2D::SetVelocity(Point2D vel)
{
	velocity->x = vel.x;
	velocity->y = vel.y;
}
