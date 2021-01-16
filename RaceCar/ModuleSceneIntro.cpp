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
	CreateBuilding({ 0, 19, -151 }, { 20, 40, 50 }, Red);


	CreatePatient({ 0, 0, -30 }, Red, 1);


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
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (int i = 0; i < cube_buildings.prim_builds.Count(); i++)
		cube_buildings.prim_builds[i].Render();
	
	for (int i = 0; i < cube_patients.body_patients.Count(); i++)
		cube_patients.body_patients[i].Render();
	
	for (int i = 0; i < cube_patients.head_patients.Count(); i++)
		cube_patients.head_patients[i].Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateBuilding(const vec3 pos, const vec3 dim, Color bColor)
{
	Cube c;
	c.color = bColor;
	c.size = { dim.x, dim.y, dim.z };
	c.SetPos(pos.x, pos.y + 1, pos.z);
	cube_buildings.prim_builds.PushBack(c);
	cube_buildings.phys_builds.PushBack(App->physics->AddBody(c, this, 0.0f));
}

void ModuleSceneIntro::CreatePatient(const vec3 pos, Color pColor, int id)
{
	Cube c;
	c.color = pColor;
	c.size = { 0.5,1.5,0.5 };
	c.SetPos(pos.x, pos.y + 1, pos.z);
	cube_patients.body_patients.PushBack(c);
	cube_patients.phys_patients.PushBack(App->physics->AddBody(c, this, 0.0f, true));
	Sphere s;
	s.color = pColor;
	s.radius = 0.5;
	s.SetPos(pos.x, pos.y + 2, pos.z);
	cube_patients.head_patients.PushBack(s);
	cube_patients.phys_patients.PushBack(App->physics->AddBody(s, this, 0.0f, true));
}
