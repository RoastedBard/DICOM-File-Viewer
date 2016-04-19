﻿#pragma once

#include "SignedIntElement.h"

class SL_Element : public SignedIntElement
{
public:
	SL_Element()
	{
		_data.valueRepresentation = MC_VR::SL;
		_data.valueRepresentationString = "SL";
	}
};
