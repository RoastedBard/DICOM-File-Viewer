#pragma once

#include "Type_Elements/StringElement.h"

class DA_Element : public StringElement
{
public:
	DA_Element()
	{
		_data.valueRepresentation = MC_VR::DA;
		_data.valueRepresentationString = "DA";
		_valueSize = 8;
	}
};
