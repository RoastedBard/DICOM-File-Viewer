#pragma once

#include "AbstractDICOMDataElement.h"

class DoubleElement : public AbstractDICOMDataElement
{
public:
	std::vector<double> values;

public:
	virtual void GetValues(int messageId);
};
