#include "App.h"
#include <cstdlib>

App::App() {
	setup = new Setup;
	setup->DisplaySelection();
	

	switch (setup->PROJECT_TYPE) {
	case 0:
		sim = new Serial(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED);
		sim->PopulateGrid();
		m_IterationCount = 0;
		while (m_IterationCount < setup->ITERATIONS) {
			if (setup->DRAW_GRAPHICS == 1) {
				sim->DrawSimToScreen();
			}

			m_IterationCount++;
		}
		break;
	}

}

App::~App() {
	delete setup;
	delete sim;
}
