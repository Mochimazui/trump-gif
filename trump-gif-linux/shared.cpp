
#include "shared.h"

static std::string s_left_page_file_name = R"(E:\video\you-1.jpg)";
static std::string s_right_page_file_name = R"(E:\video\you-2.jpg)";

static std::string s_output_directory = R"(E:\video\output\)";

std::string leftPageFileName() {
	return s_left_page_file_name;
}

std::string rightPageFileName() {
	return s_right_page_file_name;
}

std::string outputDirectory() {
	return s_output_directory;
}

void setLeftPageFileName(const std::string &s) {
	s_left_page_file_name = s;
}

void setRightPageFileName(const std::string &s) {
	s_right_page_file_name = s;
}

void setOutputDirectory(const std::string &s) {
	s_output_directory = s;
}
