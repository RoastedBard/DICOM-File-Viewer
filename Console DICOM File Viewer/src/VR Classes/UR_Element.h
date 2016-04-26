#pragma once

#include "StringElement.h"

class UR_Element : public StringElement
{
public:
	UR_Element()
	{
		_data.valueRepresentation = MC_VR::UR;
		_data.valueRepresentationString = "UR";
	}
};
