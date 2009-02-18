#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef struct _DIRECTORY_INFO {
	HANDLE hFileList;
	BOOL Initialized;
	BOOL Finished;
	BOOL RecurseSubDirs;
	char BasePathName[MAX_PATH+1];
	WIN32_FIND_DATA BasePath; // do not reference this
	struct _SEARCH_RESULTS *pSearchResults; // use this!
} DIRECTORY_INFO, *PDIRECTORY_INFO;

typedef struct _SEARCH_RESULTS {
	 struct _SEARCH_RESULTS *Previous, *Next;
	 char *FilePath;
} SEARCH_RESULTS, *PSEARCH_RESULTS;

PDIRECTORY_INFO DirectoryOpen(char *Directory, BOOL RecurseSubDirs);
BOOL DirectorySearch(PDIRECTORY_INFO pDirectory, char *FileWildcard);
void DirectoryClose(PDIRECTORY_INFO pDirectory);

#endif // DIRECTORY_H
