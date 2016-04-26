#pragma once

#include "src/VR_Classes/AbstractDICOMDataElement.h"

class StringElement : public AbstractDICOMDataElement
{
protected:
	unsigned long _valueSize;

private:
	void _GetValueLength(int messageId, int valueNumber, unsigned long& bufferLength);
	void _GetStringValue(int messageId, unsigned long bufferLength, char* buffer, bool multipleValues);

public:
	std::vector<std::string> values;

public:
	StringElement();
	virtual void GetValues(int messageId);
};
