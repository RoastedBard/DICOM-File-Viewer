#pragma once

#include "AbstractDICOMDataElement.h"

MC_STATUS ByteValueGetFunction(int CBMsgFileItemID, unsigned long CBtag, void* CBuserInfo, int CBdataSize, void* CBdataBuffer, int CBisFirst, int CBisLast);

class ByteElement : public AbstractDICOMDataElement
{
public:
	std::vector<char> value;

public:
	virtual void GetValues(int messageId);
};
