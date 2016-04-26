#pragma once

#include "AbstractDICOMDataElement.h"

class UnsignedIntElement : public AbstractDICOMDataElement
{
public:
	std::vector<unsigned int> values;

public:
	virtual void GetValues(int messageId);
};
