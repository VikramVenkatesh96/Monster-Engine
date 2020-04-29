#pragma once
#include <vector>

class RigidBody2D;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	static void Run(float dt);
	static void AddRigidBody(RigidBody2D*);

public:
	static const float gravity;
	static const float dragCoefficient;

private:
	static std::vector<RigidBody2D *> rigidBodies;
};

