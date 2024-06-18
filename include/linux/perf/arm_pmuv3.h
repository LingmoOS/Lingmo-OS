/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2012 ARM Ltd.
 */

#ifndef __PERF_ARM_PMUV3_H
#define __PERF_ARM_PMUV3_H

#define ARMV8_PMU_MAX_COUNTERS	32
#define ARMV8_PMU_COUNTER_MASK	(ARMV8_PMU_MAX_COUNTERS - 1)

/*
 * Common architectural and microarchitectural event numbers.
 */
#define ARMV8_PMUV3_PERFCTR_SW_INCR				0x0000
#define ARMV8_PMUV3_PERFCTR_L1I_CACHE_REFILL			0x0001
#define ARMV8_PMUV3_PERFCTR_L1I_TLB_REFILL			0x0002
#define ARMV8_PMUV3_PERFCTR_L1D_CACHE_REFILL			0x0003
#define ARMV8_PMUV3_PERFCTR_L1D_CACHE				0x0004
#define ARMV8_PMUV3_PERFCTR_L1D_TLB_REFILL			0x0005
#define ARMV8_PMUV3_PERFCTR_LD_RETIRED				0x0006
#define ARMV8_PMUV3_PERFCTR_ST_RETIRED				0x0007
#define ARMV8_PMUV3_PERFCTR_INST_RETIRED			0x0008
#define ARMV8_PMUV3_PERFCTR_EXC_TAKEN				0x0009
#define ARMV8_PMUV3_PERFCTR_EXC_RETURN				0x000A
#define ARMV8_PMUV3_PERFCTR_CID_WRITE_RETIRED			0x000B
#define ARMV8_PMUV3_PERFCTR_PC_WRITE_RETIRED			0x000C
#define ARMV8_PMUV3_PERFCTR_BR_IMMED_RETIRED			0x000D
#define ARMV8_PMUV3_PERFCTR_BR_RETURN_RETIRED			0x000E
#define ARMV8_PMUV3_PERFCTR_UNALIGNED_LDST_RETIRED		0x000F
#define ARMV8_PMUV3_PERFCTR_BR_MIS_PRED				0x0010
#define ARMV8_PMUV3_PERFCTR_CPU_CYCLES				0x0011
#define ARMV8_PMUV3_PERFCTR_BR_PRED				0x0012
#define ARMV8_PMUV3_PERFCTR_MEM_ACCESS				0x0013
#define ARMV8_PMUV3_PERFCTR_L1I_CACHE				0x0014
#define ARMV8_PMUV3_PERFCTR_L1D_CACHE_WB			0x0015
#define ARMV8_PMUV3_PERFCTR_L2D_CACHE				0x0016
#define ARMV8_PMUV3_PERFCTR_L2D_CACHE_REFILL			0x0017
#define ARMV8_PMUV3_PERFCTR_L2D_CACHE_WB			0x0018
#define ARMV8_PMUV3_PERFCTR_BUS_ACCESS				0x0019
#define ARMV8_PMUV3_PERFCTR_MEMORY_ERROR			0x001A
#define ARMV8_PMUV3_PERFCTR_INST_SPEC				0x001B
#define ARMV8_PMUV3_PERFCTR_TTBR_WRITE_RETIRED			0x001C
#define ARMV8_PMUV3_PERFCTR_BUS_CYCLES				0x001D
#define ARMV8_PMUV3_PERFCTR_CHAIN				0x001E
#define ARMV8_PMUV3_PERFCTR_L1D_CACHE_ALLOCATE			0x001F
#define ARMV8_PMUV3_PERFCTR_L2D_CACHE_ALLOCATE			0x0020
#define ARMV8_PMUV3_PERFCTR_BR_RETIRED				0x0021
#define ARMV8_PMUV3_PERFCTR_BR_MIS_PRED_RETIRED			0x0022
#define ARMV8_PMUV3_PERFCTR_STALL_FRONTEND			0x0023
#define ARMV8_PMUV3_PERFCTR_STALL_BACKEND			0x0024
#define ARMV8_PMUV3_PERFCTR_L1D_TLB				0x0025
#define ARMV8_PMUV3_PERFCTR_L1I_TLB				0x0026
#define ARMV8_PMUV3_PERFCTR_L2I_CACHE				0x0027
#define ARMV8_PMUV3_PERFCTR_L2I_CACHE_REFILL			0x0028
#define ARMV8_PMUV3_PERFCTR_L3D_CACHE_ALLOCATE			0x0029
#define ARMV8_PMUV3_PERFCTR_L3D_CACHE_REFILL			0x002A
#define ARMV8_PMUV3_PERFCTR_L3D_CACHE				0x002B
#define ARMV8_PMUV3_PERFCTR_L3D_CACHE_WB			0x002C
#define ARMV8_PMUV3_PERFCTR_L2D_TLB_REFILL			0x002D
#define ARMV8_PMUV3_PERFCTR_L2I_TLB_REFILL			0x002E
#define ARMV8_PMUV3_PERFCTR_L2D_TLB				0x002F
#define ARMV8_PMUV3_PERFCTR_L2I_TLB				0x0030
#define ARMV8_PMUV3_PERFCTR_REMOTE_ACCESS			0x0031
#define ARMV8_PMUV3_PERFCTR_LL_CACHE				0x0032
#define ARMV8_PMUV3_PERFCTR_LL_CACHE_MISS			0x0033
#define ARMV8_PMUV3_PERFCTR_DTLB_WALK				0x0034
#define ARMV8_PMUV3_PERFCTR_ITLB_WALK				0x0035
#define ARMV8_PMUV3_PERFCTR_LL_CACHE_RD				0x0036
#define ARMV8_PMUV3_PERFCTR_LL_CACHE_MISS_RD			0x0037
#define ARMV8_PMUV3_PERFCTR_REMOTE_ACCESS_RD			0x0038
#define ARMV8_PMUV3_PERFCTR_L1D_CACHE_LMISS_RD			0x0039
#define ARMV8_PMUV3_PERFCTR_OP_RETIRED				0x003A
#define ARMV8_PMUV3_PERFCTR_OP_SPEC				0x003B
#define ARMV8_PMUV3_PERFCTR_STALL				0x003C
#define ARMV8_PMUV3_PERFCTR_STALL_SLOT_BACKEND			0x003D
#define ARMV8_PMUV3_PERFCTR_STALL_SLOT_FRONTEND			0x003E
#define ARMV8_PMUV3_PERFCTR_STALL_SLOT				0x003F

