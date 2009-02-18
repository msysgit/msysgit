#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "directory.h"

#define MAX_WILDCARDS 10

// Internal functions only
BOOL AddFileToSearchResult(PDIRECTORY_INFO pDirectory, char *BasePathName, char *Filename);
BOOL MergeSearchResults(PDIRECTORY_INFO pBaseDir, PDIRECTORY_INFO pSubDir);
BOOL MergeSearchResultsAndClose(PDIRECTORY_INFO pBaseDir, PDIRECTORY_INFO pSubDir);
PSEARCH_RESULTS GetLastSearchResult(PSEARCH_RESULTS pSearchResult);
DWORD GetSearchResultCount(PSEARCH_RESULTS pSearchResult);
void DumpSearchResults(PSEARCH_RESULTS pSearchResults);

BOOL IsSameExtension(char *Extension1, char *Extension2)
{
	if (_stricmp(Extension1, Extension2) == 0) return TRUE;
	else return FALSE;
}

void PrintWildcardError()
{
	fprintf(stderr, "Error: invalid wildcards for filename\n"
		"Wildcards can be:\n"
		"\tfilename      match \"filename\"\n"
		"\tfilename.ext  match \"filename.ext\"\n"
		"\t*             match all files (with or without extensions)\n"
		"\t*.*           match all files with extensions\n"
		"\t*.            match all files without extensions\n"
		"\t*.ext         match all files ending in \".ext\"\n"
		"\t*.ext1;*.ext2 match all files ending in \".ext1\" or \".ext2\"\n");
}

PDIRECTORY_INFO DirectoryOpen(char *Directory, BOOL RecurseSubDirs)
{
	PDIRECTORY_INFO pDirectory;
	char tmpdir[MAX_PATH+1];

	if (!Directory) return NULL;
	//printf("Opening directory %s (RecurseSubDirs = %d)\n", Directory, RecurseSubDirs);

	pDirectory = (PDIRECTORY_INFO)malloc(sizeof(DIRECTORY_INFO));
	if (!pDirectory)
	{
		fprintf(stderr, "Unable to allocate %d bytes\n", sizeof(DIRECTORY_INFO));
		return NULL;
	}

	_snprintf(tmpdir, sizeof(tmpdir), "%s\\*", Directory);
	pDirectory->hFileList = FindFirstFile(tmpdir, &pDirectory->BasePath);
	if (pDirectory->hFileList == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Invalid path \"%s\"\n", Directory);
		return NULL;
	}

	pDirectory->Initialized = TRUE;
	pDirectory->Finished = FALSE;
	pDirectory->RecurseSubDirs = RecurseSubDirs;
	pDirectory->pSearchResults = NULL;
	
	_snprintf(pDirectory->BasePathName, sizeof(pDirectory->BasePathName), "%s", Directory);
	return pDirectory;
}

void DirectoryClose(PDIRECTORY_INFO pDirectory)
{
	PSEARCH_RESULTS pLast;

	if (!pDirectory || !pDirectory->Initialized) return;
	//printf("Closing %s\n", pDirectory->BasePathName);

	// Free the search results, if any
	if (pDirectory->pSearchResults)
	{
		assert(pDirectory->pSearchResults->Previous == NULL);

		pLast = GetLastSearchResult(pDirectory->pSearchResults);
		assert(pLast);
		while (pLast->Previous)
		{
			assert(pLast->FilePath);
			if (pLast->FilePath)
			{
				//printf("Deallocating entry for %s\n", pLast->FilePath);
				free(pLast->FilePath);
				pLast->FilePath = NULL;
			}
			pLast = pLast->Previous;
			free(pLast->Next);
			pLast->Next = NULL;
		}

		assert(pDirectory->pSearchResults == pLast);	
		assert(pDirectory->pSearchResults->FilePath);

		if (pDirectory->pSearchResults->FilePath)
		{
			//printf("Deallocating entry for %s\n", pDirectory->pSearchResults->FilePath);
			free(pDirectory->pSearchResults->FilePath);
			pDirectory->pSearchResults->FilePath = NULL;
		}

		pDirectory->pSearchResults->Next = NULL;
		free(pDirectory->pSearchResults);
		pDirectory->pSearchResults = NULL;
	}
	
	FindClose(pDirectory->hFileList);
	pDirectory->Initialized = FALSE;
	free(pDirectory);
}

