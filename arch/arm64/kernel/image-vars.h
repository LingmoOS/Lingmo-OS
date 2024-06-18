/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Linker script variables to be set after section resolution, as
 * ld.lld does not like variables assigned before SECTIONS is processed.
 */
#ifndef __ARM64_KERNEL_IMAGE_VARS_H
#define __ARM64_KERNEL_IMAGE_VARS_H

#ifndef LINKER_SCRIPT
#error This file should only be included in vmlinux.lds.S
#endif

PROVIDE(__efistub_primary_entry		= primary_entry);

/*
 * The EFI stub has its own symbol namespace prefixed by __efistub_, to
 * isolate it from the kernel proper. The following symbols are legally
 * accessed by the stub, so provide some aliases to make them accessible.
 * Only include data symbols here, or text symbols of functions that are
 * guaranteed to be safe when executed at another offset than they were
 * linked at. The routines below are all implemented in assembler in a
 * position independent manner
 */
PROVIDE(__efistub_caches_clean_inval_pou = __pi_caches_clean_inval_pou);

PROVIDE(__efistub__text			= _text);
PROVIDE(__efistub__end			= _end);
PROVIDE(__efistub___inittext_end       	= __inittext_end);
PROVIDE(__efistub__edata		= _edata);
#if defined(CONFIG_EFI_EARLYCON) || defined(CONFIG_SYSFB)
PROVIDE(__efistub_screen_info		= screen_info);
#endif
PROVIDE(__efistub__ctype		= _ctype);

PROVIDE(__pi___memcpy			= __pi_memcpy);
PROVIDE(__pi___memmove			= __pi_memmove);
PROVIDE(__pi___memset			= __pi_memset);

PROVIDE(__pi_id_aa64isar1_override	= id_aa64isar1_override);
PROVIDE(__pi_id_aa64isar2_override	= id_aa64isar2_override);
PROVIDE(__pi_id_aa64mmfr0_override	= id_aa64mmfr0_override);
PROVIDE(__pi_id_aa64mmfr1_override	= id_aa64mmfr1_override);
PROVIDE(__pi_id_aa64mmfr2_override	= id_aa64mmfr2_override);
PROVIDE(__pi_id_aa64pfr0_override	= id_aa64pfr0_override);
PROVIDE(__pi_id_aa64pfr1_override	= id_aa64pfr1_override);
PROVIDE(__pi_id_aa64smfr0_override	= id_aa64smfr0_override);
PROVIDE(__pi_id_aa64zfr0_override	= id_aa64zfr0_override);
PROVIDE(__pi_arm64_sw_feature_override	= arm64_sw_feature_override);
PROVIDE(__pi_arm64_use_ng_mappings	= arm64_use_ng_mappings);
#ifdef CONFIG_CAVIUM_ERRATUM_27456
PROVIDE(__pi_cavium_erratum_27456_cpus	= cavium_erratum_27456_cpus);
#endif
PROVIDE(__pi__ctype			= _ctype);
PROVIDE(__pi_memstart_offset_seed	= memstart_offset_seed);

PROVIDE(__pi_init_idmap_pg_dir		= init_idmap_pg_dir);
PROVIDE(__pi_init_idmap_pg_end		= init_idmap_pg_end);
PROVIDE(__pi_init_pg_dir		= init_pg_dir);
PROVIDE(__pi_init_pg_end		= init_pg_end);
PROVIDE(__pi_swapper_pg_dir		= swapper_pg_dir);

PROVIDE(__pi__text			= _text);
PROVIDE(__pi__stext               	= _stext);
PROVIDE(__pi__etext               	= _etext);
PROVIDE(__pi___start_rodata       	= __start_rodata);
PROVIDE(__pi___inittext_begin     	= __inittext_begin);
PROVIDE(__pi___inittext_end       	= __inittext_end);
PROVIDE(__pi___initdata_begin     	= __initdata_begin);
PROVIDE(__pi___initdata_end       	= __initdata_end);
PROVIDE(__pi__data                	= _data);
PROVIDE(__pi___bss_start		= __bss_start);
PROVIDE(__pi__end			= _end);

