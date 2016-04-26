#pragma once

#include "src/VR_Classes/AbstractDICOMDataElement.h"

class DoubleElement : public AbstractDICOMDataElement
{
public:
	std::vector<double> values;

public:
	virtual void GetValues(int messageId);
};
