#pragma once

#include "Type_Elements/ByteElement.h"

class OB_Element : public ByteElement
{
public:
	OB_Element()
	{
		_data.valueRepresentation = MC_VR::OB;
		_data.valueRepresentationString = "OB";
	}
};
