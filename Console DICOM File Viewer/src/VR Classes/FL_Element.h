﻿#pragma once

#include "FloatElement.h"

class FL_Element : public FloatElement
{
public:
	FL_Element()
	{
		_data.valueRepresentation = MC_VR::FL;
		_data.valueRepresentationString = "FL";
	}
};
