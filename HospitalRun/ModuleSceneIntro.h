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
	p2DynArray<Cube*>			prim_builds;
};
struct Patients
{
	p2DynArray<PhysBody3D*>		phys_patients;
	p2DynArray<Sphere>			head;
	p2DynArray<Cube*>			body;
};
struct Constraints
{
	p2DynArray<PhysBody3D*>		phys_constraints;
	p2DynArray<Cube*>			prim_constraints;
};
struct WinSphere
{
	p2DynArray<PhysBody3D*>		phys_winSphere;
	p2DynArray<Sphere>			sphere;
};

#define TRACK_WIDTH 20.0f
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void CleanWinScene();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateBuilding(const vec3 pos, const vec3 dim, Color bColor);
	void CreatePatient(const vec3 pos, Color pColorHead, Color pColorBody);
	void CreateHospitalSensor(const vec3 pos);
	void CreateConstrain(const vec3 pos, Color color);
	void CreateWinSphere(const vec3 pos, float radius, Color color);

	void Win();

public:
	Buildings buildings;
	Sphere sun;

	Constraints constraints;
	p2DynArray<Cube*> garageDoor;
	p2DynArray<Primitive*>	primitives;
	p2DynArray<Primitive*>	winPrimitives;

	WinSphere winSphere;
		
	PhysBody3D* hospitalSensor;
	Patients patients;
	bool pickUpPatient1 = false;
	bool pickUpPatient2 = false;
	bool pickUpPatient3 = false;
	bool pickUpPatient4 = false;
	bool pickUpPatient5 = false;
	bool ambulanceFree = true;
	int countPatients = 0;
	int countHospitalPatients = 0;

	bool inSceneWin = false;

private:
	int pickupFx;
	int hospitalFx;

	Timer doorTimer;
	bool doorClosed = true;
	Timer winTimer;
	float doorDuration;
	float winDuration;
};
