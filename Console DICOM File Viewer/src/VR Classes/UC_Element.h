#pragma once

#include "StringElement.h"

class UC_Element : public StringElement
{
public:
	UC_Element()
	{
		_data.valueRepresentation = MC_VR::UC;
		_data.valueRepresentationString = "UC";
	}
};
