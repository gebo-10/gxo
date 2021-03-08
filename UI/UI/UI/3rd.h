#pragma once

#include <GLFW/glfw3.h>
#pragma comment(lib, "glfw3.lib")
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
//#include "terra/terra.h"
}

//#pragma comment(lib, "lua51.lib")
//#pragma comment(lib, "terra.lib")
//#define SOL_USING_CXX_LUA_JIT 1
#define SOL_NO_EXCEPTIONS 1
//#define SOL_ALL_SAFETIES_ON 1
#include "forward.hpp"
#include "sol.hpp"

// /D "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"
extern "C" int luaopen_skia(lua_State * L);

#define SK_GL
#include "include/skia.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#include "include/utils/SkLua.h"

#pragma comment(lib, "skshaper.lib")
#pragma comment(lib, "skia.lib")

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32s.lib")