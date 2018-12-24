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
	void DestroyScorePoint(PhysBody3D* point);

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	uint score = 0;

	Cube floor;

	p2DynArray <Cube> scene_terrain;
	p2DynArray <Cube> scene_points;
	p2DynArray <PhysBody3D*> scene_points_pb;
	p2DynArray <Sphere> scene_spheres;
	p2DynArray <Cylinder> scene_cylinders;
};
