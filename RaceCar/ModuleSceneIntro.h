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
	void CreatePatient(const vec3 pos, Color pColor);
	void CreateHospitalSensor(const vec3 pos);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
public:
	Buildings buildings;

	Patients patients;

	PhysBody3D* hospitalSensor;

	bool pickUpPatient1 = false;
	bool pickUpPatient2 = false;
	bool pickUpPatient3 = false;
	bool pickUpPatient4 = false;
	bool pickUpPatient5 = false;
	bool ambulanceFree = true;
	int countPatients = 0;
	int countHospitalPatients = 0;

private:
	int pickupFx;
	int hospitalFx;
};
