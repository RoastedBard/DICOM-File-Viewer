#pragma once

#include "Type_Elements/StringElement.h"

class UC_Element : public StringElement
{
public:
	UC_Element()
	{
		_data.valueRepresentation = MC_VR::UC;
		_data.valueRepresentationString = "UC";
	}
};
