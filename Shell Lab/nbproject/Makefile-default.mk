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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/17176491/heap_2.o ${OBJECTDIR}/_ext/1481540018/list.o ${OBJECTDIR}/_ext/1642425384/port.o ${OBJECTDIR}/_ext/1642425384/port_asm.o ${OBJECTDIR}/_ext/1481540018/queue.o ${OBJECTDIR}/_ext/1481540018/tasks.o ${OBJECTDIR}/src/led.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/MainControl.o ${OBJECTDIR}/src/Uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/17176491/heap_2.o.d ${OBJECTDIR}/_ext/1481540018/list.o.d ${OBJECTDIR}/_ext/1642425384/port.o.d ${OBJECTDIR}/_ext/1642425384/port_asm.o.d ${OBJECTDIR}/_ext/1481540018/queue.o.d ${OBJECTDIR}/_ext/1481540018/tasks.o.d ${OBJECTDIR}/src/led.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/MainControl.o.d ${OBJECTDIR}/src/Uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/17176491/heap_2.o ${OBJECTDIR}/_ext/1481540018/list.o ${OBJECTDIR}/_ext/1642425384/port.o ${OBJECTDIR}/_ext/1642425384/port_asm.o ${OBJECTDIR}/_ext/1481540018/queue.o ${OBJECTDIR}/_ext/1481540018/tasks.o ${OBJECTDIR}/src/led.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/MainControl.o ${OBJECTDIR}/src/Uart.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX360F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1642425384/port_asm.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1642425384 
	@${RM} ${OBJECTDIR}/_ext/1642425384/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1642425384/port_asm.o.ok ${OBJECTDIR}/_ext/1642425384/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1642425384/port_asm.o.d" "${OBJECTDIR}/_ext/1642425384/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1642425384/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1642425384/port_asm.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1642425384/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1
	
else
${OBJECTDIR}/_ext/1642425384/port_asm.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1642425384 
	@${RM} ${OBJECTDIR}/_ext/1642425384/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1642425384/port_asm.o.ok ${OBJECTDIR}/_ext/1642425384/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1642425384/port_asm.o.d" "${OBJECTDIR}/_ext/1642425384/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -MMD -MF "${OBJECTDIR}/_ext/1642425384/port_asm.o.d"  -o ${OBJECTDIR}/_ext/1642425384/port_asm.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1642425384/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/17176491/heap_2.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MemMang/heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/17176491 
	@${RM} ${OBJECTDIR}/_ext/17176491/heap_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/17176491/heap_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/17176491/heap_2.o.d" -o ${OBJECTDIR}/_ext/17176491/heap_2.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MemMang/heap_2.c   
	
${OBJECTDIR}/_ext/1481540018/list.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1481540018 
	@${RM} ${OBJECTDIR}/_ext/1481540018/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481540018/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1481540018/list.o.d" -o ${OBJECTDIR}/_ext/1481540018/list.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/1642425384/port.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1642425384 
	@${RM} ${OBJECTDIR}/_ext/1642425384/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1642425384/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1642425384/port.o.d" -o ${OBJECTDIR}/_ext/1642425384/port.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/1481540018/queue.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1481540018 
	@${RM} ${OBJECTDIR}/_ext/1481540018/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481540018/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1481540018/queue.o.d" -o ${OBJECTDIR}/_ext/1481540018/queue.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/1481540018/tasks.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1481540018 
	@${RM} ${OBJECTDIR}/_ext/1481540018/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481540018/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1481540018/tasks.o.d" -o ${OBJECTDIR}/_ext/1481540018/tasks.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/src/led.o: src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/led.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/led.o.d" -o ${OBJECTDIR}/src/led.o src/led.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
${OBJECTDIR}/src/MainControl.o: src/MainControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/MainControl.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/MainControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/MainControl.o.d" -o ${OBJECTDIR}/src/MainControl.o src/MainControl.c   
	
${OBJECTDIR}/src/Uart.o: src/Uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Uart.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/Uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/Uart.o.d" -o ${OBJECTDIR}/src/Uart.o src/Uart.c   
	
else
${OBJECTDIR}/_ext/17176491/heap_2.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MemMang/heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/17176491 
	@${RM} ${OBJECTDIR}/_ext/17176491/heap_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/17176491/heap_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/17176491/heap_2.o.d" -o ${OBJECTDIR}/_ext/17176491/heap_2.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MemMang/heap_2.c   
	
${OBJECTDIR}/_ext/1481540018/list.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1481540018 
	@${RM} ${OBJECTDIR}/_ext/1481540018/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481540018/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1481540018/list.o.d" -o ${OBJECTDIR}/_ext/1481540018/list.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/list.c   
	
${OBJECTDIR}/_ext/1642425384/port.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1642425384 
	@${RM} ${OBJECTDIR}/_ext/1642425384/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1642425384/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1642425384/port.o.d" -o ${OBJECTDIR}/_ext/1642425384/port.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/_ext/1481540018/queue.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1481540018 
	@${RM} ${OBJECTDIR}/_ext/1481540018/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481540018/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1481540018/queue.o.d" -o ${OBJECTDIR}/_ext/1481540018/queue.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/_ext/1481540018/tasks.o: ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1481540018 
	@${RM} ${OBJECTDIR}/_ext/1481540018/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1481540018/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1481540018/tasks.o.d" -o ${OBJECTDIR}/_ext/1481540018/tasks.o ../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/src/led.o: src/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/led.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/led.o.d" -o ${OBJECTDIR}/src/led.o src/led.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
${OBJECTDIR}/src/MainControl.o: src/MainControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/MainControl.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/MainControl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/MainControl.o.d" -o ${OBJECTDIR}/src/MainControl.o src/MainControl.c   
	
${OBJECTDIR}/src/Uart.o: src/Uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Uart.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/Uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./include" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../FreeRTOS/FreeRTOSV7.4.0/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/src/Uart.o.d" -o ${OBJECTDIR}/src/Uart.o src/Uart.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/lab_3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
