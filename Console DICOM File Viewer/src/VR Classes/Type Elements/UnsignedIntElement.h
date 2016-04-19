#pragma once

#include "AbstractDICOMDataElement.h"

class UnsignedIntElement : public AbstractDICOMDataElement
{
public:
	std::vector<unsigned int> values;

public:
	virtual void GetValues(int messageId)
	{
		MC_STATUS status;

		unsigned int buffer = 0;

		if(_data.numberOfValues == 1)
		{
			status = MC_Get_Value_To_UInt(messageId, _data.tag.tag, &buffer);

			if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE && status != MC_NULL_VALUE)
				throw std::runtime_error("ERROR: Failed to get unsigned int value.\n");

			values.push_back(buffer);
		}
		else
		{
			for(int i = 0; i < _data.numberOfValues; ++i)
			{
				status = MC_Get_Next_Value_To_UInt(messageId, _data.tag.tag, &buffer);

				if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE && status != MC_NULL_VALUE)
					throw std::runtime_error("ERROR: Failed to get unsigned int value.\n");

				values.push_back(buffer);
				buffer = 0;
			}
		}
	}
};