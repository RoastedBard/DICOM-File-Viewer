#include "ConsolePrinter.h"

bool ConsolePrinter::_isSQ = false;

void ConsolePrinter::PrintValues(AbstractDICOMDataElement* element)
{
	switch(element->GetValueRepresentation())
	{
	case AE:case AS:case CS:case DA:case DS:case DT:case IS:case LO:case LT:case PN:case SH:case ST:case TM:case UT:case UI:case UC:case UR:
		{
			StringElement *sEl = static_cast<StringElement*>(element);
			for(int i = 0; i < element->GetNumberOfValues(); ++i)
			{
				printf("%s", sEl->values[i].c_str());

				/* Insert delimeter '\' between elements if attribute have multiple values */
				if(i != sEl->values.size() - 1)
					printf("\\");
			}
			break; 
		}
	case SS:case SL:
		{
			SignedIntElement *sIntEl = static_cast<SignedIntElement*>(element);
			for(int i = 0; i < element->GetNumberOfValues(); ++i)
			{
				printf("%d", sIntEl->values[i]);

				/* Insert delimeter '\' between elements if attribute have multiple values */
				if(i != sIntEl->values.size() - 1)
					printf("\\");
			}
			break; 
		}
	case US: case UL:
		{
			UnsignedIntElement *uIntEl = static_cast<UnsignedIntElement*>(element);
			for(int i = 0; i < element->GetNumberOfValues(); ++i)
			{
				printf("%d", uIntEl->values[i]);

				/* Insert delimeter '\' between elements if attribute have multiple values */
				if(i != uIntEl->values.size() - 1)
					printf("\\");
			}
			break; 
		} 
	case FL:
		{
			FloatElement *fEl = static_cast<FloatElement*>(element);
			for(int i = 0; i < element->GetNumberOfValues(); ++i)
			{
				printf("%f", fEl->values[i]);

				/* Insert delimeter '\' between elements if attribute have multiple values */
				if(i != fEl->values.size() - 1)
					printf("\\");
			}
			break; 
		} 

	case FD:
		{
			DoubleElement *dEl = static_cast<DoubleElement*>(element);
			for(int i = 0; i < element->GetNumberOfValues(); ++i)
			{
				printf("%f", dEl->values[i]);

				/* Insert delimeter '\' between elements if attribute have multiple values */
				if(i != dEl->values.size() - 1)
					printf("\\");
			}
			break; 
		} 

	case OB:case OW:case OF:case OD:case OL:
		{
			ByteElement *bEl = static_cast<ByteElement*>(element);
			for(int i = 0; i < bEl->value.size(); ++i)
				printf("(#%02x)", bEl->value[i] & 0xff);
			break;
		}
	case SQ:
		{
			//SQ_Element *sqEl = static_cast<SQ_Element*>(element);
			//for(int i = 0; i < sqEl->GetNumberOfValues(); ++i)
			//printf("%d", sqEl->values[i]);
			break; 
		}
	case AT:
		{
			AT_Element* atEl = static_cast<AT_Element*>(element);
			for(int i = 0; i < atEl->values.size(); ++i)
				printf("(%s,%s) ", atEl->values[i].group.c_str(), atEl->values[i].element.c_str());
			break;
		}

	case UNKNOWN_VR:
		printf("UNKNOWN VALUE");
		break;
	}
}

void ConsolePrinter::PrintElement(AbstractDICOMDataElement* element)
{
	if(element->GetValueRepresentation() == MC_VR::SQ || _isSQ == true)
		printf("\t");

	/* Print tag */
	printf("(%s,%s) ", element->GetTag().group.c_str(), element->GetTag().element.c_str());

	/* Print VR */
	printf("%s ", element->GetValueRepresentationString().c_str());

	/* Print desription */
	printf("%s ", element->GetDescription());

	/* Print values */
	printf("< ");
	PrintValues(element);
	printf(" >\n");
}

void ConsolePrinter::PrintSQ(SQ_Element* rootElement)
{
	for(int j = 0; j < rootElement->sqAttributes.size(); ++j)
	{
		PrintElements(rootElement->sqAttributes[j]);
	}
}

void ConsolePrinter::PrintElements(std::vector<AbstractDICOMDataElement*> elements)
{
	for(int i = 0; i < elements.size(); ++i)
	{
		PrintElement(elements[i]);

		if(elements[i]->GetValueRepresentation() == MC_VR::SQ)
		{
			_isSQ = true;
			PrintSQ(static_cast<SQ_Element*>(elements[i]));
			_isSQ = false;
		}
	}
}