#pragma once

#include <vector>

#include "mergecom.h"

#include "DICOMTag.h"
#include "CommonElementData.h"

class AbstractDICOMDataElement
{
protected:
	CommonElementData _data; 

public:
	AbstractDICOMDataElement();
	virtual ~AbstractDICOMDataElement();

	virtual void GetValues(int messageId) = 0;
	void		 SetData(const CommonElementData& data);
	DICOMTag	 GetTag() const;
	MC_VR		 GetValueRepresentation() const;
	std::string  GetValueRepresentationString() const;
	int			 GetNumberOfValues() const;
	const char*  GetDescription() const;
};
