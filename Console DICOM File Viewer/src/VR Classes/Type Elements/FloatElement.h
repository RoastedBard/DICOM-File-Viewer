#pragma once

#include "AbstractDICOMDataElement.h"

class FloatElement : public AbstractDICOMDataElement
{
public:
	std::vector<float> values;

public:
	virtual void GetValues(int messageId);
};
