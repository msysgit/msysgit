/*
       zmouse.h - Header for IntelliMouse.

       This file is part of a free library for the Win32 API.

       This library is distributed in the hope that it will be useful,
       but WITHOUT ANY WARRANTY; without even the implied warranty of
       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

       FIXME: This file is obviously horribly incomplete!

*/

#ifndef _ZMOUSE_H
#define _ZMOUSE_H

#ifndef WM_MOUSEWHEEL
# define WM_MOUSEWHEEL (WM_MOUSELAST + 1)
#endif

#define WHEEL_DELTA 120
#define WHEEL_PAGESCROLL UINT_MAX

#endif /* _ZMOUSE_H */
