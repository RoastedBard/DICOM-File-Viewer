﻿#pragma once

#include "ByteElement.h"

class OL_Element : public ByteElement
{
public:
	OL_Element()
	{
		_data.valueRepresentation = MC_VR::OL;
		_data.valueRepresentationString = "OL";
	}
};