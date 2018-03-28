#pragma once
#include <vector>
#include <ostream>
#include <fstream>

static void FileWiter(std::vector<float> log) {
	const char* saveFile = "data/test.csv";
	std::ofstream wf;
	wf.open(saveFile);
	for (unsigned int i = 0; i < log.size(); i++) {
		wf << log[i] << "," << std::endl;
	}
	wf.close();
}
