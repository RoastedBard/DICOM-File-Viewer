#pragma once

#include "Type_Elements/StringElement.h"

class LT_Element : public StringElement
{
public:
	LT_Element()
	{
		_data.valueRepresentation = MC_VR::LT;
		_data.valueRepresentationString = "LT";
		_valueSize = 1024;
	}
};
