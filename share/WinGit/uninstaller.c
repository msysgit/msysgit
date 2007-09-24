/*
 * Since Windows has problems deleting files that are in use, we cannot
 * have a Tcl/Tk based uninstaller, which would have been easy.
 *
 * Instead, we use a dirt simple C program using the Win32 API.  It is so
 * simple and small that you have to wonder why other Windows programs
 * have to be so large.
 *
 * Use like this:
 *
 * - create a directory (preferably in %%TEMP%%),
 * - copy this installer there,
 * - output a list of to-be-removed files into fileList.txt in that,
 *   directory, one file per line, absolute paths only,
 * - output a list of to-be-removed registry keys into registryKeys.txt
 *   in that directory, one key per line
 *
 * By executing the uninstaller, the files and the registry keys are
 * removed, and the removal of the directory is scheduled.
 *
 * (C) 2007 Johannes E. Schindelin
 * Distributed under the GPL v2.  And no, that means you are not allowed
 * to use/redistribute if you do not know what the GPL is... D'oh!
 */

#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

static const char *class_name = "GitUninstallerClass";
static HWND progress, label;
static int label_printf(const char *format, ...);

static int die(const char *format, ...)
{
	char buffer[16384];
	va_list args;
	int result;

	va_start(args, format);
	result = vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	if (result >= 0)
		MessageBox(NULL, buffer, "Error!", MB_OK);

	exit(1);
}

/* reading a list from a file */

struct list {
	char *buffer, **list;
	int count;
} files, registry_keys;

static inline int is_eol(char c)
{
	return c == '\r' || c == '\n' || c == '\0';
}

static int read_list(const char *file_name, struct list *list)
{
	int fd = open(file_name, O_RDONLY | O_BINARY), i;
	struct stat st;

	if (list->buffer) {
		free(list->buffer);
		list->buffer = NULL;
		list->list = NULL;
		list->count = 0;
	}

	if (fd < 0)
		return -1;

	if (fstat(fd, &st) < 0)
		return -1;

	list->buffer = malloc(st.st_size + 1);
	for (i = 0; i < st.st_size; ) {
		int result = read(fd, list->buffer + i, st.st_size - i);

		/* short read? */
		if (result <= 0)
			die ("Short read: %s", strerror(errno));
		i += result;
	}
	list->buffer[i] = '\0';
	close(fd);

	/* no need to be careful here... just overshoot */
	list->list = malloc(st.st_size / 2 * sizeof(char *));
	list->list[0] = list->buffer;
	if (list->buffer[0]) {
		for (list->count = 1, i = 0; i < st.st_size; i++)
			if (is_eol(list->buffer[i])) {
				char next = list->buffer[i + 1];
				if (next && !is_eol(next))
					list->list[list->count++]
						= list->buffer + i + 1;
				list->buffer[i] = '\0';
			}
	} else
		list->count = 0;

	return 0;
}

/* path stuff */

static int is_path_delimiter(char c)
{
	return c == '/' || c == '\\';
}

/* get a file in the same directory as this .exe; argv0 must be absolute */
const char *get_aux_file_path(const char *argv0, const char *basename)
{
	static char buffer[1024];
	int len1 = strlen(argv0), len2 = basename ? strlen(basename) : 0;

	while (len1 && !is_path_delimiter(argv0[len1 - 1]))
		len1--;

	if (len1 + len2 >= sizeof(buffer))
		exit(1);

	if (basename) {
		memcpy(buffer, argv0, len1);
		strcpy(buffer + len1, basename);
	} else
		buffer[len1 - 1] = '\0';

	return buffer;
}

/* registry stuff */

