#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "directory.h"
#include "image.h"
#define EXECUTABLES "*.exe;*.dll;*.sys;*.pyd"

int SearchImport(char *ImportDLL, char *ImportFunction, char *SourcePath);
int SearchExport(char *ExportFunction, char *SourcePath);
int SearchImportWithImageHlp(char *InputPath, char *ImportDLL, char *ImportFunction);
int SearchExportWithImageHlp(char *InputPath, char *ExportFunction);

void Usage(char *ProgramName)
{
	printf("Usage: %s test.dll c:\\dir\\test.exe\n", ProgramName);
	printf("\tReport if c:\\dir\\test.exe imports test.dll\n");
	printf("\nExamples:\n");
	printf("%s test.dll!funcname c:\\dir\\test.exe\n", ProgramName);
	printf("\tReport if c:\\dir\\test.exe imports test.dll!funcname\n");
	printf("%s test.dll c:\\dir\n", ProgramName);
	printf("\tFind executables importing test.dll in c:\\dir\n");
	printf("%s test.dll!funcname c:\\dir\n", ProgramName);
	printf("\tFind executables importing funcname from test.dll in c:\\dir\n");
	printf("%s test!funcname c:\\dir\n", ProgramName);
	printf("\tFind executables importing funcname from test.dll in c:\\dir\n");
	printf("%s test!ord_1234 c:\\dir\n", ProgramName);
	printf("\tFind executables importing ordinal 1234 (in decimal) from test.dll in c:\\dir\n");
	printf("\tNOTE: this only works if there is no name associated with the function\n");
	printf("%s -e funcname c:\\dir\n", ProgramName);
	printf("\tFind all DLLs exporting funcname in c:\\dir\n");
}

// Try to match Target against Source
BOOL CompareFilenames(char *Target, char *Source)
{
	DWORD i;
	BOOL HasExtension = FALSE;

	if (!Target || !Source || !Target[0] || !Source[0]) return FALSE;
	if (strchr(Source, '.')) HasExtension = TRUE;

	// If we don't need to consider that the source may lack an extension, 
	// then the lengths must be the same
	if (HasExtension && strlen(Target) != strlen(Source)) return FALSE;

	for (i = 0; i < strlen(Source); i++)
	{
		if (tolower(Target[i]) != tolower(Source[i])) return FALSE;
	}


	if (HasExtension)
	{
		if (Target[i]) return FALSE;
		else return TRUE;
	}
	else
	{
		if (Target[i] == '.') return TRUE;
		else return FALSE;
	}
}

int main(int argc, char* argv[])
{
	char *ImportFunction;

	if (argc < 2)
	{
		Usage(argv[0]);
		return -1;
	}

	if (argv[1][0] == '-')
		
	{
		if (tolower(argv[1][1]) != 'e')
		{
			fprintf(stderr, "Error: -e is the only valid option\n");
			Usage(argv[0]);
			return -1;
		}

		if (argc != 3 && argc != 4)
		{
			fprintf(stderr, "Error: incorrect number of parameters for export searching\n");
			Usage(argv[0]);
			return -1;
		}

		if (strchr(argv[2], '!'))
		{
			fprintf(stderr, "Error: you cannot pass a dll!func format with -e\n");
			Usage(argv[0]);
			return -1;
		}

		if (argc == 4) return SearchExport(argv[2], argv[3]);
		else return SearchExport(argv[2], NULL);
	}

	else
	{
		if (argc != 3)
		{
			fprintf(stderr, "Error: incorrect number of parameters for import searching\n");
			Usage(argv[0]);
			return -1;
		}

		if ((ImportFunction = strchr(argv[1], '!')) != NULL)
		{
			*ImportFunction++ = '\0';
			return SearchImport(argv[1], ImportFunction, argv[2]);
		}
		else return SearchImport(argv[1], NULL, argv[2]);
	}

	return 0;
}

int SearchImport(char *ImportDLL, char *ImportFunction, char *SourcePath)
{
	PDIRECTORY_INFO pDirectory;
	PSEARCH_RESULTS result;	

	if (!(pDirectory = DirectoryOpen(SourcePath, TRUE))) return -1;
	if (!DirectorySearch(pDirectory, EXECUTABLES)) return -1;

	for (result = pDirectory->pSearchResults; result; result = result->Next)
	{
		SearchImportWithImageHlp(result->FilePath, ImportDLL, ImportFunction);
	}

	DirectoryClose(pDirectory);
	return 0;
}

