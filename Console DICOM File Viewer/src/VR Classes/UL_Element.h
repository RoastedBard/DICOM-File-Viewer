#pragma once

#include "UnsignedIntElement.h"

class UL_Element : public UnsignedIntElement
{
public:
	UL_Element()
	{
		_data.valueRepresentation = MC_VR::UL;
		_data.valueRepresentationString = "UL";
	}
};
