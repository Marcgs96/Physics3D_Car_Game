#include "PhysVehicle3D.h"
#include "Primitive.h"
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

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();


	chassis.Render();
	//--------------------------------------------------------------------------------
	Cube chassis2(info.chassis_size2.x, info.chassis_size2.y, info.chassis_size2.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis2.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset2(info.chassis_offset2.x, info.chassis_offset2.y, info.chassis_offset2.z);
	offset2 = offset2.rotate(q.getAxis(), q.getAngle());

	chassis2.transform.M[12] += offset2.getX();
	chassis2.transform.M[13] += offset2.getY();
	chassis2.transform.M[14] += offset2.getZ();


	chassis2.Render();	
	//--------------------------------------------------------------------------------
	Cube chassis3(info.chassis_size3.x, info.chassis_size3.y, info.chassis_size3.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis3.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset3(info.chassis_offset3.x, info.chassis_offset3.y, info.chassis_offset3.z);
	offset3 = offset3.rotate(q.getAxis(), q.getAngle());

	chassis3.transform.M[12] += offset3.getX();
	chassis3.transform.M[13] += offset3.getY();
	chassis3.transform.M[14] += offset3.getZ();


	chassis3.Render();
	//--------------------------------------------------------------------------------
	Cube chassis4(info.chassis_size4.x, info.chassis_size4.y, info.chassis_size4.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis4.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset4(info.chassis_offset4.x, info.chassis_offset4.y, info.chassis_offset4.z);
	offset4 = offset4.rotate(q.getAxis(), q.getAngle());

	chassis4.transform.M[12] += offset4.getX();
	chassis4.transform.M[13] += offset4.getY();
	chassis4.transform.M[14] += offset4.getZ();


	chassis4.Render();
	//--------------------------------------------------------------------------------
	Cube chassis5(info.chassis_size5.x, info.chassis_size5.y, info.chassis_size5.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis5.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset5(info.chassis_offset5.x, info.chassis_offset5.y, info.chassis_offset5.z);
	offset5 = offset5.rotate(q.getAxis(), q.getAngle());

	chassis5.transform.M[12] += offset5.getX();
	chassis5.transform.M[13] += offset5.getY();
	chassis5.transform.M[14] += offset5.getZ();


	chassis5.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
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

vec3 PhysVehicle3D::GetForwardVector()
{
	btVector3 btForward = vehicle->getForwardVector();
	vec3 forward_vector; forward_vector.Set(btForward.getX(), btForward.getY(), btForward.getZ());
	return forward_vector;
}
