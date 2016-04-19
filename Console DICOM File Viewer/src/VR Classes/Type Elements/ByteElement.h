#pragma once

#include "AbstractDICOMDataElement.h"

MC_STATUS ByteValueGetFunction(int CBMsgFileItemID, unsigned long CBtag, void* CBuserInfo, int CBdataSize, void* CBdataBuffer, int CBisFirst, int CBisLast);

class ByteElement : public AbstractDICOMDataElement
{
public:
	std::vector<char> value;

public:
	virtual void GetValues(int messageId)
	{
		MC_STATUS status;

		status = MC_Get_Value_To_Function(messageId, _data.tag.tag, this, ByteValueGetFunction);

		if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE)
			throw std::runtime_error("ERROR: Failed to get byte value.\n");
	}
};
