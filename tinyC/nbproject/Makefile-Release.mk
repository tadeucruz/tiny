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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran

# Macros
PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ComandoWriteln.o \
	${OBJECTDIR}/src/Comandoread.o \
	${OBJECTDIR}/src/ArquivoFonte.o \
	${OBJECTDIR}/src/Interpretador.o \
	${OBJECTDIR}/src/ComandoEndp.o \
	${OBJECTDIR}/src/ComandoWrite.o \
	${OBJECTDIR}/src/ComandoAtrib.o \
	${OBJECTDIR}/src/Comando.o \
	${OBJECTDIR}/src/ExpVariavel.o \
	${OBJECTDIR}/src/ComandoFor.o \
	${OBJECTDIR}/src/Memoria.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/ComandoWhile.o \
	${OBJECTDIR}/src/ComandoIf.o \
	${OBJECTDIR}/src/ExpConstante.o \
	${OBJECTDIR}/src/ExpBinaria.o \
	${OBJECTDIR}/src/ComandowriteVar.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/tinyc

dist/Release/${PLATFORM}/tinyc: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -o dist/Release/${PLATFORM}/tinyc ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ComandoWriteln.o: src/ComandoWriteln.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandoWriteln.o src/ComandoWriteln.cpp

${OBJECTDIR}/src/Comandoread.o: src/Comandoread.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Comandoread.o src/Comandoread.cpp

${OBJECTDIR}/src/ArquivoFonte.o: src/ArquivoFonte.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ArquivoFonte.o src/ArquivoFonte.cpp

${OBJECTDIR}/src/Interpretador.o: src/Interpretador.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Interpretador.o src/Interpretador.cpp

${OBJECTDIR}/src/ComandoEndp.o: src/ComandoEndp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandoEndp.o src/ComandoEndp.cpp

${OBJECTDIR}/src/ComandoWrite.o: src/ComandoWrite.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandoWrite.o src/ComandoWrite.cpp

${OBJECTDIR}/src/ComandoAtrib.o: src/ComandoAtrib.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandoAtrib.o src/ComandoAtrib.cpp

${OBJECTDIR}/src/Comando.o: src/Comando.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Comando.o src/Comando.cpp

${OBJECTDIR}/src/ExpVariavel.o: src/ExpVariavel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ExpVariavel.o src/ExpVariavel.cpp

${OBJECTDIR}/src/ComandoFor.o: src/ComandoFor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandoFor.o src/ComandoFor.cpp

${OBJECTDIR}/src/Memoria.o: src/Memoria.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Memoria.o src/Memoria.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/ComandoWhile.o: src/ComandoWhile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandoWhile.o src/ComandoWhile.cpp

${OBJECTDIR}/src/ComandoIf.o: src/ComandoIf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandoIf.o src/ComandoIf.cpp

${OBJECTDIR}/src/ExpConstante.o: src/ExpConstante.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ExpConstante.o src/ExpConstante.cpp

${OBJECTDIR}/src/ExpBinaria.o: src/ExpBinaria.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ExpBinaria.o src/ExpBinaria.cpp

${OBJECTDIR}/src/ComandowriteVar.o: src/ComandowriteVar.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ComandowriteVar.o src/ComandowriteVar.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/tinyc

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
