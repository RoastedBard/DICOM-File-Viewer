#pragma once

#include "Type_Elements/SignedIntElement.h"

class SS_Element : public SignedIntElement
{
public:
	SS_Element()
	{
		_data.valueRepresentation = MC_VR::SS;
		_data.valueRepresentationString = "SS";
	}
};
