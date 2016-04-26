#pragma once

#include "mergecom.h"
#include "src/Common/DICOMTag.h"

struct CommonElementData
{
	DICOMTag				 tag;
	MC_VR					 valueRepresentation;
	std::string				 valueRepresentationString;
	int						 numberOfValues;
	char					 description[128];
};