/* Statistical profiling extension microarchitectural events */
#define ARMV8_SPE_PERFCTR_SAMPLE_POP				0x4000
#define ARMV8_SPE_PERFCTR_SAMPLE_FEED				0x4001
#define ARMV8_SPE_PERFCTR_SAMPLE_FILTRATE			0x4002
#define ARMV8_SPE_PERFCTR_SAMPLE_COLLISION			0x4003

/* AMUv1 architecture events */
#define ARMV8_AMU_PERFCTR_CNT_CYCLES				0x4004
#define ARMV8_AMU_PERFCTR_STALL_BACKEND_MEM			0x4005

/* long-latency read miss events */
#define ARMV8_PMUV3_PERFCTR_L1I_CACHE_LMISS			0x4006
#define ARMV8_PMUV3_PERFCTR_L2D_CACHE_LMISS_RD			0x4009
#define ARMV8_PMUV3_PERFCTR_L2I_CACHE_LMISS			0x400A
#define ARMV8_PMUV3_PERFCTR_L3D_CACHE_LMISS_RD			0x400B

/* Trace buffer events */
#define ARMV8_PMUV3_PERFCTR_TRB_WRAP				0x400C
#define ARMV8_PMUV3_PERFCTR_TRB_TRIG				0x400E

/* Trace unit events */
#define ARMV8_PMUV3_PERFCTR_TRCEXTOUT0				0x4010
#define ARMV8_PMUV3_PERFCTR_TRCEXTOUT1				0x4011
#define ARMV8_PMUV3_PERFCTR_TRCEXTOUT2				0x4012
#define ARMV8_PMUV3_PERFCTR_TRCEXTOUT3				0x4013
#define ARMV8_PMUV3_PERFCTR_CTI_TRIGOUT4			0x4018
#define ARMV8_PMUV3_PERFCTR_CTI_TRIGOUT5			0x4019
#define ARMV8_PMUV3_PERFCTR_CTI_TRIGOUT6			0x401A
#define ARMV8_PMUV3_PERFCTR_CTI_TRIGOUT7			0x401B

