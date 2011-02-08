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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/nbody/direct/direct.o \
	${OBJECTDIR}/src/options.o \
	${OBJECTDIR}/src/nbody.o \
	${OBJECTDIR}/src/nbody/barneshut/barneshut.o \
	${OBJECTDIR}/src/io/vtk/vtk.o \
	${OBJECTDIR}/src/nbody/fmm/fmm.o \
	${OBJECTDIR}/src/particle.o \
	${OBJECTDIR}/src/utils/util.o \
	${OBJECTDIR}/src/nbody/barneshut/treecode.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/MinGW-Windows/nbodyc.exe

dist/Debug/MinGW-Windows/nbodyc.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/MinGW-Windows
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbodyc ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/nbody/direct/direct.o: src/nbody/direct/direct.c 
	${MKDIR} -p ${OBJECTDIR}/src/nbody/direct
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/nbody/direct/direct.o src/nbody/direct/direct.c

${OBJECTDIR}/src/options.o: src/options.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/options.o src/options.c

${OBJECTDIR}/src/nbody.o: src/nbody.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/nbody.o src/nbody.c

${OBJECTDIR}/src/nbody/barneshut/barneshut.o: src/nbody/barneshut/barneshut.c 
	${MKDIR} -p ${OBJECTDIR}/src/nbody/barneshut
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/nbody/barneshut/barneshut.o src/nbody/barneshut/barneshut.c

${OBJECTDIR}/src/io/vtk/vtk.o: src/io/vtk/vtk.c 
	${MKDIR} -p ${OBJECTDIR}/src/io/vtk
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/io/vtk/vtk.o src/io/vtk/vtk.c

${OBJECTDIR}/src/nbody/fmm/fmm.o: src/nbody/fmm/fmm.c 
	${MKDIR} -p ${OBJECTDIR}/src/nbody/fmm
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/nbody/fmm/fmm.o src/nbody/fmm/fmm.c

${OBJECTDIR}/src/particle.o: src/particle.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/particle.o src/particle.c

${OBJECTDIR}/src/utils/util.o: src/utils/util.c 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/utils/util.o src/utils/util.c

${OBJECTDIR}/src/nbody/barneshut/treecode.o: src/nbody/barneshut/treecode.c 
	${MKDIR} -p ${OBJECTDIR}/src/nbody/barneshut
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/nbody/barneshut/treecode.o src/nbody/barneshut/treecode.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/MinGW-Windows/nbodyc.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
