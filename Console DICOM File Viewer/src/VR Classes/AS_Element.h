#pragma once

#include "StringElement.h"

class AS_Element : public StringElement
{
public:
	AS_Element()
	{
		_data.valueRepresentation = MC_VR::AS;
		_data.valueRepresentationString = "AS";
		_valueSize = 4;
	}
};
