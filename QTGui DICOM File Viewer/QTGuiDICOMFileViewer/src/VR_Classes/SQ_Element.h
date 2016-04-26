#pragma once

#include "Type_Elements/UnsignedIntElement.h"

class SQ_Element : public UnsignedIntElement
{
public:
	std::vector<std::vector<AbstractDICOMDataElement*>> sqAttributes;

public:
	SQ_Element()
	{
		_data.valueRepresentation = MC_VR::SQ;
		_data.valueRepresentationString = "SQ";
	}
};
