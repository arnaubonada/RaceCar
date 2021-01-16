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

	CreateBuilding({ 55 , 19, -80 }, { 20, 40, 20 }, Gray);
	CreateBuilding({ 55 , 14, -40 }, { 20, 30, 20 }, White);
	CreateBuilding({ 55 , 14, -10 }, { 20, 30, 20 }, White);
	CreateBuilding({ 55,  19,  20 }, { 30, 40, 30 }, Gray);
	CreateBuilding({ 55 , 4,   60 }, { 30, 10, 30 }, White);
	CreateBuilding({ 55 , 29, 100 }, { 20, 60, 20 }, White);

	CreateBuilding({ -25, 19, 100 }, { 20, 40, 20 }, Gray);
	CreateBuilding({ -25, 14,  60 }, { 20, 30, 20 }, White);
	CreateBuilding({ -25, 14,  20 }, { 20, 30, 20 }, White);
	CreateBuilding({ -25, 19, -10 }, { 30, 40, 30 }, Gray);
	CreateBuilding({ -25, 4,  -50 }, { 30, 10, 30 }, White);
	CreateBuilding({ -25, 29, -80 }, { 20, 60, 20 }, White);
	
	//HOSPITAL
	CreateBuilding({ 15, 14, -150 }, { 50, 30, 50 }, White);
	CreateBuilding({ 15, 19, -151 }, { 20, 40, 50 }, Red);


	CreatePatient({ 15, 0, -30 }, Red, 1);


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
