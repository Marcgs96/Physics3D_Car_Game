#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "Primitive.h"

class btRigidBody;
class btQuaternion;
class Module;
class vec3;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
	enum class type {PLAYER, POINT, CHECKPOINT, END, NONE};
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);
	vec3 GetPos();
	btQuaternion GetRotation();
	type GetType();
	void SetType(type my_type);
	void SetRotation(btQuaternion rotation);

	btRigidBody* GetBody();

	bool active = true;

private:
	btRigidBody* body = nullptr;
	bool is_sensor = false;
	type my_type;

public:
	p2List<Module*> collision_listeners;
};
#endif // __PhysBody3D_H__