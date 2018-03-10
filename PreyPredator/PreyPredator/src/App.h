#pragma once
#include "Serial.h"
#include "Setup.h"

class App {
public:

private:
	Setup* setup;
	Simulator* sim;

protected:
	// int WIDTH, HEIGHT;

public:
	App();
	~App();

};
