#pragma once
#include "Component.h"
#include <vector>
class Point2D;
class RigidBody2D : public Component
{
public:
	RigidBody2D(GameObject*, float mass, bool enableGravity, bool enableDrag);
	~RigidBody2D();
	void AddForce(Point2D);
	Point2D* GetNetForce();
	Point2D* GetVelocity();
	void SetVelocity(Point2D);
	Point2D* GetPosition();
	void Start() override;
	void Update() override;

public:
	bool enableGravity;
	bool enableDrag;
	float mass;
private:
	Point2D* velocity;
	Point2D* netForce;
	std::vector<Point2D> forces;
};

