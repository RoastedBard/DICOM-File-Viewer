﻿#pragma once

#include "ByteElement.h"

class OD_Element : public ByteElement
{
public:
	OD_Element()
	{
		_data.valueRepresentation = MC_VR::OD;
		_data.valueRepresentationString = "OD";
	}
};
