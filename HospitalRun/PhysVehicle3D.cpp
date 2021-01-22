#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Application.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
	//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Black;

	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.SetRadius(info.wheels[i].radius);
		wheel.SetHeight(info.wheels[i].width);

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	chassis.color = Yellow;
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();
	chassis.Render();

	Cube sirena(info.sirena_size);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&sirena.transform);

	sirena.color = Orange;
	btQuaternion s = vehicle->getChassisWorldTransform().getRotation();
	btVector3 sirenaOffset(info.sirena_offset.x, info.sirena_offset.y, info.sirena_offset.z);
	sirenaOffset = sirenaOffset.rotate(q.getAxis(), q.getAngle());

	sirena.transform.M[12] += sirenaOffset.getX();
	sirena.transform.M[13] += sirenaOffset.getY();
	sirena.transform.M[14] += sirenaOffset.getZ();
	sirena.Render();

}

// ----------------------------------------------------------------------------
void PhysVehicle3D::RenderPatient()
{
	Cylinder wheel;

	wheel.color = Black;

	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.SetRadius(info.wheels[i].radius);
		wheel.SetHeight(info.wheels[i].width);

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	chassis.color = Yellow;
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();
	chassis.Render();

	Cube sirena(info.sirena_size);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&sirena.transform);

	sirena.color = Red;
	btQuaternion s = vehicle->getChassisWorldTransform().getRotation();
	btVector3 sirenaOffset(info.sirena_offset.x, info.sirena_offset.y, info.sirena_offset.z);
	sirenaOffset = sirenaOffset.rotate(q.getAxis(), q.getAngle());

	sirena.transform.M[12] += sirenaOffset.getX();
	sirena.transform.M[13] += sirenaOffset.getY();
	sirena.transform.M[14] += sirenaOffset.getZ();
	sirena.Render();

}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}
