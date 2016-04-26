#pragma once

#include "Type_Elements/StringElement.h"

class IS_Element : public StringElement
{
public:
	IS_Element()
	{
		_data.valueRepresentation = MC_VR::IS;
		_data.valueRepresentationString = "IS";
		_valueSize = 12;
	}
};
