#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	// ---------------------------------------------------------
	// Building Creation
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
	// ---------------------------------------------------------
	// Sky Creation
	CreateBuilding({ 0, 99, 300 }, { 600, 200, 1 }, Sky);
	CreateBuilding({ 0, 99, -300 }, { 600, 200, 1 }, Sky);
	CreateBuilding({ 300, 99, 0 }, { 1, 200, 600 }, Sky);
	CreateBuilding({ -300, 99, 0 }, { 1, 200, 600 }, Sky);
	// Sun Creation
	sun.color = Yellow;
	sun.radius = 20;
	sun.SetPos(100, 110, 250);
	// ---------------------------------------------------------
	// HOSPITAL
	CreateBuilding({ 0, 14, -150 }, { 50, 30, 50 }, White);
	CreateBuilding({ 0, 10, -117 }, { 50, 2, 16 }, Turquoise);
	CreateBuilding({ 0,  4, -109.5 }, { 25, 10, 1 }, White);
	CreateBuilding({ 0, 30, -124 }, { 3, 10, 2 }, Red);
	CreateBuilding({ 0, 30, -124 }, { 10, 3, 2 }, Red);

	CreateBuilding({ 0, -1, 0 }, { 300, 0.5, 300 }, Gray);

	// Patient 1
	CreatePatient({ 60, -0.1, -50 }, Beige, Black);
	// Patient 2
	CreatePatient({ 20, -0.1, -70 }, Beige, Blue);
	// Patient 3
	CreatePatient({ -87, -0.1, 50 }, Brown, Green);
	// Patient 4
	CreatePatient({ 10, -0.1, 70 }, Beige, Pink);
	// Patient 5
	CreatePatient({ 80, -0.1, 70 }, Brown, White);

	// Hospital sensor
	CreateHospitalSensor({ 0, 1, -118 });

	// Hospital's doors
	CreateConstrain({ -18.7, 4, -109.5 }, DarkBlue);
	CreateConstrain({ 18.7, 4, -109.5 }, DarkBlue);	
	// ---------------------------------------------------------
	// Timer and Camera
	doorTimer.Start();
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	// ---------------------------------------------------------
	// Music Loadings
	App->audio->PlayMusic("Assets/Sound/dubstep.ogg");
	pickupFx = App->audio->LoadFx("Assets/Sound/retro_pickup.ogg");
	hospitalFx = App->audio->LoadFx("Assets/Sound/completed.ogg");

	return ret;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	// Primitives Render
	for (uint i = 0; i < primitives.Count(); i++)
		primitives[i]->Update();		

	// Building Renders
	for (int i = 0; i < buildings.prim_builds.Count(); i++)
		buildings.prim_builds[i]->Render();

	// Constraints Timer
	doorDuration = doorTimer.Read() * 0.001f;
	if (doorDuration > 4.0f)
	{
		doorTimer.Start();
		doorClosed = !doorClosed;
	}
	// Constraints Render
	if (doorClosed) garageDoor[0]->body.Push(vec3(0, 20000, 0));
	else garageDoor[1]->body.Push(vec3(0, 20000, 0));

	for (int i = 0; i < winSphere.sphere.Count(); i++)
		winSphere.sphere[i].Render();
	
	// Patients Render
	if (!pickUpPatient1 && !inSceneWin)
	{
		patients.head[0].Render();
		patients.body[0]->Render();
	}
	if (!pickUpPatient2 && pickUpPatient1 && ambulanceFree)
	{
		patients.head[1].Render();
		patients.body[1]->Render();
	}
	if (!pickUpPatient3 && pickUpPatient2 && ambulanceFree)
	{
		patients.head[2].Render();
		patients.body[2]->Render();
	}
	if (!pickUpPatient4 && pickUpPatient3 && ambulanceFree)
	{
		patients.head[3].Render();
		patients.body[3]->Render();
	}
	if (!pickUpPatient5 && pickUpPatient4 && ambulanceFree)
	{
		patients.head[4].Render();
		patients.body[4]->Render();
	}

	// Win Scene. Only for Debug purpose. Use with caution
	/*if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		CleanWinScene();
		inSceneWin = true;
		countHospitalPatients = 5;
		countPatients = 5;

		App->audio->StopMusic();
		App->audio->PlayMusic("Assets/Sound/victory.ogg");
		App->player->SetWinPosition();
		winTimer.Start();
	}*/

	if (countHospitalPatients == 5 && countPatients == 5)
	{		
		winDuration = winTimer.Read() * 0.001f;
		Win();
		for (uint i = 0; i < winPrimitives.Count(); i++)
			winPrimitives[i]->Update();
	}

	sun.Render();
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	for (uint i = 0; i < primitives.Count(); i++)
		primitives[i]->Render();
	
	if (countHospitalPatients == 5 && countPatients == 5)
	{
		for (uint i = 0; i < winPrimitives.Count(); i++)
			winPrimitives[i]->Render();
	}

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

void ModuleSceneIntro::CleanWinScene()
{
	// Cleans all the spheres in the win scene
	for (uint i = 0; i < winPrimitives.Count(); i++)
		winPrimitives[i]->body.~PhysBody3D();

	winPrimitives.Clear();
}

