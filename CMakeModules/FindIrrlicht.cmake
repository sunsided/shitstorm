# Locate Irrlicht
# This module defines
# IRRLICHT_LIBRARY
# IRRLICHT_FOUND, if false, do not try to link to Irrlicht
# IRRLICHT_INCLUDE_DIR, where to find the headers
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


FIND_PATH(IRRLICHT_INCLUDE_DIR irrlicht.h
  HINTS
  $ENV{IRRLICHTDIR}
  PATH_SUFFIXES include/Irrlicht include/irrlicht include
  PATHS
  ~/dev/lib/irrlicht
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(IRRLICHT_LIBRARY 
  NAMES libirrlicht libIrrlicht irrlicht Irrlicht
  HINTS
  $ENV{IRRLICHTDIR}
  PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64 lib64/Linux lib/Linux libs64/Linux libs/Linux
  PATHS
  ~/dev/lib/irrlicht
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