/* additional latency from alignment events */
#define ARMV8_PMUV3_PERFCTR_LDST_ALIGN_LAT			0x4020
#define ARMV8_PMUV3_PERFCTR_LD_ALIGN_LAT			0x4021
#define ARMV8_PMUV3_PERFCTR_ST_ALIGN_LAT			0x4022

/* Armv8.5 Memory Tagging Extension events */
#define ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED			0x4024
#define ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED_RD			0x4025
#define ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED_WR			0x4026

/* ARMv8 recommended implementation defined event types */
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_RD			0x0040
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_WR			0x0041
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_RD		0x0042
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_WR		0x0043
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_INNER		0x0044
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_OUTER		0x0045
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_WB_VICTIM		0x0046
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_WB_CLEAN			0x0047
#define ARMV8_IMPDEF_PERFCTR_L1D_CACHE_INVAL			0x0048

#define ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_RD			0x004C
#define ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_WR			0x004D
#define ARMV8_IMPDEF_PERFCTR_L1D_TLB_RD				0x004E
#define ARMV8_IMPDEF_PERFCTR_L1D_TLB_WR				0x004F
#define ARMV8_IMPDEF_PERFCTR_L2D_CACHE_RD			0x0050
#define ARMV8_IMPDEF_PERFCTR_L2D_CACHE_WR			0x0051
#define ARMV8_IMPDEF_PERFCTR_L2D_CACHE_REFILL_RD		0x0052
#define ARMV8_IMPDEF_PERFCTR_L2D_CACHE_REFILL_WR		0x0053

#define ARMV8_IMPDEF_PERFCTR_L2D_CACHE_WB_VICTIM		0x0056
#define ARMV8_IMPDEF_PERFCTR_L2D_CACHE_WB_CLEAN			0x0057
#define ARMV8_IMPDEF_PERFCTR_L2D_CACHE_INVAL			0x0058

#define ARMV8_IMPDEF_PERFCTR_L2D_TLB_REFILL_RD			0x005C
#define ARMV8_IMPDEF_PERFCTR_L2D_TLB_REFILL_WR			0x005D
#define ARMV8_IMPDEF_PERFCTR_L2D_TLB_RD				0x005E
#define ARMV8_IMPDEF_PERFCTR_L2D_TLB_WR				0x005F
#define ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_RD			0x0060
#define ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_WR			0x0061
#define ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_SHARED			0x0062
#define ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_NOT_SHARED		0x0063
#define ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_NORMAL			0x0064
#define ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_PERIPH			0x0065
#define ARMV8_IMPDEF_PERFCTR_MEM_ACCESS_RD			0x0066
#define ARMV8_IMPDEF_PERFCTR_MEM_ACCESS_WR			0x0067
#define ARMV8_IMPDEF_PERFCTR_UNALIGNED_LD_SPEC			0x0068
#define ARMV8_IMPDEF_PERFCTR_UNALIGNED_ST_SPEC			0x0069
#define ARMV8_IMPDEF_PERFCTR_UNALIGNED_LDST_SPEC		0x006A

#define ARMV8_IMPDEF_PERFCTR_LDREX_SPEC				0x006C
#define ARMV8_IMPDEF_PERFCTR_STREX_PASS_SPEC			0x006D
#define ARMV8_IMPDEF_PERFCTR_STREX_FAIL_SPEC			0x006E
#define ARMV8_IMPDEF_PERFCTR_STREX_SPEC				0x006F
#define ARMV8_IMPDEF_PERFCTR_LD_SPEC				0x0070
#define ARMV8_IMPDEF_PERFCTR_ST_SPEC				0x0071
#define ARMV8_IMPDEF_PERFCTR_LDST_SPEC				0x0072
#define ARMV8_IMPDEF_PERFCTR_DP_SPEC				0x0073
#define ARMV8_IMPDEF_PERFCTR_ASE_SPEC				0x0074
#define ARMV8_IMPDEF_PERFCTR_VFP_SPEC				0x0075
#define ARMV8_IMPDEF_PERFCTR_PC_WRITE_SPEC			0x0076
#define ARMV8_IMPDEF_PERFCTR_CRYPTO_SPEC			0x0077
#define ARMV8_IMPDEF_PERFCTR_BR_IMMED_SPEC			0x0078
#define ARMV8_IMPDEF_PERFCTR_BR_RETURN_SPEC			0x0079
#define ARMV8_IMPDEF_PERFCTR_BR_INDIRECT_SPEC			0x007A

