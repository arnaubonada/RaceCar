#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	CreateBuilding({ -75, 24, 90 }, { 40, 50, 30 }, Gray);
	CreateBuilding({ -40, 14, 90 }, { 30, 30, 30 }, White);
	CreateBuilding({ -15, 29, 90 }, { 20, 60, 30 }, Gray);
	CreateBuilding({ 10,  14, 90 }, { 30, 30, 30 }, White);
	CreateBuilding({ 35, 19, 90 }, { 20, 40, 30 }, Gray);
	CreateBuilding({ 60,  9, 90 }, { 30, 20, 30 }, White);
	CreateBuilding({ 90, 14, 90 }, { 30, 30, 30 }, Gray);

	CreateBuilding({ 35,  9, 35 }, { 20, 20, 40 }, White);
	CreateBuilding({ 55,  24, 25 }, { 20, 50, 20 }, Gray);
	CreateBuilding({ 55, 19, 45 }, { 20, 40, 20 }, Gray);

	CreateBuilding({ 35, 19,  -20 }, { 20, 40, 30 }, Gray);
	CreateBuilding({ 55, 14,  -15 }, { 20, 30, 20 }, White);
	CreateBuilding({ 55,  9,  -30 }, { 20, 20, 10 }, Gray);

	CreateBuilding({ 100, 14, 70 }, { 20, 30, 10 }, Gray);
	CreateBuilding({ 100,  9, 55 }, { 20, 20, 20 }, White);
	CreateBuilding({ 100,  9, 30 }, { 20, 20, 30 }, Gray);
	CreateBuilding({ 100, 14,   0 }, { 20, 30, 30 }, Gray);
	CreateBuilding({ 100,  9,  -35 }, { 20, 20, 40 }, White);
	CreateBuilding({ 85, 19, -75 }, { 20, 40, 40 }, Gray);
	CreateBuilding({ 60, 14,  -75 }, { 30, 30, 40 }, White);
	CreateBuilding({ 35,  9, -75 }, { 20, 20, 40 }, White);
	CreateBuilding({ 35, 29,-110 }, { 20, 60, 30 }, White);

	CreateBuilding({ -35, 24, -129 }, { 20, 50, 40 }, White);
	CreateBuilding({ -35, 19, -99 }, { 20, 40, 20 }, Gray);
	CreateBuilding({ -35, 14, -69 }, { 20, 30, 40 }, Gray);
	CreateBuilding({ -35, 29, -27 }, { 20, 60, 44 }, White);
	CreateBuilding({ -60,  9, -27 }, { 30, 20, 44 }, Gray);
	CreateBuilding({ -85, 14,  -27 }, { 20, 30, 44 }, White);
	CreateBuilding({ -95, 14, 10 }, { 10, 30, 30 }, White);
	CreateBuilding({ -95,  9, 35 }, { 10, 20, 20 }, Gray);
	CreateBuilding({ -95, 19, 60 }, { 10, 40, 30 }, White);

	CreateBuilding({ -35, 14, 35 }, { 20, 30, 40 }, White);
	CreateBuilding({ -55,  9, 25 }, { 20, 20, 20 }, Gray);
	CreateBuilding({ -55, 24, 45 }, { 20, 50, 20 }, Gray);

	//HOSPITAL
	CreateBuilding({ 0, 14, -150 }, { 50, 30, 50 }, White);
	CreateBuilding({ 0, 10, -117 }, { 50, 2, 16 }, White);
	CreateBuilding({ 0,  4, -109.5 }, { 25, 10, 1 }, White);
	CreateBuilding({ 0, 30, -124 }, { 3, 10, 2 }, Red);
	CreateBuilding({ 0, 30, -124 }, { 10, 3, 2 }, Red);

	CreateBuilding({ 0, -1, 0 }, { 300, 0.5, 300 }, Gray);

	

	//Patient 1
	CreatePatient({ 60, -0.1, -50 }, Red);

	//Patient 2
	CreatePatient({ 20, -0.1, -70 }, Red);

	//Patient 3
	CreatePatient({ -87, -0.1, 50  }, Red);

	//Patient 4
	CreatePatient({ 10, -0.1, 70 }, Red);

	//Patient 5
	CreatePatient({ 80, -0.1, 70 }, Red);

	CreateHospitalSensor({ 0, 1, -118 });


	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	/*Plane p(0, 1, 0, 0);
	p.axis = true;*/
	//p.Render();

	for (int i = 0; i < buildings.prim_builds.Count(); i++)
		buildings.prim_builds[i].Render();

	if (!pickUpPatient1)
	{
		patients.head_patients[0].Render();
		patients.body_patients[0].Render();
	}
	if (!pickUpPatient2 && pickUpPatient1 && ambulanceFree)
	{
		patients.head_patients[1].Render();
		patients.body_patients[1].Render();
	}
	if (!pickUpPatient3 && pickUpPatient2 && ambulanceFree)
	{
		patients.head_patients[2].Render();
		patients.body_patients[2].Render();
	}
	if (!pickUpPatient4 && pickUpPatient3 && ambulanceFree)
	{
		patients.head_patients[3].Render();
		patients.body_patients[3].Render();
	}
	if (!pickUpPatient5 && pickUpPatient4 && ambulanceFree)
	{
		patients.head_patients[4].Render();
		patients.body_patients[4].Render();
	}


	return UPDATE_CONTINUE;
}



