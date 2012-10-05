#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/Selector.o \
	${OBJECTDIR}/src/gameobjects/Soldier.o \
	${OBJECTDIR}/src/tiles/Tile.o \
	${OBJECTDIR}/src/gameobjects/Tank.o \
	${OBJECTDIR}/src/tiles/TiledObjectLayer.o \
	${OBJECTDIR}/src/gameobjects/GameObject.o \
	${OBJECTDIR}/src/gameobjects/Water.o \
	${OBJECTDIR}/src/gameobjects/Ground.o \
	${OBJECTDIR}/src/gameobjects/Tree.o \
	${OBJECTDIR}/src/Pathfinding.o \
	${OBJECTDIR}/src/RtsCamera.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Werror -lglut -lGL -lGLU -lphantom -lpng15
CXXFLAGS=-Werror -lglut -lGL -lGLU -lphantom -lpng15

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../dist -Wl,-rpath,.

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../dist/guarrilla_tactics.run

../dist/guarrilla_tactics.run: ${OBJECTFILES}
	${MKDIR} -p ../dist
	${LINK.cc} -Werror -lphantom -lglut -o ../dist/guarrilla_tactics.run ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Game.o: src/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/Selector.o: src/Selector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Selector.o src/Selector.cpp

${OBJECTDIR}/src/gameobjects/Soldier.o: src/gameobjects/Soldier.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Soldier.o src/gameobjects/Soldier.cpp

${OBJECTDIR}/src/tiles/Tile.o: src/tiles/Tile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tiles
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tiles/Tile.o src/tiles/Tile.cpp

${OBJECTDIR}/src/gameobjects/Tank.o: src/gameobjects/Tank.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Tank.o src/gameobjects/Tank.cpp

${OBJECTDIR}/src/tiles/TiledObjectLayer.o: src/tiles/TiledObjectLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tiles
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tiles/TiledObjectLayer.o src/tiles/TiledObjectLayer.cpp

${OBJECTDIR}/src/gameobjects/GameObject.o: src/gameobjects/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/GameObject.o src/gameobjects/GameObject.cpp

${OBJECTDIR}/src/gameobjects/Water.o: src/gameobjects/Water.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Water.o src/gameobjects/Water.cpp

${OBJECTDIR}/src/gameobjects/Ground.o: src/gameobjects/Ground.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Ground.o src/gameobjects/Ground.cpp

${OBJECTDIR}/src/gameobjects/Tree.o: src/gameobjects/Tree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gameobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gameobjects/Tree.o src/gameobjects/Tree.cpp

${OBJECTDIR}/src/Pathfinding.o: src/Pathfinding.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Pathfinding.o src/Pathfinding.cpp

${OBJECTDIR}/src/RtsCamera.o: src/RtsCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Werror -I/usr/local/include -I../phantom/src -I../phantom/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RtsCamera.o src/RtsCamera.cpp

# Subprojects
.build-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../dist/guarrilla_tactics.run

# Subprojects
.clean-subprojects:
	cd ../phantom && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