void ModuleSceneIntro::CreateBuilding(const vec3 pos, const vec3 dim, Color bColor)
{
	// Create a cube to render a building
	Cube* c;
	c = new Cube(dim.x, dim.y, dim.z);
	c->color = bColor;
	c->SetPos(pos.x, pos.y + 1, pos.z);
	buildings.prim_builds.PushBack(c);
	buildings.phys_builds.PushBack(App->physics->AddBody(*c, this, 0.0f));
}

void ModuleSceneIntro::CreatePatient(const vec3 pos, Color pColorHead, Color pColorBody)
{
	// Create sphere and cube to render a patient
	Sphere s;
	s.color = pColorHead;
	s.radius = 0.5;
	s.SetPos(pos.x, pos.y + 2.5, pos.z);
	patients.head.PushBack(s);

	Cube* c;
	c = new Cube(0.5, 2, 0.5);
	c->color = pColorBody;
	c->SetPos(pos.x, pos.y + 1.5, pos.z);
	patients.body.PushBack(c);

	// Create a sensor to be able to pick patients
	Cube* sensor;
	sensor = new Cube(1, 3, 1);
	sensor->SetPos(pos.x, pos.y + 2, pos.z);
	patients.phys_patients.PushBack(App->physics->AddBody(*sensor, this, 0.0f, true));
}

void ModuleSceneIntro::CreateHospitalSensor(const vec3 pos)
{
	// Create a cube to render a building
	Cube* sensor;
	sensor = new Cube(2, 4, 16);
	sensor->SetPos(pos.x, pos.y + 1.5, pos.z);
	hospitalSensor = App->physics->AddBody(*sensor, this, 0.0f, true);
}

void ModuleSceneIntro::CreateConstrain(const vec3 pos, Color color)
{
	// Create two cubes to add a constraint slider
	Cube* bodyA;
	bodyA = new Cube(vec3(12.3, 5, 0.5), 1000);
	bodyA->color = color;
	bodyA->SetPos(pos.x, 1.5, pos.z);
	primitives.PushBack(bodyA);
	garageDoor.PushBack(bodyA);

	Cube* bodyB;
	bodyB = new Cube(vec3(12.3, 0.8, 0.8), 0);
	bodyB->SetPos(pos.x, -0.2, pos.z);
	primitives.PushBack(bodyB);

	btTransform frameInA;
	frameInA.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameInA.setOrigin(btVector3(0, 0, 0));

	btTransform frameInB;
	frameInB.getBasis().setEulerZYX(0, 0, M_PI / 2);
	frameInB.setOrigin(btVector3(0, 0, 0));

	App->physics->AddConstraintSlider(*bodyA, *bodyB, frameInA, frameInB);
}

void ModuleSceneIntro::CreateWinSphere(const vec3 pos, float radius, Color color)
{
	float mass = 0.3f;
	Sphere* s =  new Sphere(radius, mass);
	s->color = color;
	s->radius = radius;
	s->SetPos(pos.x, pos.y, pos.z);

	winPrimitives.PushBack(s);
}

void ModuleSceneIntro::Win()
{
	if (winDuration == 0.0f)
	{
		CreateWinSphere({ 0, 20, 0 }, 6, Red);
		CreateWinSphere({ 20, 30, 40 }, 5, White);
		CreateWinSphere({ 30, 20, 0 }, 4, Blue);
		CreateWinSphere({ -30, 10, 0 }, 5, Green);
		CreateWinSphere({ 50, 30, 70 }, 3, Yellow);
		CreateWinSphere({ 40, 30, 50 }, 3, DarkBlue);
		CreateWinSphere({ 0, 20, 30 }, 3, Beige);
		CreateWinSphere({ -50, 20, 15 }, 5, Green);
		CreateWinSphere({ -10, 20, 45 }, 5, Turquoise);
		CreateWinSphere({ -70, 30, 20 }, 7, Orange);
		CreateWinSphere({ 20, 20, -80 }, 3, Black);
		CreateWinSphere({ 10, 30, -90 }, 4, Blue);
		CreateWinSphere({ 60, 10, -30 }, 6, Pink);
		CreateWinSphere({ -20, 20, -90 }, 3, Brown);
		CreateWinSphere({ -10, 10, -80 }, 2, DarkBlue);
		CreateWinSphere({ 40, 20, -50 }, 10, White);
		
		App->player->timer.Stop();
	}	
	if (winDuration >= 10.0f)
	{
		App->player->ResetGame();
		App->audio->StopMusic();
		App->audio->PlayMusic("Assets/Sound/dubstep.ogg");
		inSceneWin = false;
		CleanWinScene();
	}
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	// All cases for collisions with patients or hospital sensor
	if (body1->is_sensor && !inSceneWin)
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
			App->audio->StopFx(App->player->sirenFx);
			App->audio->PlayFx(hospitalFx);
			

			if (countHospitalPatients < 1 && pickUpPatient1) countHospitalPatients = 1;
			if (countHospitalPatients < 2 && pickUpPatient2) countHospitalPatients = 2;
			if (countHospitalPatients < 3 && pickUpPatient3) countHospitalPatients = 3;
			if (countHospitalPatients < 4 && pickUpPatient4) countHospitalPatients = 4;
			if (countHospitalPatients < 5 && pickUpPatient5)
			{
				countHospitalPatients = 5;
				App->audio->StopMusic();
				App->audio->PlayMusic("Assets/Sound/victory.ogg");
				App->player->SetWinPosition();
				inSceneWin = true;
				winTimer.Start();
			}
		}
	}
}