void ModuleSceneIntro::CreateBuilding(const vec3 pos, const vec3 dim, Color bColor)
{
	Cube c;
	c.color = bColor;
	c.size = { dim.x, dim.y, dim.z };
	c.SetPos(pos.x, pos.y + 1, pos.z);
	buildings.prim_builds.PushBack(c);
	buildings.phys_builds.PushBack(App->physics->AddBody(c, this, 0.0f));
}

void ModuleSceneIntro::CreatePatient(const vec3 pos, Color pColor)
{
	Cube c;
	c.color = pColor;
	c.size = { 0.5,1.5,0.5 };
	c.SetPos(pos.x, pos.y + 1, pos.z);
	patients.body_patients.PushBack(c);
	Sphere s;
	s.color = pColor;
	s.radius = 0.5;
	s.SetPos(pos.x, pos.y + 2, pos.z);
	patients.head_patients.PushBack(s);

	Cube sensor;
	sensor.size = { 1,2.5,1 };
	sensor.SetPos(pos.x, pos.y + 1.5, pos.z);
	patients.phys_patients.PushBack(App->physics->AddBody(sensor, this, 0.0f, true));
}

void ModuleSceneIntro::CreateHospitalSensor(const vec3 pos)
{
	Cube sensor;
	sensor.size = { 2,4,16 };
	sensor.SetPos(pos.x, pos.y + 1.5, pos.z);
	hospitalSensor = App->physics->AddBody(sensor, this, 0.0f, true);
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->is_sensor)
	{
		if (body1 == patients.phys_patients[0] && ambulanceFree)
		{
			pickUpPatient1 = true;
			ambulanceFree = false;
			if(countPatients<1) countPatients=1;
		}
		
		if (body1 == patients.phys_patients[1] && pickUpPatient1 && ambulanceFree)
		{
			pickUpPatient2 = true;
			ambulanceFree = false;
			if (countPatients < 2) countPatients=2;
		}
		if (body1 == patients.phys_patients[2] && pickUpPatient2 && ambulanceFree)
		{
			pickUpPatient3 = true;
			ambulanceFree = false;
			if (countPatients < 3) countPatients=3;
		}
		if (body1 == patients.phys_patients[3] && pickUpPatient3 && ambulanceFree)
		{
			pickUpPatient4 = true;
			ambulanceFree = false;
			if (countPatients < 4) countPatients=4;
		}
		if (body1 == patients.phys_patients[4] && pickUpPatient4 && ambulanceFree)
		{
			pickUpPatient5 = true;
			ambulanceFree = false;
			if (countPatients < 5) countPatients=5;
		}

		if (body1 == hospitalSensor)
		{
			ambulanceFree = true;
			if (countHospitalPatients < 1 && pickUpPatient1) countHospitalPatients = 1;
			if (countHospitalPatients < 2 && pickUpPatient2) countHospitalPatients = 2;
			if (countHospitalPatients < 3 && pickUpPatient3) countHospitalPatients = 3;
			if (countHospitalPatients < 4 && pickUpPatient4) countHospitalPatients = 4;
			if (countHospitalPatients < 5 && pickUpPatient5) countHospitalPatients = 5;
		}

	}
}