// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// 동영상
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

// 사운드
#include <io.h>
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>
using namespace std;
#include <time.h>

// TODO: reference additional headers your program requires here
#include "Extern.h"
#include "Define.h"
#include "Typedef.h"
#include "Struct.h"
#include "Enum.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Function.h"
