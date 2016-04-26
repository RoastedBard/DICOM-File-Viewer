#pragma once

#include "src/VR_Classes/AbstractDICOMDataElement.h"
#include "mergecom.h"

#include <vector>

class DICOMFile
{
private:
	int _fileId;
	std::vector<AbstractDICOMDataElement*> _elements;

private:
	void	  _CreateFile(char *filename);
	void	  _FetchElements(int messageId, std::vector<AbstractDICOMDataElement*>& elements);
	MC_STATUS _ExtractElementInfo(int messageId, std::vector<AbstractDICOMDataElement*>& elements);
	MC_STATUS _InitializeElementData(int messageId, CommonElementData& data);
	void	  _DeleteElements(std::vector<AbstractDICOMDataElement*>& elements);

public:
	~DICOMFile();

	std::vector<AbstractDICOMDataElement*> GetElements() const;
	
	void OpenFile(char *filename, int applicationId);

	AbstractDICOMDataElement* FindFirst(MC_VR valueRepresentation) const; // Finds first occurrence of element with matching valueRepresentation
	AbstractDICOMDataElement* FindByTag(unsigned long tag) const; // Finds element with matching tag
	AbstractDICOMDataElement* FindByTag(std::string group, std::string element) const; // Finds element with matching tag
	
	std::vector<AbstractDICOMDataElement*> FindAll(MC_VR valueRepresentation) const; // Finds all elements with matching valueRepresentation
	std::vector<AbstractDICOMDataElement*> FindAll(std::string group) const; // Finds all elements of specified group

public:
	char buffer[WORK_BUFFER_SIZE];
	FILE* fp;
};
