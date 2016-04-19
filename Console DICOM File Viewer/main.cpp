#include <iostream>
#include <conio.h> // _getch()

#include "DICOMFile.h"
#include "diction.h"

#include "ConsolePrinter.h"

void TEST_ElementSearch(const DICOMFile& dicomFile)
{
	/* 1. AbstractDICOMDataElement* FindFirst(MC_VR valueRepresentation) */
	CS_Element* cs_el = static_cast<CS_Element*>(dicomFile.FindFirst(MC_VR::CS));

	/* 2. AbstractDICOMDataElement* FindByTag(std::string group, std::string element) */
	AbstractDICOMDataElement* a_El = dicomFile.FindByTag("0008","1090");

	/* 3. AbstractDICOMDataElement* FindByTag(unsigned long tag) */
	AbstractDICOMDataElement* el = dicomFile.FindByTag(MC_ATT_MANUFACTURER);

	/* 4. std::vector<AbstractDICOMDataElement*> FindAll(MC_VR valueRepresentation) */
	std::vector<AbstractDICOMDataElement*> csVec = dicomFile.FindAll(MC_VR::CS);

	/* 5. std::vector<AbstractDICOMDataElement*> FindAll(std::string group) */
	std::vector<AbstractDICOMDataElement*> csVec_2 = dicomFile.FindAll("0010");

	printf("\n\n\n\t\t\t=========Search results=========\n\n1.\n\n");
	if(cs_el != NULL)
		ConsolePrinter::PrintElement(cs_el);
	else
		printf("Nothing was found");

	printf("\n2.\n\n");
	if(a_El != NULL)
		ConsolePrinter::PrintElement(a_El);
	else
		printf("Nothing was found");

	printf("\n3.\n\n");
	if(el != NULL)
		ConsolePrinter::PrintElement(el);
	else
		printf("Nothing was found");

	printf("\n4.\n\n");
	if(csVec.size() != 0)
		ConsolePrinter::PrintElements(csVec);
	else
		printf("Nothing was found");

	printf("\n5.\n\n");
	if(csVec_2.size() != 0)
		ConsolePrinter::PrintElements(csVec_2);
	else
		printf("Nothing was found");
}

int main()
{
	int applicationId;

	try
	{
		/* Initialization */
		MC_STATUS status = MC_Library_Initialization(NULL, NULL, NULL);

		if(status != MC_NORMAL_COMPLETION)
			throw std::runtime_error("ERROR: Failed to initialize application\n");

		/* Registration */
		status = MC_Register_Application(&applicationId, "My_DICOM_App");

		if(status != MC_NORMAL_COMPLETION)
			throw std::runtime_error("ERROR: Failed to register application\n");

		/* Open a file */
		DICOMFile dicomFile;

		/* Read data from file */
		dicomFile.OpenFile("dicom_TestFiles/RG1_JPLL", applicationId);

		/* Print data */
		ConsolePrinter::PrintElements(dicomFile.GetElements());

		/* Search for element */
		TEST_ElementSearch(dicomFile);

	}
	catch(std::invalid_argument ex)
	{
		printf(ex.what());

	}
	catch(std::runtime_error ex)
	{
		printf(ex.what());
	}

	_getch();

	MC_Library_Release();

	return 0;
}