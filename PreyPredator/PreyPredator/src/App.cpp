#include "App.h"
#include <cstdlib>

App::App() {
	setup = new Setup;
	setup->DisplaySelection();

	switch (setup->PROJECT_TYPE) {
	case 0:
		sim = new Serial(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED);
		break;
	}

	sim->PopulateGrid();

	if (setup->DRAW_GRAPHICS == 1) {
		sim->DrawSimToScreen(setup->ITERATIONS);
	} else {
		sim->RunSimNoDraw(setup->ITERATIONS);
	}

}

App::~App() {
	delete setup;
	delete sim;
}
