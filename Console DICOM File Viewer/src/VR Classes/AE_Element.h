#pragma once

#include "StringElement.h"

class AE_Element : public StringElement
{
public:
	AE_Element()
	{
		_data.valueRepresentation = MC_VR::AE;
		_data.valueRepresentationString = "AE";
		_valueSize = 16;
	}
};
