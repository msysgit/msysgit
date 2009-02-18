#include <windows.h>
#include <stdio.h>
#include "image.h"

PIMAGE_SECTION_HEADER GetSection(LOADED_IMAGE Image, DWORD RVA)
{
	DWORD i;
	PIMAGE_SECTION_HEADER pSection;

	for (i = 0, pSection = Image.Sections; i < Image.NumberOfSections; i++, pSection++)
	{
		if (RVA >= pSection->VirtualAddress && 
			RVA < pSection->VirtualAddress + pSection->Misc.VirtualSize)
		{
			return pSection;
		}
	}
	return NULL;
}

BYTE *GetAddressFromRVA(LOADED_IMAGE Image, DWORD RVA)
{
	int delta;
	PIMAGE_SECTION_HEADER pSection;

	if (!(pSection = GetSection(Image, RVA))) return NULL;
	delta = (int)(pSection->VirtualAddress - pSection->PointerToRawData);
	return (BYTE *)Image.MappedAddress + RVA - delta;
}