// This will match all files in a directory (or subdirectories if recursion is enabled)
// Currently, this will not match any directories or specific filenames
// Must use "*", "*.ext", or "*.ext1;*.ext2"
// This is definitely not efficient and may crash when dealing with very deep levels
BOOL DirectorySearch(PDIRECTORY_INFO pDirectory, char *FileWildcard)
{
	int i, WildcardCount = 0;
    BOOL IsDirectory;	
	BOOL RecurseSubDirs, MatchAllFiles = FALSE;
	char tmpSubDir[MAX_PATH+1];
	char *tmpWildcard, *Wildcard, *Wildcards[MAX_WILDCARDS];
	char *BasePathName, *Filename, *FileExtension, *tmpFileExtension;
	PDIRECTORY_INFO pNewDirectory;

	if (!pDirectory || !pDirectory->Initialized || pDirectory->Finished) return FALSE;

	//////////////////////////////////////////////////////////////
	// Setup wildcards

	if (!FileWildcard)
	{
		MatchAllFiles = TRUE;
	}
	else if (!FileWildcard[0] || strchr(FileWildcard, ','))
	{
		PrintWildcardError();
		return FALSE;
	}
	else
	{
		if (!(tmpWildcard = Wildcard = strdup(FileWildcard)))
		{
			fprintf(stderr, "Error allocating %d bytes\n", strlen(FileWildcard)+1);
			return FALSE;
		}

		while (*tmpWildcard && (tmpFileExtension = strchr(tmpWildcard, ';')))
		{
			*tmpFileExtension++ = '\0';
			if (WildcardCount == MAX_WILDCARDS - 1)	return FALSE;

			if (tmpWildcard[0] == '*' && !tmpWildcard[1])
			{
				MatchAllFiles = TRUE;
				break;
			}
			else
			{
				if (tmpWildcard[0] == '*' && tmpWildcard[1] != '.')
				{
					PrintWildcardError();
					return FALSE;
				}

				Wildcards[WildcardCount++] = strdup(tmpWildcard);
				tmpWildcard = tmpFileExtension;
			}
		}

		if (MatchAllFiles || (tmpWildcard[0] == '*' && !tmpWildcard[1]))
		{
			MatchAllFiles = TRUE;
			for (i = 0; i < WildcardCount; i++) free(Wildcards[i]);
			WildcardCount = 0;
		}
		else if (*tmpWildcard)
		{
			Wildcards[WildcardCount++] = strdup(tmpWildcard);
			free(Wildcard);
		}
	}

	//////////////////////////////////////////////////////////////
	// Iterate through subdirectories

	RecurseSubDirs = pDirectory->RecurseSubDirs;
	BasePathName = pDirectory->BasePathName;
	Filename = pDirectory->BasePath.cFileName;

	//printf("=== Searching in %s (RecurseSubDirs = %d)\n", BasePathName, RecurseSubDirs);
	while (TRUE)
	{
		IsDirectory = pDirectory->BasePath.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		FileExtension = strrchr(Filename, '.');
	
		// Match if the currently found item is a subdirectory and recursion is enabled
		if (IsDirectory && RecurseSubDirs && *Filename != '.')
		{
			_snprintf(tmpSubDir, sizeof(tmpSubDir), "%s\\%s", BasePathName, Filename);
			if (!(pNewDirectory = DirectoryOpen(tmpSubDir, TRUE))) return FALSE;
			if (!(DirectorySearch(pNewDirectory, FileWildcard))) return FALSE;
			if (!MergeSearchResults(pDirectory, pNewDirectory)) return FALSE;
			DirectoryClose(pNewDirectory);
		}

		// Try to match the current file to a wildcard or filename
		else if (!IsDirectory)
		{
			//printf("Found %s\\%s\n", BasePathName, Filename);

			if (MatchAllFiles)
			{
				if (!AddFileToSearchResult(pDirectory, BasePathName, Filename)) return FALSE;
			}
			else if (FileExtension)
			{
				FileExtension++; // point to one byte past "." (the file extension)
				for (i = 0; i < WildcardCount; i++)
				{
					if (Wildcards[i][0] == '*')
					{
						if (!Wildcards[i][1] || Wildcards[i][2] == '*')
						{
							if (!AddFileToSearchResult(pDirectory, BasePathName, Filename)) return FALSE;
							break;
						}
						else if (Wildcards[i][2] && IsSameExtension(FileExtension, Wildcards[i] + 2)) 
						{
							if (!AddFileToSearchResult(pDirectory, BasePathName, Filename)) return FALSE;
							break;
						}
					}
					else if (IsSameExtension(Filename, Wildcards[i]))
					{
						if (!AddFileToSearchResult(pDirectory, BasePathName, Filename)) return FALSE;
						break;
					}
				}
			}
			else
			{ 
				for (i = 0; i < WildcardCount; i++)
				{
					if (Wildcards[i][0] == '*' && Wildcards[i][1] == '.' &&	!Wildcards[i][2])
					{
						if (!AddFileToSearchResult(pDirectory, BasePathName, Filename)) return FALSE;
						break;
					}
					else if (IsSameExtension(Filename, Wildcards[i])) // match file
					{
						if (!AddFileToSearchResult(pDirectory, BasePathName, Filename)) return FALSE;
						break;
					}

				}
			}
		}

		if (!FindNextFile(pDirectory->hFileList, &pDirectory->BasePath))
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) break;
			fprintf(stderr, "FindNextFile failed: error code 0x%08lx\n", GetLastError());
			return FALSE;
		}
    }

	pDirectory->Finished = TRUE;
	return TRUE;
}

PSEARCH_RESULTS GetLastSearchResult(PSEARCH_RESULTS pSearchResult)
{
	while (pSearchResult && pSearchResult->Next) pSearchResult = pSearchResult->Next;
	return pSearchResult;
}

