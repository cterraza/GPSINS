#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../I2C/I2C1.c ../I2C/I2CScript.c ../Uart/Uart1.c ../Send/Send.c ../Imu/Imu.c ../Main.c ../Receive/Receive.c ../Timer/Timer.c ../Uart/Uart2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360894859/I2C1.o ${OBJECTDIR}/_ext/1360894859/I2CScript.o ${OBJECTDIR}/_ext/761528099/Uart1.o ${OBJECTDIR}/_ext/761583977/Send.o ${OBJECTDIR}/_ext/1360896738/Imu.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1066438004/Receive.o ${OBJECTDIR}/_ext/2133224938/Timer.o ${OBJECTDIR}/_ext/761528099/Uart2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360894859/I2C1.o.d ${OBJECTDIR}/_ext/1360894859/I2CScript.o.d ${OBJECTDIR}/_ext/761528099/Uart1.o.d ${OBJECTDIR}/_ext/761583977/Send.o.d ${OBJECTDIR}/_ext/1360896738/Imu.o.d ${OBJECTDIR}/_ext/1472/Main.o.d ${OBJECTDIR}/_ext/1066438004/Receive.o.d ${OBJECTDIR}/_ext/2133224938/Timer.o.d ${OBJECTDIR}/_ext/761528099/Uart2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360894859/I2C1.o ${OBJECTDIR}/_ext/1360894859/I2CScript.o ${OBJECTDIR}/_ext/761528099/Uart1.o ${OBJECTDIR}/_ext/761583977/Send.o ${OBJECTDIR}/_ext/1360896738/Imu.o ${OBJECTDIR}/_ext/1472/Main.o ${OBJECTDIR}/_ext/1066438004/Receive.o ${OBJECTDIR}/_ext/2133224938/Timer.o ${OBJECTDIR}/_ext/761528099/Uart2.o

# Source Files
SOURCEFILES=../I2C/I2C1.c ../I2C/I2CScript.c ../Uart/Uart1.c ../Send/Send.c ../Imu/Imu.c ../Main.c ../Receive/Receive.c ../Timer/Timer.c ../Uart/Uart2.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512GM604
MP_LINKER_FILE_OPTION=,--script=p33EP512GM604.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360894859/I2C1.o: ../I2C/I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360894859" 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../I2C/I2C1.c  -o ${OBJECTDIR}/_ext/1360894859/I2C1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360894859/I2C1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360894859/I2C1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360894859/I2CScript.o: ../I2C/I2CScript.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360894859" 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2CScript.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2CScript.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../I2C/I2CScript.c  -o ${OBJECTDIR}/_ext/1360894859/I2CScript.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360894859/I2CScript.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360894859/I2CScript.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761528099/Uart1.o: ../Uart/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761528099" 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart/Uart1.c  -o ${OBJECTDIR}/_ext/761528099/Uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761583977/Send.o: ../Send/Send.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761583977" 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o.d 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Send/Send.c  -o ${OBJECTDIR}/_ext/761583977/Send.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761583977/Send.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761583977/Send.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360896738/Imu.o: ../Imu/Imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360896738" 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Imu/Imu.c  -o ${OBJECTDIR}/_ext/1360896738/Imu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360896738/Imu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360896738/Imu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Main.c  -o ${OBJECTDIR}/_ext/1472/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1066438004/Receive.o: ../Receive/Receive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1066438004" 
	@${RM} ${OBJECTDIR}/_ext/1066438004/Receive.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066438004/Receive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Receive/Receive.c  -o ${OBJECTDIR}/_ext/1066438004/Receive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1066438004/Receive.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1066438004/Receive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2133224938/Timer.o: ../Timer/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2133224938" 
	@${RM} ${OBJECTDIR}/_ext/2133224938/Timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/2133224938/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Timer/Timer.c  -o ${OBJECTDIR}/_ext/2133224938/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2133224938/Timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2133224938/Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761528099/Uart2.o: ../Uart/Uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761528099" 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart/Uart2.c  -o ${OBJECTDIR}/_ext/761528099/Uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1360894859/I2C1.o: ../I2C/I2C1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360894859" 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2C1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../I2C/I2C1.c  -o ${OBJECTDIR}/_ext/1360894859/I2C1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360894859/I2C1.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360894859/I2C1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360894859/I2CScript.o: ../I2C/I2CScript.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360894859" 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2CScript.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360894859/I2CScript.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../I2C/I2CScript.c  -o ${OBJECTDIR}/_ext/1360894859/I2CScript.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360894859/I2CScript.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360894859/I2CScript.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761528099/Uart1.o: ../Uart/Uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761528099" 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart/Uart1.c  -o ${OBJECTDIR}/_ext/761528099/Uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart1.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761583977/Send.o: ../Send/Send.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761583977" 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o.d 
	@${RM} ${OBJECTDIR}/_ext/761583977/Send.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Send/Send.c  -o ${OBJECTDIR}/_ext/761583977/Send.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761583977/Send.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761583977/Send.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1360896738/Imu.o: ../Imu/Imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360896738" 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360896738/Imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Imu/Imu.c  -o ${OBJECTDIR}/_ext/1360896738/Imu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360896738/Imu.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360896738/Imu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/Main.o: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Main.c  -o ${OBJECTDIR}/_ext/1472/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/Main.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1066438004/Receive.o: ../Receive/Receive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1066438004" 
	@${RM} ${OBJECTDIR}/_ext/1066438004/Receive.o.d 
	@${RM} ${OBJECTDIR}/_ext/1066438004/Receive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Receive/Receive.c  -o ${OBJECTDIR}/_ext/1066438004/Receive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1066438004/Receive.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1066438004/Receive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2133224938/Timer.o: ../Timer/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2133224938" 
	@${RM} ${OBJECTDIR}/_ext/2133224938/Timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/2133224938/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Timer/Timer.c  -o ${OBJECTDIR}/_ext/2133224938/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2133224938/Timer.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2133224938/Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761528099/Uart2.o: ../Uart/Uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761528099" 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/761528099/Uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Uart/Uart2.c  -o ${OBJECTDIR}/_ext/761528099/Uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761528099/Uart2.o.d"      -mno-eds-warn  -g -omf=elf -O1 -I"../" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761528099/Uart2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
