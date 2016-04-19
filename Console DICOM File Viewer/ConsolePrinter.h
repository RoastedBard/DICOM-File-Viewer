#pragma once

#include "AT_Element.h"
#include "CS_Element.h"
#include "SQ_Element.h"
#include "StringElement.h"
#include "SignedIntElement.h"
#include "UnsignedIntElement.h"
#include "FloatElement.h"
#include "DoubleElement.h"
#include "ByteElement.h"

class ConsolePrinter
{
private:
	static bool _isSQ;

public:
	static void PrintValues(AbstractDICOMDataElement* element);
	static void PrintElement(AbstractDICOMDataElement* element);
	static void PrintElements(std::vector<AbstractDICOMDataElement*> elements);
};