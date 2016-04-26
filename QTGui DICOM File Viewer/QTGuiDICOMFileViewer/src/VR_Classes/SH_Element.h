#pragma once

#include "Type_Elements/StringElement.h"

class SH_Element : public StringElement
{
public:
	SH_Element()
	{
		_data.valueRepresentation = MC_VR::SH;
		_data.valueRepresentationString = "SH";
		_valueSize = 16;
	}
};
