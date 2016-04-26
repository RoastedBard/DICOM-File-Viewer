#pragma once

#include "AbstractDICOMDataElement.h"

MC_STATUS UNValueGetFunction(int CBMsgFileItemID, unsigned long CBtag, void* CBuserInfo, int CBdataSize, void* CBdataBuffer, int CBisFirst, int CBisLast);

class UN_Element : public AbstractDICOMDataElement
{
public:
	std::vector<char> value;

public:
	UN_Element()
	{
		_data.valueRepresentation = MC_VR::UNKNOWN_VR;
		_data.valueRepresentationString = "UNKNOWN_VR";
	}

	virtual void GetValues(int messageId)
	{
		MC_STATUS status;

		status = MC_Get_Value_To_Function(messageId, _data.tag.tag, this, UNValueGetFunction);

		if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE)
				throw std::runtime_error("ERROR: Failed to get UNKNOWN_VR value.\n");
	}
};

MC_STATUS UNValueGetFunction(int CBMsgFileItemID, unsigned long CBtag, void* CBuserInfo, int CBdataSize, void* CBdataBuffer, int CBisFirst, int CBisLast)
{
	for(int i = 0; i < CBdataSize; ++i)
		static_cast<UN_Element*>(CBuserInfo)->value.push_back(((const char*)CBdataBuffer)[i]);

	return MC_NORMAL_COMPLETION;
}