#define ARMV8_IMPDEF_PERFCTR_ISB_SPEC				0x007C
#define ARMV8_IMPDEF_PERFCTR_DSB_SPEC				0x007D
#define ARMV8_IMPDEF_PERFCTR_DMB_SPEC				0x007E

#define ARMV8_IMPDEF_PERFCTR_EXC_UNDEF				0x0081
#define ARMV8_IMPDEF_PERFCTR_EXC_SVC				0x0082
#define ARMV8_IMPDEF_PERFCTR_EXC_PABORT				0x0083
#define ARMV8_IMPDEF_PERFCTR_EXC_DABORT				0x0084

#define ARMV8_IMPDEF_PERFCTR_EXC_IRQ				0x0086
#define ARMV8_IMPDEF_PERFCTR_EXC_FIQ				0x0087
#define ARMV8_IMPDEF_PERFCTR_EXC_SMC				0x0088

#define ARMV8_IMPDEF_PERFCTR_EXC_HVC				0x008A
#define ARMV8_IMPDEF_PERFCTR_EXC_TRAP_PABORT			0x008B
#define ARMV8_IMPDEF_PERFCTR_EXC_TRAP_DABORT			0x008C
#define ARMV8_IMPDEF_PERFCTR_EXC_TRAP_OTHER			0x008D
#define ARMV8_IMPDEF_PERFCTR_EXC_TRAP_IRQ			0x008E
#define ARMV8_IMPDEF_PERFCTR_EXC_TRAP_FIQ			0x008F
#define ARMV8_IMPDEF_PERFCTR_RC_LD_SPEC				0x0090
#define ARMV8_IMPDEF_PERFCTR_RC_ST_SPEC				0x0091

#define ARMV8_IMPDEF_PERFCTR_L3D_CACHE_RD			0x00A0
#define ARMV8_IMPDEF_PERFCTR_L3D_CACHE_WR			0x00A1
#define ARMV8_IMPDEF_PERFCTR_L3D_CACHE_REFILL_RD		0x00A2
#define ARMV8_IMPDEF_PERFCTR_L3D_CACHE_REFILL_WR		0x00A3

#define ARMV8_IMPDEF_PERFCTR_L3D_CACHE_WB_VICTIM		0x00A6
#define ARMV8_IMPDEF_PERFCTR_L3D_CACHE_WB_CLEAN			0x00A7
#define ARMV8_IMPDEF_PERFCTR_L3D_CACHE_INVAL			0x00A8

/*
 * Per-CPU PMCR: config reg
 */
#define ARMV8_PMU_PMCR_E	(1 << 0) /* Enable all counters */
#define ARMV8_PMU_PMCR_P	(1 << 1) /* Reset all counters */
#define ARMV8_PMU_PMCR_C	(1 << 2) /* Cycle counter reset */
#define ARMV8_PMU_PMCR_D	(1 << 3) /* CCNT counts every 64th cpu cycle */
#define ARMV8_PMU_PMCR_X	(1 << 4) /* Export to ETM */
#define ARMV8_PMU_PMCR_DP	(1 << 5) /* Disable CCNT if non-invasive debug*/
#define ARMV8_PMU_PMCR_LC	(1 << 6) /* Overflow on 64 bit cycle counter */
#define ARMV8_PMU_PMCR_LP	(1 << 7) /* Long event counter enable */
#define ARMV8_PMU_PMCR_N	GENMASK(15, 11) /* Number of counters supported */
/* Mask for writable bits */
#define ARMV8_PMU_PMCR_MASK	(ARMV8_PMU_PMCR_E | ARMV8_PMU_PMCR_P | \
				 ARMV8_PMU_PMCR_C | ARMV8_PMU_PMCR_D | \
				 ARMV8_PMU_PMCR_X | ARMV8_PMU_PMCR_DP | \
				 ARMV8_PMU_PMCR_LC | ARMV8_PMU_PMCR_LP)

/*
 * PMOVSR: counters overflow flag status reg
 */