#ifdef CONFIG_KVM

/*
 * KVM nVHE code has its own symbol namespace prefixed with __kvm_nvhe_, to
 * separate it from the kernel proper. The following symbols are legally
 * accessed by it, therefore provide aliases to make them linkable.
 * Do not include symbols which may not be safely accessed under hypervisor
 * memory mappings.
 */

/* Alternative callbacks for init-time patching of nVHE hyp code. */
KVM_NVHE_ALIAS(kvm_patch_vector_branch);
KVM_NVHE_ALIAS(kvm_update_va_mask);
KVM_NVHE_ALIAS(kvm_get_kimage_voffset);
KVM_NVHE_ALIAS(kvm_compute_final_ctr_el0);
KVM_NVHE_ALIAS(spectre_bhb_patch_loop_iter);
KVM_NVHE_ALIAS(spectre_bhb_patch_loop_mitigation_enable);
KVM_NVHE_ALIAS(spectre_bhb_patch_wa3);
KVM_NVHE_ALIAS(spectre_bhb_patch_clearbhb);
KVM_NVHE_ALIAS(alt_cb_patch_nops);

/* Global kernel state accessed by nVHE hyp code. */
KVM_NVHE_ALIAS(kvm_vgic_global_state);

/* Kernel symbols used to call panic() from nVHE hyp code (via ERET). */
KVM_NVHE_ALIAS(nvhe_hyp_panic_handler);

/* Vectors installed by hyp-init on reset HVC. */
KVM_NVHE_ALIAS(__hyp_stub_vectors);

/* Static keys which are set if a vGIC trap should be handled in hyp. */
KVM_NVHE_ALIAS(vgic_v2_cpuif_trap);
KVM_NVHE_ALIAS(vgic_v3_cpuif_trap);

#ifdef CONFIG_ARM64_PSEUDO_NMI
/* Static key checked in GIC_PRIO_IRQOFF. */
KVM_NVHE_ALIAS(gic_nonsecure_priorities);
#endif

/* EL2 exception handling */
KVM_NVHE_ALIAS(__start___kvm_ex_table);
KVM_NVHE_ALIAS(__stop___kvm_ex_table);

/* PMU available static key */
#ifdef CONFIG_HW_PERF_EVENTS
KVM_NVHE_ALIAS(kvm_arm_pmu_available);
#endif

/* Position-independent library routines */
KVM_NVHE_ALIAS_HYP(clear_page, __pi_clear_page);
KVM_NVHE_ALIAS_HYP(copy_page, __pi_copy_page);
KVM_NVHE_ALIAS_HYP(memcpy, __pi_memcpy);
KVM_NVHE_ALIAS_HYP(memset, __pi_memset);

#ifdef CONFIG_KASAN
KVM_NVHE_ALIAS_HYP(__memcpy, __pi_memcpy);
KVM_NVHE_ALIAS_HYP(__memset, __pi_memset);
#endif

/* Hyp memory sections */
KVM_NVHE_ALIAS(__hyp_idmap_text_start);
KVM_NVHE_ALIAS(__hyp_idmap_text_end);
KVM_NVHE_ALIAS(__hyp_text_start);
KVM_NVHE_ALIAS(__hyp_text_end);
KVM_NVHE_ALIAS(__hyp_bss_start);
KVM_NVHE_ALIAS(__hyp_bss_end);
KVM_NVHE_ALIAS(__hyp_rodata_start);
KVM_NVHE_ALIAS(__hyp_rodata_end);

/* pKVM static key */
KVM_NVHE_ALIAS(kvm_protected_mode_initialized);

#endif /* CONFIG_KVM */

#ifdef CONFIG_EFI_ZBOOT
_kernel_codesize = ABSOLUTE(__inittext_end - _text);
#endif

#endif /* __ARM64_KERNEL_IMAGE_VARS_H */
