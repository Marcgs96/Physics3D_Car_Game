#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateMap();
	void CreateScorePoints(vec3 starting_position, uint num_points, uint pos_incr);

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	Cube floor;
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	p2DynArray <Cube> scene_cubes;
	p2DynArray <Sphere> scene_spheres;
	p2DynArray <Cylinder> scene_cylinders;
};
