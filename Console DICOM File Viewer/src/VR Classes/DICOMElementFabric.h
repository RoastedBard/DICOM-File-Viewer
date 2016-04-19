#pragma once

#include "AE_Element.h"
#include "AS_Element.h"
#include "AT_Element.h"
#include "CS_Element.h"
#include "DA_Element.h"
#include "DS_Element.h"
#include "DT_Element.h"
#include "IS_Element.h"
#include "LO_Element.h"
#include "LT_Element.h"
#include "PN_Element.h"
#include "SH_Element.h"
#include "ST_Element.h"
#include "TM_Element.h"
#include "UT_Element.h"
#include "UI_Element.h"
#include "SS_Element.h"
#include "US_Element.h"
#include "SL_Element.h"
#include "UL_Element.h"
#include "FL_Element.h"
#include "FD_Element.h"
#include "OB_Element.h"
#include "OW_Element.h"
#include "OF_Element.h"
#include "SQ_Element.h"
#include "UN_Element.h"

class DICOMElementFabric
{
public:
	static AbstractDICOMDataElement* CreateElement(MC_VR valueRepresentation)
	{
		switch (valueRepresentation)
		{
		case AE:
			return new AE_Element();
			break;

		case AS:
			return new AS_Element();
			break; 

		case AT:
			return new AT_Element();
			break; 

		case CS:
			return new CS_Element();
			break; 

		case DA:
			return new DA_Element();
			break;

		case DS:
			return new DS_Element();
			break; 

		case DT:
			return new DT_Element();
			break;

		case IS:
			return new IS_Element();
			break;

		case LO:
			return new LO_Element();
			break;

		case LT:
			return new LT_Element();
			break;

		case PN:
			return new PN_Element();
			break; 

		case SH:
			return new SH_Element();
			break; 

		case ST:
			return new ST_Element();
			break; 

		case TM:
			return new TM_Element();
			break; 

		case UT:
			return new UT_Element();
			break; 

		case UI:
			return new UI_Element();
			break; 

		case SS:
			return new SS_Element();
			break; 

		case US:
			return new US_Element();
			break; 

		case SL:
			return new SL_Element();
			break; 

		case UL:
			return new UL_Element();
			break; 

		case FL:
			return new FL_Element();
			break; 

		case FD:
			return new FD_Element();
			break; 

		case OB:
			return new OB_Element();
			break; 

		case OW:
			return new OW_Element();
			break; 

		case OF:
			return new OF_Element();
			break; 

		case SQ:
			return new SQ_Element();
			break; 

		case UNKNOWN_VR:
			return new UN_Element();
			break;

		default:
			return NULL;
			break;
		}
	}

	
};