struct { const char* str; HKEY hkey; } root_keys[]={
	{ "HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE },
	{ "HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT },
	{ "HKEY_CURRENT_USER", HKEY_CURRENT_USER },
	{ "HKEY_USERS", HKEY_USERS },
	{ 0,0 }
};

void get_root_key(char** key_pointer, HKEY* root_pointer, int* index_pointer)
{
	int i;

	for (i = 0; root_keys[i].str; i++)
                if (!strncasecmp(*key_pointer, root_keys[i].str,
				strlen(root_keys[i].str))) {
                        *key_pointer += strlen(root_keys[i].str);
                        *root_pointer = root_keys[i].hkey;
                        if (**key_pointer == '\\')
                                (*key_pointer)++;
			break;
                }
	if(index_pointer)
		*index_pointer = i;
}

/*
 * If value == NULL, delete the whole key.
 * If component == NULL, remove the value,
 * otherwise remove only this substring from the value */

static int delete_from_registry(char *key,
	const char *value, const char *substring)
{
	char* slash = strrchr(key, '\\');
	LPCTSTR sub_key = NULL;
	HKEY root_key_handle, key_handle;
	LONG result;

	if (slash) {
		sub_key = slash + 1;
		*slash = '\0';
	}
	if (!sub_key || !sub_key[0])
		die ("Invalid registry key: %s", key);

	get_root_key(&key, &root_key_handle, NULL);
	result = RegOpenKeyEx(root_key_handle,
			key, 0, KEY_SET_VALUE, &key_handle);
	if (result != ERROR_SUCCESS)
		die ("Opening key %s returned 0x%lx!\n", key, result);

	if (value == NULL)
		result = SHDeleteKey(key_handle, sub_key);
	else if (substring == NULL) {
		HKEY sub_key_handle;

		result = RegOpenKey(key_handle, sub_key, &sub_key_handle);
		if (result != ERROR_SUCCESS)
			die ("Could not get sub key %s", sub_key);

		result = RegDeleteValue(sub_key_handle, value);
	} else {
		char buffer[16384];
		DWORD size = sizeof(buffer) - 1;
		int len = strlen(substring);
		char *match;
		HKEY sub_key_handle;

		result = RegOpenKey(key_handle, sub_key, &sub_key_handle);
		if (result != ERROR_SUCCESS)
			die ("Could not get sub key %s", sub_key);
		result = RegQueryValueEx(sub_key_handle, value, 0,
			NULL, (BYTE *)buffer, &size);
		if (result != ERROR_SUCCESS)
			die ("Cannot read value from %s %s", sub_key, value);

		/* actually remove the substring */
		buffer[size] = '\0';
		match = strstr(buffer, substring);
		if (!match)
			return 0;
		if (strlen(match) == len)
			*match = '\0';
		else
			memmove(match, match + len,
				size - (match + len - buffer));
		size -= len;

		result = RegSetValueEx(sub_key_handle, value, 0, REG_EXPAND_SZ,
			(BYTE *)buffer, size);
	}

	if (result != ERROR_SUCCESS) {
		char buffer[1024];
		die ("Deleting key %s:%s returned 0x%lx (%s)!\n",
			key, sub_key, result,
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_FROM_HMODULE,
				GetModuleHandle(NULL),
				GetLastError(), 0,
				buffer, sizeof(buffer), NULL));
	}

