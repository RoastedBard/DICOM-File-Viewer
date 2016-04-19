#pragma once

#include "AbstractDICOMDataElement.h"

class SQ_Element : public AbstractDICOMDataElement
{
public:
	unsigned int value;
	std::vector<AbstractDICOMDataElement*> sqAttributes;

public:
	SQ_Element()
	{
		_data.valueRepresentation = MC_VR::SQ;
		_data.valueRepresentationString = "SQ";
	}

	virtual void GetValues(int messageId)
	{
		MC_STATUS status;

		status = MC_Get_Value_To_UInt(messageId, _data.tag.tag, &value);

		if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE && status != MC_NULL_VALUE)
				throw std::runtime_error("ERROR: Failed to get SQ value.\n");
	}
};
