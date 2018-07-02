
#pragma once

#define DEBUG

#include <iostream>
#include <string>

	//TODO: log into real logs file ifndef DEBUG
	//TODO: turn functions into one log(va_list...)

template <typename T>
void  log(const T) {
	#ifdef DEBUG
		std::cout << mesg << std::endl;
	#endif
}