int SearchImportWithImageHlp(char *InputPath, char *ImportDLL, char *ImportFunction)
{
	DWORD i = 0;
	BOOL ModuleFound;
	char *Filename, *ModuleName;

	// Used to read import table
	LOADED_IMAGE Image;
	IMAGE_DATA_DIRECTORY ImportDirectory;
	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
	PIMAGE_THUNK_DATA pThunk, pThunkIAT;
	PIMAGE_IMPORT_BY_NAME pOrdinalName;
	USHORT ImportOrdinal = 0;
	BOOL UseOrdinal = FALSE;

	if (!(Filename = strrchr(InputPath, '\\')))
	{
		fprintf(stderr, "Error: unexpected file \"%s\"\n", InputPath);
		return -1;
	}
	*Filename++ = '\0';

	//printf("Loading %s\n", Filename);
	// TODO: under what circumstances does this fail?
	if (!MapAndLoad(Filename, InputPath, &Image, FALSE, TRUE))
	{
		fprintf(stderr, "Unable to map and load %s\n", Filename);
		return -1;
	}

	ImportDirectory = Image.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	if (!ImportDirectory.VirtualAddress) return 0; // no imports

	if (ImportDirectory.Size < sizeof(IMAGE_IMPORT_DESCRIPTOR))
	{
		fprintf(stderr, "Error loading %s: invalid import descriptor table (size < sizeof(IMAGE_IMPORT_DESCRIPTOR))\n", Filename);
		if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
		return -1;
	}

	pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)GetAddressFromRVA(Image, ImportDirectory.VirtualAddress);
	if (!pImportDescriptor)
	{
		fprintf(stderr, "Error loading %s: invalid import descriptor table (invalid RVA)\n", Filename);
		if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
		return -1;
	}
	
	for (i = 0, ModuleFound = FALSE; i < ImportDirectory.Size / sizeof(IMAGE_IMPORT_DESCRIPTOR); i++)
	{
		ModuleName = (char *)GetAddressFromRVA(Image, pImportDescriptor->Name);
		if (!ModuleName || !ModuleName[0]) break;

		if (CompareFilenames(ModuleName, ImportDLL))
		{
			ModuleFound = TRUE;
			break;
		}
		pImportDescriptor++;
	}

	if (!ModuleFound)
	{
		if (!UnMapAndLoad(&Image))
		{
			fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
			return 0;
		}
		return -1;
	}

	if (!ImportFunction)
	{
		printf("Match found: %s\\%s imports the library %s\n", InputPath, Filename, ImportDLL);
		if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
		return 1;
	}

	if (strncmp(ImportFunction, "ord_", 4) == 0)
	{
		ImportOrdinal = atoi(ImportFunction + 4);
		if (!ImportOrdinal && ImportFunction[4] != '0')
		{
			fprintf(stderr, "Error: you passed an invalid ordinal\n");
		    fprintf(stderr, "Should be in the format ord_1234 where 1234 is a decimal number\n");
			if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
			return -1;
		}
		UseOrdinal = TRUE;
	}

	pThunkIAT = (PIMAGE_THUNK_DATA)GetAddressFromRVA(Image, pImportDescriptor->FirstThunk);
	if (!pImportDescriptor->OriginalFirstThunk) pThunk = pThunkIAT;
	else pThunk = (PIMAGE_THUNK_DATA)GetAddressFromRVA(Image, pImportDescriptor->OriginalFirstThunk);
	if (!pThunk || !pThunkIAT)
	{
		fprintf(stderr, "Error loading %s: invalid import descriptor table (neither thunk is set)\n", Filename);
		if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
		return -1;
	}

	for (; ; pThunk++, pThunkIAT++)
	{
		if (!pThunk->u1.AddressOfData) break;
		if (UseOrdinal && pThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG)
		{
			if (ImportOrdinal == IMAGE_ORDINAL(pThunk->u1.Ordinal))
			{
				printf("Match found: %s\\%s imports ordinal %d from %s\n", InputPath, Filename, ImportOrdinal, ImportDLL);
				if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
				return 1;
            }
		}
		else
		{
			pOrdinalName = (PIMAGE_IMPORT_BY_NAME)GetAddressFromRVA(Image, (DWORD)pThunk->u1.AddressOfData);
			if (!pOrdinalName) continue;
				
			if (_stricmp(pOrdinalName->Name, ImportFunction) == 0)
			{
				printf("Match found: %s\\%s imports %s!%s\n", InputPath, Filename, ImportDLL, pOrdinalName->Name);
				if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
				return 1;
			}
		}
	}

	if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
	return 0;
}

