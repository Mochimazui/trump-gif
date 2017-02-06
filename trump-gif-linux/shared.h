#pragma once

#include <string>

std::string leftPageFileName();
std::string rightPageFileName();

std::string outputDirectory();

void setLeftPageFileName(const std::string &s);
void setRightPageFileName(const std::string &s);

void setOutputDirectory(const std::string &s);
