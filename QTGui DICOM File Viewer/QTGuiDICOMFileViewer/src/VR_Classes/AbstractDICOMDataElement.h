#pragma once

#include <vector>

#include "mergecom.h"

#include "src/Common/DICOMTag.h"
#include "CommonElementData.h"

class AbstractDICOMDataElement
{
protected:
	CommonElementData _data; 

public:
	bool _isValid;

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
	bool		 IsValid() const;
};
