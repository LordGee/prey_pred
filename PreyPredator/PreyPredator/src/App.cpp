#include "App.h"

App::App() {
	setup.SelectProjectType();
	setup.SetWindowSize();
	switch (setup.PROJECT_TYPE) {
	case 0:
		sim = new Serial;
		break;
	}
}
