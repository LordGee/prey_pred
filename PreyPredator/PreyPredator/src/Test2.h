#pragma once
#include "App.h"
#include <cstdio>

class Test2 : public App {
public:

	void TestFunction() override {
		printf("I am Test Two\n");
	}
};
