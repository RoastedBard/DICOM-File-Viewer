#pragma once

#include "StringElement.h"

class TM_Element : public StringElement
{
public:
	TM_Element()
	{
		_data.valueRepresentation = MC_VR::TM;
		_data.valueRepresentationString = "TM";
		_valueSize = 14;
	}
};
