
#include "shared.h"

static std::string s_left_page_file_name = R"(example/side-1.png)";
static std::string s_right_page_file_name = R"(example/side-2.png)";

static std::string s_output_file_name = R"()";

std::string leftPageFileName() {
	return s_left_page_file_name;
}

std::string rightPageFileName() {
	return s_right_page_file_name;
}

std::string outputFileName() {
	return s_output_file_name;
}

void setLeftPageFileName(const std::string &s) {
	s_left_page_file_name = s;
}

void setRightPageFileName(const std::string &s) {
	s_right_page_file_name = s;
}

void setOutputFileName(const std::string &s) {
	s_output_file_name = s;
}
