#pragma once
#include "App.h"
#include <cstdio>

class Test1 : public App {
public:
	Test1() {};
	void TestFunction() override {
		printf("I am Test One\n");
	}
};
