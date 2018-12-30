#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "glmath.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define MAX_VELOCITY 200.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 250.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void SetPosition(int x, int y, int z);
	vec3 GetPosition();
	void SetRotation(btQuaternion rot);
	vec3 GetSavedPosition();
	void SetSavedPosition(vec3 pos);
	btQuaternion GetSavedRotation();
	void SetSavedRotation(btQuaternion rotation);
	float GetVehicleSpeed();
	vec3 GetUpwardPosition();

	float max_height = 0;

private:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float speed;
	float brake;
	float offset_x = 0;
	vec3 saved_position = { -175, 1, 190 };
	btQuaternion saved_rotation;
};