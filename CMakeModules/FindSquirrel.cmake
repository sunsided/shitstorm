# Locate SQUIRREL
# This module defines
# SQUIRREL_LIBRARY
# SQRAT_LIBRARY
# SQUIRREL_FOUND, if false, do not try to link to Squirrel 
# SQUIRREL_INCLUDE_DIR, where to find the headers
#
# Created by Markus Mayer. This was influenced by the FindOpenAL.cmake module.

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)


FIND_PATH(SQUIRREL_INCLUDE_DIR squirrel.h
  HINTS
  $ENV{SQUIRRELDIR}
  PATH_SUFFIXES include/SQUIRREL3 include/squirrel include
  PATHS
  ~/dev/lib/SQUIRREL3
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_PATH(SQRAT_INCLUDE_DIR sqrat.h
  HINTS
  $ENV{SQRATDIR}
  PATH_SUFFIXES include/sqrat include/Sqrat include
  PATHS
  ~/dev/lib/sqrat
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(SQUIRREL_LIBRARY 
  NAMES libsquirrelU squirrelU libsquirrel squirrel
  HINTS
  $ENV{SQUIRRELDIR}
  PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
  PATHS
  ~/dev/lib/SQUIRREL3
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

FIND_LIBRARY(SQUIRRELSTD_LIBRARY 
  NAMES libsqstdU libsqstdlibU sqstdlibU libsqstd libsqstdlib sqstdlib
  HINTS
  $ENV{SQUIRRELDIR}
  PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
  PATHS
  ~/dev/lib/SQUIRREL3
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)


SET(SQUIRREL_FOUND "NO")
IF(SQUIRREL_LIBRARY AND SQUIRREL_INCLUDE_DIR)
  SET(SQUIRREL_FOUND "YES")
ENDIF(SQUIRREL_LIBRARY AND SQUIRREL_INCLUDE_DIR)

