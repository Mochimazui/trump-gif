#pragma once

#include <string>

std::string leftPageFileName();
std::string rightPageFileName();

std::string outputDirectory();
std::string outputFileName();

void setLeftPageFileName(const std::string &s);
void setRightPageFileName(const std::string &s);

void setOutputDirectory(const std::string &s);
void setOutputFileName(const std::string &s);
