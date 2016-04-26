#pragma once

#include "Type_Elements/StringElement.h"

class LO_Element : public StringElement
{
public:
	LO_Element()
	{
		_data.valueRepresentation = MC_VR::LO;
		_data.valueRepresentationString = "LO";
		_valueSize = 64;
	}
};
