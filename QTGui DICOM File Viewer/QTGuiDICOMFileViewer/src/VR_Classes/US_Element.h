#pragma once

#include "Type_Elements/UnsignedIntElement.h"

class US_Element : public UnsignedIntElement
{
public:
	US_Element()
	{
		_data.valueRepresentation = MC_VR::US;
		_data.valueRepresentationString = "US";
	}
};
