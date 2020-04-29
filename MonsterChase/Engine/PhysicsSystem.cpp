#include "PhysicsSystem.h"
#include "RigidBody2D.h"
#include "Point2D.h"

std::vector<RigidBody2D *> PhysicsSystem::rigidBodies;
//Coefficient declarations 
const float PhysicsSystem::gravity = -1.0f;
const float PhysicsSystem::dragCoefficient = 12.5f;

PhysicsSystem::PhysicsSystem()
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Run(float dt)
{
	for(unsigned int i = 0; i < rigidBodies.size(); ++i)
	{
		Point2D netForce = Point2D(0, 0);
		RigidBody2D* rigidBody = rigidBodies.at(i);
		netForce = *rigidBody->GetNetForce();
		
		if (rigidBody->enableGravity)
		{
			//F = mg
			netForce += Point2D(0.0f, rigidBody->mass * gravity);
		}
		if (rigidBody->enableDrag)
		{
			//F = -kV^2
			netForce += *rigidBody->GetVelocity()->Normalize() * (rigidBody->GetVelocity()->SquareLength()) *-1.0f * dragCoefficient;
		}

		Point2D acceleration = netForce / rigidBody->mass;
		Point2D vel = *rigidBody->GetVelocity();
		Point2D prevVel = vel;
		
		Point2D* pos = rigidBody->GetPosition();
		//Using Euler midpoint method
		vel += acceleration * dt;
		*pos += ((vel + prevVel) / 2.0f) * dt;

		rigidBody->SetVelocity(vel);
	}
}

void PhysicsSystem::AddRigidBody(RigidBody2D * rigidBody)
{
	rigidBodies.push_back(rigidBody);
}