BOOL AddFileToSearchResult(PDIRECTORY_INFO pDirectory, char *BasePathName, char *Filename)
{
	DWORD PathLength;
	PSEARCH_RESULTS pSearchResults;

	////////////////////////////////////////////////////////////////
	// Allocate a new search result set or append to an existing one

	if (!pDirectory->pSearchResults)
	{
		pSearchResults = pDirectory->pSearchResults = malloc(sizeof(SEARCH_RESULTS));
		if (!pSearchResults)
		{
			fprintf(stderr, "Error allocating %d bytes\n", sizeof(SEARCH_RESULTS));
			return FALSE;
		}

		pSearchResults->Previous = NULL;
	}
	else // an existing entry
	{
		pSearchResults = GetLastSearchResult(pDirectory->pSearchResults);
		if (!(pSearchResults->Next = malloc(sizeof(SEARCH_RESULTS))))
		{
			fprintf(stderr, "Error: unable to allocate %d bytes\n", sizeof(SEARCH_RESULTS));
			return FALSE;
		}
		pSearchResults->Next->Previous = pSearchResults;
		pSearchResults = pSearchResults->Next;
	}

	pSearchResults->Next = NULL;

	////////////////////////////////////////////////////////////////
	// Save path to filename for the search result

	PathLength = strlen(pDirectory->BasePathName) + strlen(Filename) + 2;
	if (PathLength > MAX_PATH)
	{
		fprintf(stderr, "Error: File path is too large\n");
		return FALSE;
	}

	if (!(pSearchResults->FilePath = (char *)malloc(PathLength)))
	{
		fprintf(stderr, "Error: unable to allocate %d bytes\n", PathLength);
		return FALSE;
	}

	sprintf(pSearchResults->FilePath, "%s\\%s", BasePathName, Filename);
	//printf("Added %s\n", pSearchResults->FilePath);
	return TRUE;
}

BOOL MergeSearchResults(PDIRECTORY_INFO pBaseDir, PDIRECTORY_INFO pSubDir)
{
	DWORD PathLength;
	PSEARCH_RESULTS pDestination, pSource;

	if (!pBaseDir || !pSubDir) return FALSE;	
	pSource = pSubDir->pSearchResults;
	if (!pSource) return TRUE; // subdirectory is empty (don't merge)
	assert(pSource->Previous == NULL);

	if (!pBaseDir->pSearchResults) // merge subdirectory into empty result set
	{
		pDestination = pBaseDir->pSearchResults = malloc(sizeof(SEARCH_RESULTS));
		if (!pDestination)
		{
			fprintf(stderr, "Error allocating %d bytes\n", sizeof(SEARCH_RESULTS));
			return FALSE;
		}

		pDestination->Previous = NULL;
		pDestination->Next = NULL;
	}
	else // merge subdirectory with an existing result set
	{
		assert(pBaseDir->pSearchResults->Previous == NULL);
		pDestination = GetLastSearchResult(pBaseDir->pSearchResults);
		pDestination->Next = malloc(sizeof(SEARCH_RESULTS));
		if (!pDestination->Next)
		{
			fprintf(stderr, "Error: unable to allocate %d bytes\n", sizeof(SEARCH_RESULTS));
			return FALSE;
		}

		pDestination->Next->Previous = pDestination;
		pDestination = pDestination->Next;
		pDestination->Next = NULL;
	}

	while (TRUE)
	{
		assert(pSource->FilePath != NULL);
		PathLength = strlen(pSource->FilePath) + 1;
		if (!(pDestination->FilePath = (char *)malloc(PathLength)))
		{
			fprintf(stderr, "Error: unable to allocate %d bytes\n", PathLength);
			return FALSE;
		}

		strcpy(pDestination->FilePath, pSource->FilePath);
		//printf("Merged %s\n", pDestination->FilePath);

		pSource = pSource->Next;
		if (!pSource) break;

		pDestination->Next = malloc(sizeof(SEARCH_RESULTS));
		if (!pDestination->Next)
		{
			fprintf(stderr, "Error: unable to allocate %d bytes\n", sizeof(SEARCH_RESULTS));
			return FALSE;
		}

		pDestination->Next->Previous = pDestination;
		pDestination = pDestination->Next;
		pDestination->Next = NULL;
	}

	//printf("New base directory contains:\n");
	//DumpSearchResults(pSubDir->pSearchResults);
	return TRUE;
}

DWORD GetSearchResultCount(PSEARCH_RESULTS pSearchResult)
{
	DWORD Count = 0;

	if (!pSearchResult) return 0;
	while (pSearchResult && pSearchResult->Next)
	{
		pSearchResult = pSearchResult->Next;
		Count++;
	}

	return Count + 1;
}

void DumpSearchResults(PSEARCH_RESULTS pSearchResults)
{
	PSEARCH_RESULTS tmpResult;

	if (!pSearchResults) return;

	printf("Total records: %d\n", GetSearchResultCount(pSearchResults));
	for (tmpResult = pSearchResults; tmpResult; tmpResult = tmpResult->Next)
	{
		if (tmpResult->FilePath) printf("\t%s\n", tmpResult->FilePath);
	}
}