int SearchExport(char *ExportFunction, char *SourcePath)
{
	PDIRECTORY_INFO pDirectory;
	PSEARCH_RESULTS result;	

	if (!(pDirectory = DirectoryOpen(SourcePath, TRUE))) return -1;
	if (!DirectorySearch(pDirectory, EXECUTABLES)) return -1;

	for (result = pDirectory->pSearchResults; result; result = result->Next)
	{
		SearchExportWithImageHlp(result->FilePath, ExportFunction);
	}

	DirectoryClose(pDirectory);
	return 0;
}

int SearchExportWithImageHlp(char *InputPath, char *ExportFunction)
{
	char *Filename, *FunctionName;
	// Used to read export table
	PIMAGE_EXPORT_DIRECTORY pExportTable;
	IMAGE_DATA_DIRECTORY ExportDirectory;
	LOADED_IMAGE Image;
	DWORD *pFunctions; // an RVA
	DWORD *pNames; // an RVA
	USHORT *pNameOrdinals;
	USHORT i, j;

	if (!(Filename = strrchr(InputPath, '\\')))
	{
		fprintf(stderr, "Error: unexpected file \"%s\"\n", InputPath);
		return -1;
	}
	*Filename++ = '\0';

	printf("Loading %s\n", Filename);
	if (!MapAndLoad(Filename, InputPath, &Image, FALSE, TRUE))
	{
		fprintf(stderr, "Unable to map and load %s\n", Filename);
		return -1;
	}

	ExportDirectory = Image.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	if (!ExportDirectory.VirtualAddress) return 0; // no exports

	if (ExportDirectory.Size < sizeof(IMAGE_EXPORT_DIRECTORY))
	{
		fprintf(stderr, "Error loading %s: invalid export table (size < sizeof(IMAGE_EXPORT_DIRECTORY))\n", Filename);
		if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
		return -1;
	}

	pExportTable = (PIMAGE_EXPORT_DIRECTORY)GetAddressFromRVA(Image, ExportDirectory.VirtualAddress);
	if (!pExportTable)
	{
		fprintf(stderr, "Error loading %s: invalid export table (invalid RVA)\n", Filename);
		if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
		return -1;
	}

    pFunctions = (DWORD *)GetAddressFromRVA(Image, pExportTable->AddressOfFunctions);
    pNameOrdinals = (USHORT *)GetAddressFromRVA(Image, pExportTable->AddressOfNameOrdinals);
    pNames = (DWORD *)GetAddressFromRVA(Image, pExportTable->AddressOfNames);

	if (!pFunctions || !pNameOrdinals || !pNames)
	{
		fprintf(stderr, "Error loading %s: invalid export table (invalid name/function/ordinal RVAs)\n", Filename);
		if (!UnMapAndLoad(&Image)) fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
		return -1;
	}

	// Rather than just read directly from pNames, we do this to ensure that we're matching
	// a function instead of a variable
	for (i = 0; i < pExportTable->NumberOfFunctions; i++)
	{
		if (!pFunctions[i]) continue;

		for (j = 0; j < pExportTable->NumberOfNames; j++)
		{
			if (i == pNameOrdinals[j])
			{
				FunctionName = (char *)GetAddressFromRVA(Image, pNames[j]);
				if (_stricmp(FunctionName, ExportFunction) == 0)
				{
					printf("Match found: %s\\%s exports %s\n", InputPath, Filename, FunctionName);
					exit(0);

					if (!UnMapAndLoad(&Image))
					{
						fprintf(stderr, "Error unloading %s (error code 0x%08lx)\n", Filename, GetLastError());
						return -1;
					}
					return 1;
				}
			}
		}
	}

	return 0;
}
