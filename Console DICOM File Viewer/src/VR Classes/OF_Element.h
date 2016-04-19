#pragma once

#include "ByteElement.h"

class OF_Element : public ByteElement
{
public:
	OF_Element()
	{
		_data.valueRepresentation = MC_VR::OF;
		_data.valueRepresentationString = "OF";
	}
};
