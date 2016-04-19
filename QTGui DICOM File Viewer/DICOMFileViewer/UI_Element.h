#pragma once

#include "StringElement.h"

class UI_Element : public StringElement
{
public:
	UI_Element()
	{
		_data.valueRepresentation = MC_VR::UI;
		_data.valueRepresentationString = "UI";
		_valueSize = 64;
	}
};
