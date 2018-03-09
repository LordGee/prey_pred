#include "SDL.h"
#include <cstdio>
#include "Test1.h"
#include "Test2.h"

int main(int argc, char* args[]) {
	printf("Hello PREY\n");

	App* one = new Test1();
	App* two = new Test2();
	one->TestFunction();
	two->TestFunction();

	system("PAUSE");
	return 1;
}
