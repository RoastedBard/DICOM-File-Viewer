#include "mergecom.h"

#include "ByteElement.h"

MC_STATUS ByteValueGetFunction(int CBMsgFileItemID, unsigned long CBtag, void* CBuserInfo, int CBdataSize, void* CBdataBuffer, int CBisFirst, int CBisLast)
{
	if(CBisFirst)
	{
		// Reads only first 4 bytes or less
		if(CBdataSize > 4)
			CBdataSize = 4;

		for(int i = 0; i < CBdataSize; ++i)
			static_cast<ByteElement*>(CBuserInfo)->value.push_back(((const unsigned char*)CBdataBuffer)[i]);
	}

	return MC_NORMAL_COMPLETION;
}

void ByteElement::GetValues(int messageId)
{
	MC_STATUS status;

	status = MC_Get_Value_To_Function(messageId, _data.tag.tag, this, ByteValueGetFunction);

	if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE)
		throw std::runtime_error("ERROR: Failed to get byte value.\n");
}