#pragma once

#include "src/VR_Classes/AbstractDICOMDataElement.h"

class UnsignedIntElement : public AbstractDICOMDataElement
{
public:
	std::vector<unsigned int> values;

public:
	virtual void GetValues(int messageId);
};
