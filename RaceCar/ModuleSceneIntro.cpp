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

	CreateBuilding({0, 99, 300 }, { 600, 200, 1 }, Sky);
	CreateBuilding({0, 99, -300 }, { 600, 200, 1 }, Sky);
	CreateBuilding({300, 99, 0}, { 1, 200, 600 }, Sky);
	CreateBuilding({-300, 99, 0 }, { 1, 200, 600 }, Sky);

	sun.color = Yellow;
	sun.radius = 10;
	sun.SetPos(100, 110, 250);


	//HOSPITAL
	CreateBuilding({ 0, 14, -150 }, { 50, 30, 50 }, White);
	CreateBuilding({ 0, 10, -117 }, { 50, 2, 16 }, Turquoise);
	CreateBuilding({ 0,  4, -109.5 }, { 25, 10, 1 }, White);
	CreateBuilding({ 0, 30, -124 }, { 3, 10, 2 }, Red);
	CreateBuilding({ 0, 30, -124 }, { 10, 3, 2 }, Red);

	CreateBuilding({ 0, -1, 0 }, { 300, 0.5, 300 }, Gray);
	
	//Patient 1
	CreatePatient({ 60, -0.1, -50 }, Beige, Black);

	//Patient 2
	CreatePatient({ 20, -0.1, -70 }, Beige, Blue);

	//Patient 3
	CreatePatient({ -87, -0.1, 50  }, Brown, Green);

	//Patient 4
	CreatePatient({ 10, -0.1, 70 }, Beige, Orange);

	//Patient 5
	CreatePatient({ 80, -0.1, 70 }, Brown, White);

	CreateHospitalSensor({ 0, 1, -118 });

	App->audio->PlayMusic("Assets/Sound/waves.ogg");
	pickupFx = App->audio->LoadFx("Assets/Sound/retro_pickup.ogg");
	
	hospitalFx = App->audio->LoadFx("Assets/Sound/completed.ogg");

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
	for (int i = 0; i < buildings.prim_builds.Count(); i++)
		buildings.prim_builds[i].Render();

	if (!pickUpPatient1)
	{
		patients.head[0].Render();
		patients.body[0].Render();
	}
	if (!pickUpPatient2 && pickUpPatient1 && ambulanceFree)
	{
		patients.head[1].Render();
		patients.body[1].Render();
	}
	if (!pickUpPatient3 && pickUpPatient2 && ambulanceFree)
	{
		patients.head[2].Render();
		patients.body[2].Render();
	}
	if (!pickUpPatient4 && pickUpPatient3 && ambulanceFree)
	{
		patients.head[3].Render();
		patients.body[3].Render();
	}
	if (!pickUpPatient5 && pickUpPatient4 && ambulanceFree)
	{
		patients.head[4].Render();
		patients.body[4].Render();
	}

	sun.Render();
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

void ModuleSceneIntro::CreatePatient(const vec3 pos, Color pColorHead, Color pColorBody)
{
	Sphere s;
	s.color = pColorHead;
	s.radius = 0.5;
	s.SetPos(pos.x, pos.y + 2.5, pos.z);
	patients.head.PushBack(s);
	Cube c;
	c.color = pColorBody;
	c.size = { 0.5,2,0.5 };
	c.SetPos(pos.x, pos.y + 1.5, pos.z);
	patients.body.PushBack(c);

	Cube sensor;
	sensor.size = { 1,3,1 };
	sensor.SetPos(pos.x, pos.y + 2, pos.z);
	patients.phys_patients.PushBack(App->physics->AddBody(sensor, this, 0.0f, true));
}

void ModuleSceneIntro::CreateHospitalSensor(const vec3 pos)
{
	Cube sensor;
	sensor.size = { 2,4,16 };
	sensor.SetPos(pos.x, pos.y + 1.5, pos.z);
	hospitalSensor = App->physics->AddBody(sensor, this, 0.0f, true);
}

void ModuleSceneIntro::CreateConstrain(const vec3 pos)
{
	Cylinder constrainBase;
	constrainBase.radius = 10.0f;
	constrainBase.height = 5.0f;
	constrainBase.SetPos(pos.x, pos.y + 1.5, pos.z);
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->is_sensor)
	{
		if (body1 == patients.phys_patients[0] && ambulanceFree)
		{
			if (countPatients < 1)
			{
				countPatients = 1;
				pickUpPatient1 = true;
				ambulanceFree = false;
				App->audio->PlayFx(pickupFx);
			}
		}
		
		if (body1 == patients.phys_patients[1] && pickUpPatient1 && ambulanceFree)
		{
			if (countPatients < 2) 
			{
				pickUpPatient2 = true;
				ambulanceFree = false;
				App->audio->PlayFx(pickupFx);
				countPatients = 2;
			}
		}
		if (body1 == patients.phys_patients[2] && pickUpPatient2 && ambulanceFree)
		{
			if (countPatients < 3)
			{
				pickUpPatient3 = true;
				ambulanceFree = false;
				App->audio->PlayFx(pickupFx);
				countPatients = 3;
			}			
		}
		if (body1 == patients.phys_patients[3] && pickUpPatient3 && ambulanceFree)
		{
			if (countPatients < 4)
			{
				pickUpPatient4 = true;
				ambulanceFree = false;
				App->audio->PlayFx(pickupFx);
				countPatients = 4;
			}			
		}
		if (body1 == patients.phys_patients[4] && pickUpPatient4 && ambulanceFree)
		{
			if (countPatients < 5)
			{
				pickUpPatient5 = true;
				ambulanceFree = false;
				App->audio->PlayFx(pickupFx);
				countPatients = 5;
			}			
		}

		if (body1 == hospitalSensor && !ambulanceFree)
		{
			ambulanceFree = true;
			App->audio->PlayFx(hospitalFx);
			App->audio->StopFx(App->player->sirenFx);

			if (countHospitalPatients < 1 && pickUpPatient1) countHospitalPatients = 1;
			if (countHospitalPatients < 2 && pickUpPatient2) countHospitalPatients = 2;
			if (countHospitalPatients < 3 && pickUpPatient3) countHospitalPatients = 3;
			if (countHospitalPatients < 4 && pickUpPatient4) countHospitalPatients = 4;
			if (countHospitalPatients < 5 && pickUpPatient5) countHospitalPatients = 5;
		}
	}
}