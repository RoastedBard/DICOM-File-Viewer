#include "DICOMFile.h"

#include <string>
#include <fstream>

#include "mc3media.h"

#include "src/VR_Classes/DICOMElementFabric.h"

/* Function which will be called repeatedly to request blocks of DICOM file data from media. */
MC_STATUS MediaToFile(char *filename, void *userInfo, int *dataSize, void **dataBuffer, int isFirst, int *isLast)
{
	if(userInfo == NULL)
		throw std::invalid_argument("ERROR: userInfo parameter in 'MediaToFile' is NULL.\n");

	DICOMFile *dicomFile = static_cast<DICOMFile*>(userInfo);

	size_t dataread;

	if(isFirst)
	{
		dicomFile->fp = fopen(filename, "rb");
		if(!dicomFile->fp)
			return MC_CALLBACK_CANNOT_COMPLY;
	}

	dataread = fread(dicomFile->buffer,1,sizeof(dicomFile->buffer),dicomFile->fp);

	if(feof(dicomFile->fp))
		*isLast = 1;

	if (dataread > 0)
		*dataSize = (int)dataread;

	*dataBuffer = dicomFile->buffer;

	return MC_NORMAL_COMPLETION;
}

void DICOMFile::_DeleteElements(std::vector<AbstractDICOMDataElement*>& elements)
{
	for(int i = 0; i < elements.size(); ++i)
	{
		if(elements[i]->GetValueRepresentation() == SQ)
		{
			for(int j = 0; j < static_cast<SQ_Element*>(elements[i])->sqAttributes.size(); ++j)
				_DeleteElements(static_cast<SQ_Element*>(elements[i])->sqAttributes[j]);
		}

		delete elements[i];
	}
}

DICOMFile::~DICOMFile()
{
	_DeleteElements(_elements);
	_elements.clear();
}

void DICOMFile::_CreateFile(char *filename)
{
	MC_STATUS status = MC_Create_Empty_File(&_fileId, filename);

	if(status != MC_NORMAL_COMPLETION)
		throw std::runtime_error("ERROR: Failed to create file\n");
}

void DICOMFile::OpenFile(char *filename, int applicationId)
{
	_elements.clear();

	_CreateFile(filename);

	MC_STATUS status = MC_Open_File(applicationId, _fileId, this, MediaToFile);

	if(status != MC_NORMAL_COMPLETION)
		throw std::invalid_argument("ERROR: Failed to open file.\n");

	memset(buffer, 0, WORK_BUFFER_SIZE);

	fclose(fp);

	_FetchElements(_fileId, _elements);

	MC_Free_File(&_fileId);
}

std::vector<AbstractDICOMDataElement*> DICOMFile::GetElements() const
{
	return _elements;
}

void DICOMFile::_FetchElements(int messageId, std::vector<AbstractDICOMDataElement*>& elements)
{
	MC_STATUS status = MC_NORMAL_COMPLETION;

	while(status != MC_NO_MORE_ATTRIBUTES)
	{
		status = _ExtractElementInfo(messageId, elements);
	}
}

MC_STATUS DICOMFile::_ExtractElementInfo(int messageId, std::vector<AbstractDICOMDataElement*>& elements)
{
	AbstractDICOMDataElement *element;

	CommonElementData data;

	MC_STATUS status = _InitializeElementData(messageId, data);

	if(status == MC_INVALID_MESSAGE_ID)
		throw std::invalid_argument("ERROR: Invalid message ID.\n");

	if(status == MC_MESSAGE_EMPTY)
		throw std::runtime_error("ERROR: Message is Empty");

	if(status == MC_NO_MORE_ATTRIBUTES || status == MC_NO_MORE_VALUES)
		return status;

	element = DICOMElementFabric::CreateElement(data.valueRepresentation);

	element->SetData(data);

	element->GetValues(messageId);

	if(element->GetValueRepresentation() == SQ)
	{
		for(int i = 0; i < static_cast<SQ_Element*>(element)->values.size(); ++i)
		{
			if(static_cast<SQ_Element*>(element)->values[i] == 0)
				continue;

			std::vector<AbstractDICOMDataElement*> item;
			static_cast<SQ_Element*>(element)->sqAttributes.push_back(item);

			_FetchElements(static_cast<SQ_Element*>(element)->values[i], static_cast<SQ_Element*>(element)->sqAttributes.back());
		}

		elements.push_back(element);
	}
	else
		elements.push_back(element);

	return status;
}

MC_STATUS DICOMFile::_InitializeElementData(int messageId, CommonElementData& data)
{
	unsigned long tag;
	MC_STATUS status = MC_Get_Next_Attribute(messageId, &tag, &data.valueRepresentation, &data.numberOfValues);

	if(status == MC_NO_MORE_ATTRIBUTES || status == MC_NO_MORE_VALUES || status == MC_MESSAGE_EMPTY || status == MC_INVALID_MESSAGE_ID)
		return status;

	data.tag.InitializeTag(tag);

	status = MC_Get_Tag_Info(data.tag.tag, data.description, 128);

	if(data.description[0] == 0 || status == MC_INVALID_TAG)
		strcpy(data.description, "[Unknown Element]");
}

/* Finds first occurrence of element with matching valueRepresentation */
AbstractDICOMDataElement* DICOMFile::FindFirst(MC_VR valueRepresentation) const
{
	if(_elements.size() == 0)
		throw std::runtime_error("ERROR: Element array is empty.\n");

	for(int i = 0; i < _elements.size(); ++i)
	{
		if(_elements[i]->GetValueRepresentation() == valueRepresentation)
			return _elements[i];
	}

	return NULL;
}

/* Finds element with matching tag */
AbstractDICOMDataElement* DICOMFile::FindByTag(std::string group, std::string element) const
{
	if(_elements.size() == 0)
		throw std::runtime_error("ERROR: Element array is empty.\n");

	for(int i = 0; i < _elements.size(); ++i)
	{
		if(_elements[i]->GetTag().group == group && _elements[i]->GetTag().element == element)
			return _elements[i];
	}

	return NULL;
}

/* Finds element with matching tag */
AbstractDICOMDataElement* DICOMFile::FindByTag(unsigned long tag) const
{
	if(_elements.size() == 0)
		throw std::runtime_error("ERROR: Element array is empty.\n");

	for(int i = 0; i < _elements.size(); ++i)
	{
		if(_elements[i]->GetTag().tag == tag)
			return _elements[i];
	}

	return NULL;
}

/* Finds all elements with matching valueRepresentation */
std::vector<AbstractDICOMDataElement*> DICOMFile::FindAll(MC_VR valueRepresentation) const
{
	if(_elements.size() == 0)
		throw std::runtime_error("ERROR: Element array is empty.\n");

	std::vector<AbstractDICOMDataElement*> vec;

	for(int i = 0; i < _elements.size(); ++i)
	{
		if(_elements[i]->GetValueRepresentation() == valueRepresentation)
			vec.push_back(_elements[i]);
	}

	return vec;
}

/* Finds all elements of specified group */
std::vector<AbstractDICOMDataElement*> DICOMFile::FindAll(std::string group) const
{
	if(_elements.size() == 0)
		throw std::runtime_error("ERROR: Element array is empty.\n");

	std::vector<AbstractDICOMDataElement*> vec;

	for(int i = 0; i < _elements.size(); ++i)
	{
		if(_elements[i]->GetTag().group == group)
			vec.push_back(_elements[i]);
	}

	return vec;
}
