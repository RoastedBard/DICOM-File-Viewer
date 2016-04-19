#pragma once

#include "DoubleElement.h"

class FD_Element : public DoubleElement
{
public:
	FD_Element()
	{
		_data.valueRepresentation = MC_VR::FD;
		_data.valueRepresentationString = "FD";
	}
};
