#pragma once

#include "AbstractDICOMDataElement.h"

class AT_Element : public AbstractDICOMDataElement
{
public:
	std::vector<DICOMTag> values;

public:
	AT_Element()
	{
		_data.valueRepresentation = MC_VR::AT;
		_data.valueRepresentationString = "AT";
	}

	virtual void GetValues(int messageId)
	{
		MC_STATUS status;

		unsigned long tagValue = 0;

		if(_data.numberOfValues == 1)
		{
			status = MC_Get_Value_To_ULongInt(messageId, _data.tag.tag, &tagValue);

			if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE && status != MC_NULL_VALUE)
				throw std::runtime_error("ERROR: Failed to get AT value.\n");

			DICOMTag tag;
			tag.InitializeTag(tagValue);

			values.push_back(tag);
		}
		else
		{
			for(int i = 0; i < _data.numberOfValues; ++i)
			{
				status = MC_Get_Value_To_ULongInt(messageId, _data.tag.tag, &tagValue);

				if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE && status != MC_NULL_VALUE)
					throw std::runtime_error("ERROR: Failed to get AT value.\n");

				DICOMTag tag;
				tag.InitializeTag(tagValue);

				values.push_back(tag);

				tagValue = 0;
			}
		}
	}
};
