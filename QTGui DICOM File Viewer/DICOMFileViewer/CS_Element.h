#pragma once

#include "StringElement.h"

class CS_Element : public StringElement
{
public:
	CS_Element()
	{
		_data.valueRepresentation = MC_VR::CS;
		_data.valueRepresentationString = "CS";
		_valueSize = 16;
	}
};
