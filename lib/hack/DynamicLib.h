/*
 * DynamicLib.h
 *
 *  Created on: 2014/11/18
 *      Author: nakatani.sho
 */

#ifndef LIB_HACK_DYNAMICLIB_H_
#define LIB_HACK_DYNAMICLIB_H_

#include "api/SmartdbType.h"

#ifdef _WIN32
static const char *dlerror(void)
{
  static char buf[32];
  DWORD dw = GetLastError();
  if (dw == 0)
    return NULL;
  sprintf(buf, "error 0x%x", (unsigned int)dw);
  return buf;
}
#endif //_WIN32

namespace Smartdb {

lib_t load_dlib(const char* dlib_path) {
#ifdef _WIN32
  return ::LoadLibraryA(dlib_path);
#else //_WIN32
  return ::dlopen(dlib_path, RTLD_LAZY);
#endif //_WIN32
}

int unload_dlib(lib_t lib_handler) {
#ifdef _WIN32
  return ::FreeLibrary(lib_handler);
#else //_WIN32
  return ::dlclose(lib_handler);
#endif //_WIN32
}

void* load_func(lib_t lib_handler, const char* func_name) {
#ifdef _WIN32
  return ::GetProcAddress(lib_handler, func_name);
#else //_WIN32
  return ::dlsym(lib_handler, func_name);
#endif //_WIN32
}

}

#endif /* LIB_HACK_DYNAMICLIB_H_ */
