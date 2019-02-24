#pragma once

// Macros set by CMake
#cmakedefine PLATFORM_WINDOWS @PLATFORM_WINDOWS@
#cmakedefine PLATFORM_LINUX @PLATFORM_LINUX@
#cmakedefine PLATFORM_GNU @PLATFORM_GNU@
#cmakedefine PLATFORM_MACOSX @PLATFORM_MACOSX@
#cmakedefine PLATFORM_OTHER @PLATFORM_OTHER@

#ifdef PLATFORM_MACOSX
// Assume we have the Mac OS X function CFLocaleCopyCurrent in the CoreFoundation framework
#define HAVE_CFLOCALECOPYCURRENT 1
#endif

#cmakedefine GLEW_STATIC

#cmakedefine OPENAL_SOUND

#cmakedefine PORTABLE_SAVES @PORTABLE_SAVES@

#define COLOBOT_DEFAULT_DATADIR "@COLOBOT_RELATIVE_DATA_DIR@"
#define COLOBOT_I18N_DIR "@COLOBOT_RELATIVE_I18N_DIR@"
