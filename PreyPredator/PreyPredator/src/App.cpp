#include "App.h"
#include <cstdlib>

App::App() {
	setup = new Setup;
	setup->DisplaySelection();
	system("pause");
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
