#pragma once

#include "Type_Elements/StringElement.h"

class DS_Element : public StringElement
{
public:
	DS_Element()
	{
		_data.valueRepresentation = MC_VR::DS;
		_data.valueRepresentationString = "DS";
		_valueSize = 16;
	}
};