	return result;
}

/* remove an empty directory structure (no files, only directories) */

int remove_directory(const char *path)
{
	DIR *d;
	struct dirent *e;
	int result = 0;

	d = opendir(path);
	if (d == NULL)
		return 1;
	while ((e = readdir(d)))
		if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
			continue;
		else if (!strcmp(e->d_name, ".bash_history")) {
			char buffer[1024];
			if (snprintf(buffer, sizeof(buffer), "%s/%s", path,
						e->d_name) >= sizeof(buffer) ||
					unlink(buffer))
				result = 1;
		} else {
			char buffer[1024];
			if (snprintf(buffer, sizeof(buffer), "%s/%s",
					path, e->d_name) >= sizeof(buffer))
				result = 1;
			else if (remove_directory(buffer))
				result = 1;
		}

	if (result)
		return result;

	return rmdir(path);
}

/* the event handler */

static LRESULT CALLBACK window_proc(HWND handle,
	UINT message, WPARAM parameter, LPARAM parameter2)
{
	HFONT font;
	RECT rectangle;

	switch (message) {
		case WM_CLOSE:
			DestroyWindow(handle);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CREATE:
			progress = CreateWindowEx(0, PROGRESS_CLASS, NULL,
				WS_CHILD | WS_VISIBLE,
				0, 0, 500, 15, handle, (HMENU)NULL,
				GetModuleHandle(NULL), NULL);
			if(progress == NULL)
				MessageBox(handle,
					"Could not create progress bar.",
					"Error", MB_OK | MB_ICONERROR);

			label = CreateWindowEx(0, "STATIC", "Hello, World!",
				WS_CHILD | WS_VISIBLE,
				0, 15, 500, 20, handle, (HMENU)NULL,
				GetModuleHandle(NULL), NULL);
			if(label == NULL)
				MessageBox(handle,
					"Could not create label.",
					"Error", MB_OK | MB_ICONERROR);

			font = GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(label,
				WM_SETFONT, (WPARAM)font, MAKELPARAM(FALSE, 0));

			break;
		case WM_SIZE:
			GetClientRect(handle, &rectangle);
			SetWindowPos(progress, NULL, 0, 0,
				rectangle.right, 15,
				SWP_NOZORDER);
			SetWindowPos(label, NULL, 0, 15,
				rectangle.right, rectangle.bottom,
				SWP_NOZORDER);
			break;
		default:
			return DefWindowProc(handle,
				message, parameter, parameter2);
	}
	return 0;
}

/* print something into the label in the window */
static int label_printf(const char *format, ...)
{
	char buffer[16384];
	va_list args;
	int result;

	va_start(args, format);
	result = vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	if (result >= 0)
		SendMessage(label, WM_SETTEXT, 0, (LPARAM)buffer);

	return result;
}

/* the main loop */

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance,
		LPSTR command_line, int command_show)
{
	MSG message = { 0 };
	struct list install_location = { 0 };
	int i = 0, w = 240, h = 82;
	WNDCLASSEX wc;
	HWND handle;
	char argv0[1024];
	RECT rect;

	GetModuleFileName(instance, argv0, sizeof(argv0));

	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = window_proc;
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = class_name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
		die ("Could not register window class");

	/* Create the window */
	InitCommonControls();

	handle = GetDesktopWindow();
	if (GetWindowRect(handle, &rect)) {
		rect.left += (rect.right - rect.left - w) / 2;
		rect.top += (rect.bottom - rect.top - h) / 2;
	} else
		rect.left = rect.top = CW_USEDEFAULT;

	handle = CreateWindowEx(WS_EX_CLIENTEDGE, class_name,
		"WinGit uninstaller", WS_OVERLAPPEDWINDOW,
		rect.left, rect.top, w, h,
		NULL, NULL, instance, NULL);

	if (handle == NULL)
		die ("Could not get window handle");

	ShowWindow(handle, command_show);
	UpdateWindow(handle);

	/* ignore if there were no files installed */
	read_list(get_aux_file_path(argv0, "fileList.txt"), &files);

	SendMessage(progress, PBM_SETRANGE, 0, MAKELPARAM(0, files.count));

	/* remove the files */

	for (i = 0; i < files.count; i++) {
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		SendMessage(progress, PBM_SETPOS, i, 0);
		label_printf("%s", files.list[i]);
		if (unlink(files.list[i]))
			die ("Could not delete %s", files.list[i]);
	}

	/* try to remove the now-hopefully-empty directories */
	if (!read_list(get_aux_file_path(argv0, "installLocation.txt"),
			&install_location))
		for (i = 0; i < install_location.count; i++)
			if (remove_directory(install_location.list[i])) {
				char buffer[1024];
				snprintf(buffer, sizeof(buffer),
					"Could not remove %s "
					"(maybe not empty?)",
					install_location.list[i]);
				MessageBox(NULL, buffer, "Warning", MB_OK);
			}

	/* ignore if there were no registry keys installed */
	read_list(get_aux_file_path(argv0, "registryKeys.txt"), &registry_keys);

	/* remove the registry key(s) */

	for (i = 0; i < registry_keys.count; i++) {
		char *key = registry_keys.list[i];
		label_printf("%s", key);
		if (delete_from_registry(key, NULL, NULL))
			die ("Could not delete key %s", key);
	}

	if (!read_list(get_aux_file_path(argv0, "pathRegistryKey.txt"),
			&registry_keys) && registry_keys.count == 2) {
		delete_from_registry(registry_keys.list[0], "PATH",
			registry_keys.list[1]);
	}

	/*
	 * And now schedule the directory containing this uninstaller and
	 * the support files for removal.
	 */

	if (!MoveFileEx(get_aux_file_path(argv0, NULL), NULL,
			MOVEFILE_DELAY_UNTIL_REBOOT))
		die ("Could not schedule %s for removal",
			get_aux_file_path(argv0, NULL));

	return message.wParam;
}
