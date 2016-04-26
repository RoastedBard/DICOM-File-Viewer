#pragma once

#include "Type_Elements/StringElement.h"

class UT_Element : public StringElement
{
public:
	UT_Element()
	{
		_data.valueRepresentation = MC_VR::UT;
		_data.valueRepresentationString = "UT";
	}
};
