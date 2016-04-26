#pragma once

#include "Type_Elements/StringElement.h"

class ST_Element : public StringElement
{
public:
	ST_Element()
	{
		_data.valueRepresentation = MC_VR::ST;
		_data.valueRepresentationString = "ST";
		_valueSize = 1024;
	}
};
