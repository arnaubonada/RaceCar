#include "PhysBody3D.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// =========================================================
PhysBody3D::PhysBody3D()
    : body(nullptr)
    , colShape(nullptr)
    , motionState(nullptr)
    , parentPrimitive(nullptr)
    , collision_listeners()
{}
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{
    body->setUserPointer(this);
}
PhysBody3D::~PhysBody3D()
{
    if (body != nullptr)
    {
        App->physics->RemoveBodyFromWorld(body);
        delete body;
       // delete colShape;
        //delete motionState;
    }
}
// ---------------------------------------------------------
btRigidBody* PhysBody3D::GetBody() const
{
    return body;
}
void PhysBody3D::SetBody(Sphere* primitive, float mass)
{
    SetBody(new btSphereShape(primitive->GetRadius()),
        primitive, mass);
}
void PhysBody3D::SetBody(Cube* primitive, float mass) {
    SetBody(new btBoxShape(btVector3(primitive->GetSize().x * 0.5, primitive->GetSize().y * 0.5, primitive->GetSize().z * 0.5)),
        primitive, mass);
}
void PhysBody3D::SetBody(btCollisionShape* shape, Primitive* parent, float mass)
{
    parentPrimitive = parent;

    colShape = shape;

    btTransform startTransform;
    startTransform.setFromOpenGLMatrix(&parent->transform);

    btVector3 localInertia(0, 0, 0);
    if (mass != 0.f)
        colShape->calculateLocalInertia(mass, localInertia);

    motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);

    body = new btRigidBody(rbInfo);

    body->setUserPointer(this);

    App->physics->AddBodyToWorld(body);
}
// ---------------------------------------------------------
void PhysBody3D::Push(vec3 force)
{  
    body->activate();
    body->applyCentralForce(btVector3(force.x, force.y, force.z));
}
void PhysBody3D::SetVelocity(float x, float y, float z)
{
    body->setLinearVelocity(btVector3(x, y, z));
}
// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
    btTransform t = body->getWorldTransform();
    t.setOrigin(btVector3(x, y, z));
    body->setWorldTransform(t);
}

float PhysBody3D::getPosX()
{
    return body->getWorldTransform().getOrigin().getX();
}
float PhysBody3D::getPosY()
{
    return body->getWorldTransform().getOrigin().getY();
}
float PhysBody3D::getPosZ()
{
    return body->getWorldTransform().getOrigin().getZ();
}
// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}
// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}