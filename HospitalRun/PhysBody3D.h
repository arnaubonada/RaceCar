#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "glmath.h"

class btRigidBody;
class btCollisionShape;
struct btDefaultMotionState;
class Module;

class Sphere;
class Cube;
class Cylinder;
class Plane;

class Primitive;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D();
    PhysBody3D(btRigidBody* body);
	~PhysBody3D();
	btRigidBody* GetBody() const;
    void SetBody(Sphere* primitive, float mass);
	void SetBody(Cube* primitive, float mass);
	void Push(vec3 force);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	float getPosX();
	float getPosY();
	float getPosZ();
    void SetBody(btCollisionShape* shape, Primitive* parent, float mass);

private:
	btRigidBody* body = nullptr;
    btCollisionShape* colShape;
    btDefaultMotionState* motionState;
public:
    Primitive* parentPrimitive;
	p2List<Module*> collision_listeners;
	bool is_sensor = false;
};

#endif // __PhysBody3D_H__