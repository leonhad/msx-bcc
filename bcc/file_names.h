#pragma once

#include <string>

void set_appname(const char *name);

std::string get_appname();

std::string get_apppath();

std::string remove_extension(const char *filename);

std::string add_extension(const char *filename, const char *extension);

std::string get_object_name(const char *filename);

std::string get_assembly_name(const char *filename);

std::string get_executable_name(const char *filename);
