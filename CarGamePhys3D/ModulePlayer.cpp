#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 1, 4);
	car.chassis_offset.Set(0, 1, 0);

	car.chassis_size2.Set(3, 0.12, 0.75);
	car.chassis_offset2.Set(0, 0.75, 2.5);

	car.chassis_size3.Set(0.25, 1, 0.25);
	car.chassis_offset3.Set(0.75, 1.75, -1.75);

	car.chassis_size4.Set(0.25, 1, 0.25);
	car.chassis_offset4.Set(-0.75, 1.75, -1.75);

	car.chassis_size5.Set(2.5, 0.2, 1);
	car.chassis_offset5.Set(0, 2.5, -1.75);

	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.6f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetType(PhysBody3D::type::PLAYER);
	vehicle->collision_listeners.add(App->scene_intro);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::OnCollision(PhysBody3D * body1, PhysBody3D * body2)
{

}

void ModulePlayer::SetPosition(int x, int y, int z)
{
	vehicle->SetPos(x, y, z);
}

vec3 ModulePlayer::GetPosition()
{
	return vehicle->GetPos();
}

void ModulePlayer::SetRotation(btQuaternion rot)
{
	vehicle->SetRotation(rot);
}

vec3 ModulePlayer::GetSavedPosition()
{
	return saved_position;
}

void ModulePlayer::SetSavedPosition(vec3 pos)
{
	saved_position = pos;
}

btQuaternion ModulePlayer::GetSavedRotation()
{
	return saved_rotation;
}

void ModulePlayer::SetSavedRotation(btQuaternion rotation)
{
	saved_rotation = rotation;
}

float ModulePlayer::GetVehicleSpeed()
{
	return speed;
}

vec3 ModulePlayer::GetUpwardPosition()
{
	return vehicle->GetUpwardVector();
}

PhysBody3D * ModulePlayer::GetVehicle()
{
	return vehicle;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;
	speed = vehicle->GetKmh();

	if (!App->camera->debug)
	{

		vec3 forward_vector = vehicle->GetForwardVector();
		vec3 upward_vector = vehicle->GetUpwardVector();

		forward_vector = -forward_vector;
		forward_vector = forward_vector * 11;
		upward_vector = upward_vector * 5;

		vec3 campos = forward_vector + upward_vector;
		App->camera->Position = campos + vehicle->GetPos();

		App->camera->LookAt(upward_vector + vehicle->GetPos());
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (speed < MAX_VELOCITY) {
			acceleration = MAX_ACCELERATION;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES) {
			turn += TURN_DEGREES;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES) {
			turn -= TURN_DEGREES;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		vehicle->SetPos(saved_position.x, saved_position.y, saved_position.z);
		vehicle->SetRotation(saved_rotation);
		vehicle->GetBody()->clearForces();
		vehicle->GetBody()->setLinearVelocity({ 0, 0, 0});
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		if (App->pause)
		{
			vehicle->GetBody()->clearForces();
			vehicle->GetBody()->setLinearVelocity({ 0, 0, 0 });
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	//TODO Set Score to game window

	if (vehicle->GetPos().y > max_height)
	{
		max_height = vehicle->GetPos().y;
	}

	return UPDATE_CONTINUE;
}



