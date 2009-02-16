#include <stdio.h>
#include <shlobj.h>

void die(const char *message)
{
	CoUninitialize();
	fprintf(stderr, "%s\n", message);
	fprintf(stderr, "last error: %d\n", GetLastError());
	exit(1);
}

int main(int argc, char **argv)
{
	const char *progname = argv[0];
	const char *work_dir = NULL, *arguments = NULL, *icon_file = NULL;
	const char *description = NULL;
	int show_cmd = 1;

	static WCHAR wsz[1024];
	HRESULT hres;
	IShellLink* psl;
	IPersistFile* ppf;


	while (argc > 2) {
		if (argv[1][0] != '-')
			break;
		if (!strcmp(argv[1], "--work-dir"))
			work_dir = argv[2];
		else if (!strcmp(argv[1], "--arguments"))
			arguments = argv[2];
		else if (!strcmp(argv[1], "--show-cmd"))
			show_cmd = atoi(argv[2]);
		else if (!strcmp(argv[1], "--icon-file"))
			icon_file = argv[2];
		else if (!strcmp(argv[1], "--description"))
			description = argv[2];
		else {
			fprintf(stderr, "Unknown option: %s\n", argv[1]);
			return 1;
		}

		argc -= 2;
		argv += 2;
	}

	if (argc > 1 && !strcmp(argv[1], "--")) {
		argc--;
		argv++;
	}

	if (argc < 3) {
		fprintf(stderr, "Usage: %s [options] <source> <destination>\n",
			progname);
		return 1;
	}

	hres = CoInitialize(NULL);
	if (FAILED(hres))
		die ("Could not initialize OLE");

	hres = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
			&IID_IShellLink, (void **)&psl);

	if (FAILED(hres))
		die ("Could not get ShellLink interface");

	hres = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile,
			(void **) &ppf);

	if (FAILED(hres))
		die ("Could not get PersistFile interface");

	hres = psl->lpVtbl->SetPath(psl, argv[1]);
	if (FAILED(hres))
		die ("Could not set path");

	if (work_dir)
		psl->lpVtbl->SetWorkingDirectory(psl, work_dir);

	if (show_cmd)
		psl->lpVtbl->SetShowCmd(psl, show_cmd);

	if (icon_file)
		psl->lpVtbl->SetIconLocation(psl, icon_file, 0);
	if (arguments)
		psl->lpVtbl->SetArguments(psl, arguments);
	if (description)
		psl->lpVtbl->SetDescription(psl, description);

	wsz[0] = 0;
	MultiByteToWideChar(CP_ACP,
			0, argv[2], -1, wsz, 1024);
	hres = ppf->lpVtbl->Save(ppf,
			(const WCHAR*)wsz, TRUE);

	ppf->lpVtbl->Release(ppf);
	psl->lpVtbl->Release(psl);

	if (FAILED(hres))
		die ("Could not save link");

	CoUninitialize();
	return 0;
}
