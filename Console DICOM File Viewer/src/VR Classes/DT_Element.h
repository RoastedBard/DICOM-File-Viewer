#pragma once

#include "StringElement.h"

class DT_Element : public StringElement
{
public:
	DT_Element()
	{
		_data.valueRepresentation = MC_VR::DT;
		_data.valueRepresentationString = "DT";
		_valueSize = 26;
	}
};
