#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"


struct PhysBody3D;
struct PhysMotor3D;

struct Buildings
{
	p2DynArray<PhysBody3D*>		phys_builds;
	p2DynArray<Cube>			prim_builds;
};
struct Patients
{
	p2DynArray<PhysBody3D*>		phys_patients;
	p2DynArray<Cube>			body_patients;
	p2DynArray<Sphere>			head_patients;
};

#define TRACK_WIDTH 20.0f
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void CreateBuilding(const vec3 pos, const vec3 dim, Color bColor);
	void CreatePatient(const vec3 pos, Color pColor, int id);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
public:
	Buildings cube_buildings;

	Patients cube_patients;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Sphere traffic_light1;
	Sphere traffic_light2;
};
