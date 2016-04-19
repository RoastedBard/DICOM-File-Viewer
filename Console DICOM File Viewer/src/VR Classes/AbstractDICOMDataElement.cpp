#include "AbstractDICOMDataElement.h"

AbstractDICOMDataElement::AbstractDICOMDataElement()
{
	_data.valueRepresentation = UNKNOWN_VR;
	_data.valueRepresentationString = "UNKNOWN_VR";
	_data.numberOfValues = 0;
	_data.description[0] = 0;
}

AbstractDICOMDataElement::~AbstractDICOMDataElement()
{
}

void AbstractDICOMDataElement::SetData(const CommonElementData& data)
{
	strcpy(_data.description, data.description);
	_data.numberOfValues = data.numberOfValues;
	_data.tag = data.tag;
}

DICOMTag AbstractDICOMDataElement::GetTag() const
{
	return _data.tag;
}

MC_VR AbstractDICOMDataElement::GetValueRepresentation() const
{
	return _data.valueRepresentation;
}

std::string AbstractDICOMDataElement::GetValueRepresentationString() const
{
	return _data.valueRepresentationString;
}

int AbstractDICOMDataElement::GetNumberOfValues() const
{
	return _data.numberOfValues;
}

const char* AbstractDICOMDataElement::GetDescription() const
{
	return _data.description;
}