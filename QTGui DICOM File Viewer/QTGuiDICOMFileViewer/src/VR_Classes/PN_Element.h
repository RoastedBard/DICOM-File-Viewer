#pragma once

#include "Type_Elements/StringElement.h"

class PN_Element : public StringElement
{
public:
	PN_Element()
	{
		_data.valueRepresentation = MC_VR::PN;
		_data.valueRepresentationString = "PN";
		_valueSize = 128;
	}
};
