#include "App.h"
#include "Setup.h"

App::App() {
	Setup setup;
	setup.SelectProjectType();
	setup.SetWindowSize();
}
