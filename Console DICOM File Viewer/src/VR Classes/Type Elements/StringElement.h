#pragma once

#include "AbstractDICOMDataElement.h"

class StringElement : public AbstractDICOMDataElement
{
protected:
	unsigned long _valueSize;

private:
	void _GetValueLength(int messageId, int valueNumber, unsigned long& bufferLength)
	{
		MC_STATUS status = MC_Get_Value_Length(messageId, _data.tag.tag, valueNumber, &bufferLength);

		if(status == MC_NULL_VALUE)
			values.push_back("");

		else if(status != MC_NORMAL_COMPLETION && status != MC_EMPTY_VALUE)
			throw std::runtime_error("ERROR: Failed to get string value length.\n");

		/* Trim values to specified in derived class length 'valueSize', if it's not an unlimited type of text */
		//if(bufferLength > _valueSize && _data.valueRepresentation != MC_VR::UC && _data.valueRepresentation != MC_VR::UR && _data.valueRepresentation != MC_VR::UT)
			//bufferLength = _valueSize;
			//_isValid = false;
				//;
	}

	void _GetStringValue(int messageId, unsigned long bufferLength, char* buffer, bool multipleValues)
	{
		MC_STATUS status;

		buffer = new char[bufferLength + 1];

		if(multipleValues)
			status = MC_Get_Next_Value_To_String(messageId, _data.tag.tag, bufferLength + 1, buffer);
		else
			status = MC_Get_Value_To_String(messageId, _data.tag.tag, bufferLength + 1, buffer);

		if(status != MC_NORMAL_COMPLETION)
		{
			delete[] buffer;
			throw std::runtime_error("ERROR: Failed to get string value.\n");
		}

		values.push_back(buffer);

		delete[] buffer;
	}

public:
	std::vector<std::string> values;

public:
	StringElement()
	{
		_valueSize = 0;
	}

	virtual void GetValues(int messageId)
	{
		MC_STATUS status;

		char* buffer = NULL;
		unsigned long bufferLength;

		if(_data.numberOfValues == 1)
		{
			_GetValueLength(messageId, 1, bufferLength);

			if(bufferLength > 0)
			{
				_GetStringValue(messageId, bufferLength, buffer, false);
			}
		}
		else
		{
			for(int i = 0; i < _data.numberOfValues; ++i)
			{
				_GetValueLength(messageId, i + 1, bufferLength);

				if(bufferLength > 0)
				{
					_GetStringValue(messageId, bufferLength, buffer, true);
				}
			}
		}
	}
};