#define ARMV8_PMU_OVSR_P		GENMASK(30, 0)
#define ARMV8_PMU_OVSR_C		BIT(31)
/* Mask for writable bits is both P and C fields */
#define ARMV8_PMU_OVERFLOWED_MASK	(ARMV8_PMU_OVSR_P | ARMV8_PMU_OVSR_C)

/*
 * PMXEVTYPER: Event selection reg
 */
#define ARMV8_PMU_EVTYPE_EVENT	GENMASK(15, 0)	/* Mask for EVENT bits */
#define ARMV8_PMU_EVTYPE_TH	GENMASK_ULL(43, 32) /* arm64 only */
#define ARMV8_PMU_EVTYPE_TC	GENMASK_ULL(63, 61) /* arm64 only */

/*
 * Event filters for PMUv3
 */
#define ARMV8_PMU_EXCLUDE_EL1		(1U << 31)
#define ARMV8_PMU_EXCLUDE_EL0		(1U << 30)
#define ARMV8_PMU_EXCLUDE_NS_EL1	(1U << 29)
#define ARMV8_PMU_EXCLUDE_NS_EL0	(1U << 28)
#define ARMV8_PMU_INCLUDE_EL2		(1U << 27)
#define ARMV8_PMU_EXCLUDE_EL3		(1U << 26)

/*
 * PMUSERENR: user enable reg
 */
#define ARMV8_PMU_USERENR_EN	(1 << 0) /* PMU regs can be accessed at EL0 */
#define ARMV8_PMU_USERENR_SW	(1 << 1) /* PMSWINC can be written at EL0 */
#define ARMV8_PMU_USERENR_CR	(1 << 2) /* Cycle counter can be read at EL0 */
#define ARMV8_PMU_USERENR_ER	(1 << 3) /* Event counter can be read at EL0 */
/* Mask for writable bits */
#define ARMV8_PMU_USERENR_MASK	(ARMV8_PMU_USERENR_EN | ARMV8_PMU_USERENR_SW | \
				 ARMV8_PMU_USERENR_CR | ARMV8_PMU_USERENR_ER)

/* PMMIR_EL1.SLOTS mask */
#define ARMV8_PMU_SLOTS		GENMASK(7, 0)
#define ARMV8_PMU_BUS_SLOTS	GENMASK(15, 8)
#define ARMV8_PMU_BUS_WIDTH	GENMASK(19, 16)
#define ARMV8_PMU_THWIDTH	GENMASK(23, 20)

/*
 * This code is really good
 */

#define PMEVN_CASE(n, case_macro) \
	case n: case_macro(n); break

#define PMEVN_SWITCH(x, case_macro)				\
	do {							\
		switch (x) {					\
		PMEVN_CASE(0,  case_macro);			\
		PMEVN_CASE(1,  case_macro);			\
		PMEVN_CASE(2,  case_macro);			\
		PMEVN_CASE(3,  case_macro);			\
		PMEVN_CASE(4,  case_macro);			\
		PMEVN_CASE(5,  case_macro);			\
		PMEVN_CASE(6,  case_macro);			\
		PMEVN_CASE(7,  case_macro);			\
		PMEVN_CASE(8,  case_macro);			\
		PMEVN_CASE(9,  case_macro);			\
		PMEVN_CASE(10, case_macro);			\
		PMEVN_CASE(11, case_macro);			\
		PMEVN_CASE(12, case_macro);			\
		PMEVN_CASE(13, case_macro);			\
		PMEVN_CASE(14, case_macro);			\
		PMEVN_CASE(15, case_macro);			\
		PMEVN_CASE(16, case_macro);			\
		PMEVN_CASE(17, case_macro);			\
		PMEVN_CASE(18, case_macro);			\
		PMEVN_CASE(19, case_macro);			\
		PMEVN_CASE(20, case_macro);			\
		PMEVN_CASE(21, case_macro);			\
		PMEVN_CASE(22, case_macro);			\
		PMEVN_CASE(23, case_macro);			\
		PMEVN_CASE(24, case_macro);			\
		PMEVN_CASE(25, case_macro);			\
		PMEVN_CASE(26, case_macro);			\
		PMEVN_CASE(27, case_macro);			\
		PMEVN_CASE(28, case_macro);			\
		PMEVN_CASE(29, case_macro);			\
		PMEVN_CASE(30, case_macro);			\
		default: WARN(1, "Invalid PMEV* index\n");	\
		}						\
	} while (0)

#endif
