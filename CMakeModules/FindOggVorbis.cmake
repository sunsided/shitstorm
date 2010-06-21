# Locate Ogg/Vorbis
# This module defines
# OGG_LIBRARY
# VORBIS_LIBRARY
# OGG_FOUND, if false, do not try to link to Ogg
# VORBIS_FOUND, if false, do not try to link to Vorbis
# OGG_INCLUDE_DIR, where to find the headers
# VORBIS_INCLUDE_DIR, where to find the headers
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


FIND_PATH(OGG_INCLUDE_DIR ogg.h
  HINTS
  $ENV{OGGDIR}
  PATH_SUFFIXES include/ogg include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_PATH(VORBIS_INCLUDE_DIR vorbisfile.h
  HINTS
  $ENV{VORBISDIR}
  PATH_SUFFIXES include/vorbis include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(OGG_LIBRARY 
  NAMES libogg ogg
  HINTS
  $ENV{OGGDIR}
  PATH_SUFFIXES bin lib64 lib libs64 libs libs/Win32 libs/Win64 lib64/Linux lib/Linux libs64/Linux libs/Linux
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

FIND_LIBRARY(VORBIS_LIBRARY 
  NAMES libvorbis vorbis
  HINTS
  $ENV{OGGDIR}
  PATH_SUFFIXES bin lib64 lib libs64 libs libs/Win32 libs/Win64 lib64/Linux lib/Linux libs64/Linux libs/Linux
  PATHS
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

