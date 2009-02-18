#ifndef IMAGE_H
#define IMAGE_H

#include <imagehlp.h>
PIMAGE_SECTION_HEADER GetSection(LOADED_IMAGE Image, DWORD RVA);
BYTE *GetAddressFromRVA(LOADED_IMAGE Image, DWORD RVA);

#endif // IMAGE_H