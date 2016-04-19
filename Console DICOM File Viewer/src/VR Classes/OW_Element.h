#pragma once

#include "ByteElement.h"

class OW_Element : public ByteElement
{
public:
	OW_Element()
	{
		_data.valueRepresentation = MC_VR::OW;
		_data.valueRepresentationString = "OW";
	}
};
