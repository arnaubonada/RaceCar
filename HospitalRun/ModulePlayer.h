#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 9.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void ResetGame();
	void SetWinPosition();

public:
	p2DynArray<PhysBody3D*>		phys_car;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	vec3 pos;

	Timer timer;
	float count = 0;
	int countInt = 0;

	// Fx Sounds
	int sirenFx;
	int loseFx;
	int restartFx;
};