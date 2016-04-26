#pragma once

#include <string>
#include <sstream>
#include <iomanip>

struct DICOMTag
{
	unsigned long tag;

	std::string group;
	std::string element;

	DICOMTag()
	{
		tag = 0;
	}

	void InitializeTag(unsigned long tag)
	{
		this->tag = tag;

		std::stringstream ss;

		ss<< std::setfill('0') << std::setw(sizeof(unsigned long)*2) << std::hex << std::uppercase <<tag;

		group = ss.str().substr(0, 4);
		element = ss.str().substr(4);
	}
};