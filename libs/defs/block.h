#pragma once

#include <string>
#include <vector>
#include <chrono>

struct Block
{
	std::chrono::system_clock::time_point timestamp;
	std::vector<std::string> commands;
};