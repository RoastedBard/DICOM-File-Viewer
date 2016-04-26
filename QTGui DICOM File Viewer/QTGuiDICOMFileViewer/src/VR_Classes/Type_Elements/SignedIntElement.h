#pragma once

#include "src/VR_Classes/AbstractDICOMDataElement.h"

class SignedIntElement : public AbstractDICOMDataElement
{
public:
	std::vector<signed int> values;

public:
	virtual void GetValues(int messageId);
};
