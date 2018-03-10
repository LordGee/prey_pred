#include "App.h"

App::App() {
	setup->SelectProjectType();
	setup->SetWindowSize();
	switch (setup->PROJECT_TYPE) {
	case 0:
		sim = new Serial(setup->WIDTH, setup->HEIGHT);
		sim->PopulateGrid();
		break;
	}
}

App::~App() {
	delete setup;
	delete sim;
}
