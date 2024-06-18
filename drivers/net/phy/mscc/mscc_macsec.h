/* SPDX-License-Identifier: (GPL-2.0 OR MIT) */
/*
 * Driver for Microsemi VSC85xx PHYs
 *
 * Copyright (c) 2020 Microsemi Corporation
 */

#ifndef _MSCC_PHY_MACSEC_H_
#define _MSCC_PHY_MACSEC_H_

#include <net/macsec.h>

#define MSCC_MS_MAX_FLOWS		16

#define CONTROL_TYPE_EGRESS		0x6
#define CONTROL_TYPE_INGRESS		0xf
#define CONTROL_IV0			BIT(5)
#define CONTROL_IV1			BIT(6)
#define CONTROL_IV2			BIT(7)
#define CONTROL_UPDATE_SEQ		BIT(13)
#define CONTROL_IV_IN_SEQ		BIT(14)
#define CONTROL_ENCRYPT_AUTH		BIT(15)
#define CONTROL_KEY_IN_CTX		BIT(16)
#define CONTROL_CRYPTO_ALG(x)		((x) << 17)
#define     CTRYPTO_ALG_AES_CTR_128	0x5
#define     CTRYPTO_ALG_AES_CTR_192	0x6
#define     CTRYPTO_ALG_AES_CTR_256	0x7
#define CONTROL_DIGEST_TYPE(x)		((x) << 21)
#define CONTROL_AUTH_ALG(x)		((x) << 23)
#define     AUTH_ALG_AES_GHAS		0x4
#define CONTROL_AN(x)			((x) << 26)
#define CONTROL_SEQ_TYPE(x)		((x) << 28)
#define CONTROL_SEQ_MASK		BIT(30)
#define CONTROL_CONTEXT_ID		BIT(31)

enum mscc_macsec_destination_ports {
	MSCC_MS_PORT_COMMON		= 0,
	MSCC_MS_PORT_RSVD		= 1,
	MSCC_MS_PORT_CONTROLLED		= 2,
	MSCC_MS_PORT_UNCONTROLLED	= 3,
};

enum mscc_macsec_drop_actions {
	MSCC_MS_ACTION_BYPASS_CRC	= 0,
	MSCC_MS_ACTION_BYPASS_BAD	= 1,
	MSCC_MS_ACTION_DROP		= 2,
	MSCC_MS_ACTION_BYPASS		= 3,
};

enum mscc_macsec_flow_types {
	MSCC_MS_FLOW_BYPASS		= 0,
	MSCC_MS_FLOW_DROP		= 1,
	MSCC_MS_FLOW_INGRESS		= 2,
	MSCC_MS_FLOW_EGRESS		= 3,
};

enum mscc_macsec_validate_levels {
	MSCC_MS_VALIDATE_DISABLED	= 0,
	MSCC_MS_VALIDATE_CHECK		= 1,
	MSCC_MS_VALIDATE_STRICT		= 2,
};

enum macsec_bank {
	FC_BUFFER   = 0x04,
	HOST_MAC    = 0x05,
	LINE_MAC    = 0x06,
	PROC_0      = 0x0e,
	PROC_2      = 0x0f,
	MACSEC_INGR = 0x38,
	MACSEC_EGR  = 0x3c,
};

struct macsec_flow {
	struct list_head list;
	enum mscc_macsec_destination_ports port;
	enum macsec_bank bank;
	u32 index;
	int assoc_num;
	bool has_transformation;

	/* Highest takes precedence [0..15] */
	u8 priority;

	union {
		struct macsec_rx_sa *rx_sa;
		struct macsec_tx_sa *tx_sa;
	};

	/* Matching */
	struct {
		u8 sci:1;
		u8 tagged:1;
		u8 untagged:1;
		u8 etype:1;
	} match;

	u16 etype;

	/* Action */
	struct {
		u8 bypass:1;
		u8 drop:1;
	} action;
};

#define MSCC_EXT_PAGE_MACSEC_17		17
#define MSCC_EXT_PAGE_MACSEC_18		18

#define MSCC_EXT_PAGE_MACSEC_19		19
#define MSCC_PHY_MACSEC_19_REG_ADDR(x)	(x)
#define MSCC_PHY_MACSEC_19_TARGET(x)	((x) << 12)
#define MSCC_PHY_MACSEC_19_READ		BIT(14)
#define MSCC_PHY_MACSEC_19_CMD		BIT(15)

#define MSCC_EXT_PAGE_MACSEC_20		20
#define MSCC_PHY_MACSEC_20_TARGET(x)	(x)

#define MSCC_MS_XFORM_REC(x, y)		(((x) << 5) + (y))
#define MSCC_MS_ENA_CFG			0x800
#define MSCC_MS_FC_CFG			0x804
#define MSCC_MS_SAM_MAC_SA_MATCH_LO(x)	(0x1000 + ((x) << 4))
#define MSCC_MS_SAM_MAC_SA_MATCH_HI(x)	(0x1001 + ((x) << 4))
#define MSCC_MS_SAM_MISC_MATCH(x)	(0x1004 + ((x) << 4))
#define MSCC_MS_SAM_MATCH_SCI_LO(x)	(0x1005 + ((x) << 4))
#define MSCC_MS_SAM_MATCH_SCI_HI(x)	(0x1006 + ((x) << 4))
#define MSCC_MS_SAM_MASK(x)		(0x1007 + ((x) << 4))
#define MSCC_MS_SAM_ENTRY_SET1		0x1808
#define MSCC_MS_SAM_ENTRY_CLEAR1	0x180c
#define MSCC_MS_SAM_FLOW_CTRL(x)	(0x1c00 + (x))
#define MSCC_MS_SAM_CP_TAG		0x1e40
#define MSCC_MS_SAM_NM_FLOW_NCP		0x1e51
#define MSCC_MS_SAM_NM_FLOW_CP		0x1e52
#define MSCC_MS_MISC_CONTROL		0x1e5f
#define MSCC_MS_COUNT_CONTROL		0x3204
#define MSCC_MS_PARAMS2_IG_CC_CONTROL	0x3a10
#define MSCC_MS_PARAMS2_IG_CP_TAG	0x3a14
#define MSCC_MS_VLAN_MTU_CHECK(x)	(0x3c40 + (x))
#define MSCC_MS_NON_VLAN_MTU_CHECK	0x3c48
#define MSCC_MS_PP_CTRL			0x3c4b
#define MSCC_MS_STATUS_CONTEXT_CTRL	0x3d02
#define MSCC_MS_INTR_CTRL_STATUS	0x3d04
#define MSCC_MS_BLOCK_CTX_UPDATE	0x3d0c
#define MSCC_MS_AIC_CTRL		0x3e02

/* MACSEC_ENA_CFG */
#define MSCC_MS_ENA_CFG_CLK_ENA				BIT(0)
#define MSCC_MS_ENA_CFG_SW_RST				BIT(1)
#define MSCC_MS_ENA_CFG_MACSEC_BYPASS_ENA		BIT(8)
#define MSCC_MS_ENA_CFG_MACSEC_ENA			BIT(9)
#define MSCC_MS_ENA_CFG_MACSEC_SPEED_MODE(x)		((x) << 10)
#define MSCC_MS_ENA_CFG_MACSEC_SPEED_MODE_M		GENMASK(12, 10)

/* MACSEC_FC_CFG */
#define MSCC_MS_FC_CFG_FCBUF_ENA			BIT(0)
#define MSCC_MS_FC_CFG_USE_PKT_EXPANSION_INDICATION	BIT(1)
#define MSCC_MS_FC_CFG_LOW_THRESH(x)			((x) << 4)
#define MSCC_MS_FC_CFG_LOW_THRESH_M			GENMASK(7, 4)
#define MSCC_MS_FC_CFG_HIGH_THRESH(x)			((x) << 8)
#define MSCC_MS_FC_CFG_HIGH_THRESH_M			GENMASK(11, 8)
#define MSCC_MS_FC_CFG_LOW_BYTES_VAL(x)			((x) << 12)
#define MSCC_MS_FC_CFG_LOW_BYTES_VAL_M			GENMASK(14, 12)
#define MSCC_MS_FC_CFG_HIGH_BYTES_VAL(x)		((x) << 16)
#define MSCC_MS_FC_CFG_HIGH_BYTES_VAL_M			GENMASK(18, 16)

/* MSCC_MS_SAM_MAC_SA_MATCH_HI */
#define MSCC_MS_SAM_MAC_SA_MATCH_HI_ETYPE(x)		((x) << 16)
#define MSCC_MS_SAM_MAC_SA_MATCH_HI_ETYPE_M		GENMASK(31, 16)

/* MACSEC_SAM_MISC_MATCH */
#define MSCC_MS_SAM_MISC_MATCH_VLAN_VALID		BIT(0)
#define MSCC_MS_SAM_MISC_MATCH_QINQ_FOUND		BIT(1)
#define MSCC_MS_SAM_MISC_MATCH_STAG_VALID		BIT(2)
#define MSCC_MS_SAM_MISC_MATCH_QTAG_VALID		BIT(3)
#define MSCC_MS_SAM_MISC_MATCH_VLAN_UP(x)		((x) << 4)
#define MSCC_MS_SAM_MISC_MATCH_VLAN_UP_M		GENMASK(6, 4)
#define MSCC_MS_SAM_MISC_MATCH_CONTROL_PACKET		BIT(7)
#define MSCC_MS_SAM_MISC_MATCH_UNTAGGED			BIT(8)
#define MSCC_MS_SAM_MISC_MATCH_TAGGED			BIT(9)
#define MSCC_MS_SAM_MISC_MATCH_BAD_TAG			BIT(10)
#define MSCC_MS_SAM_MISC_MATCH_KAY_TAG			BIT(11)
#define MSCC_MS_SAM_MISC_MATCH_SOURCE_PORT(x)		((x) << 12)
#define MSCC_MS_SAM_MISC_MATCH_SOURCE_PORT_M		GENMASK(13, 12)
#define MSCC_MS_SAM_MISC_MATCH_PRIORITY(x)		((x) << 16)
#define MSCC_MS_SAM_MISC_MATCH_PRIORITY_M		GENMASK(19, 16)
#define MSCC_MS_SAM_MISC_MATCH_AN(x)			((x) << 24)
#define MSCC_MS_SAM_MISC_MATCH_TCI(x)			((x) << 26)

/* MACSEC_SAM_MASK */
#define MSCC_MS_SAM_MASK_MAC_SA_MASK(x)			(x)
#define MSCC_MS_SAM_MASK_MAC_SA_MASK_M			GENMASK(5, 0)
#define MSCC_MS_SAM_MASK_MAC_DA_MASK(x)			((x) << 6)
#define MSCC_MS_SAM_MASK_MAC_DA_MASK_M			GENMASK(11, 6)
#define MSCC_MS_SAM_MASK_MAC_ETYPE_MASK			BIT(12)
#define MSCC_MS_SAM_MASK_VLAN_VLD_MASK			BIT(13)
#define MSCC_MS_SAM_MASK_QINQ_FOUND_MASK		BIT(14)
#define MSCC_MS_SAM_MASK_STAG_VLD_MASK			BIT(15)
#define MSCC_MS_SAM_MASK_QTAG_VLD_MASK			BIT(16)
#define MSCC_MS_SAM_MASK_VLAN_UP_MASK			BIT(17)
#define MSCC_MS_SAM_MASK_VLAN_ID_MASK			BIT(18)
#define MSCC_MS_SAM_MASK_SOURCE_PORT_MASK		BIT(19)
#define MSCC_MS_SAM_MASK_CTL_PACKET_MASK		BIT(20)
#define MSCC_MS_SAM_MASK_VLAN_UP_INNER_MASK		BIT(21)
#define MSCC_MS_SAM_MASK_VLAN_ID_INNER_MASK		BIT(22)
#define MSCC_MS_SAM_MASK_SCI_MASK			BIT(23)
#define MSCC_MS_SAM_MASK_AN_MASK(x)			((x) << 24)
#define MSCC_MS_SAM_MASK_TCI_MASK(x)			((x) << 26)

/* MACSEC_SAM_FLOW_CTRL_EGR */
#define MSCC_MS_SAM_FLOW_CTRL_FLOW_TYPE(x)		(x)
#define MSCC_MS_SAM_FLOW_CTRL_FLOW_TYPE_M		GENMASK(1, 0)
#define MSCC_MS_SAM_FLOW_CTRL_DEST_PORT(x)		((x) << 2)
#define MSCC_MS_SAM_FLOW_CTRL_DEST_PORT_M		GENMASK(3, 2)
#define MSCC_MS_SAM_FLOW_CTRL_RESV_4			BIT(4)
#define MSCC_MS_SAM_FLOW_CTRL_FLOW_CRYPT_AUTH		BIT(5)
#define MSCC_MS_SAM_FLOW_CTRL_DROP_ACTION(x)		((x) << 6)
#define MSCC_MS_SAM_FLOW_CTRL_DROP_ACTION_M		GENMASK(7, 6)
#define MSCC_MS_SAM_FLOW_CTRL_RESV_15_TO_8(x)		((x) << 8)
#define MSCC_MS_SAM_FLOW_CTRL_RESV_15_TO_8_M		GENMASK(15, 8)
#define MSCC_MS_SAM_FLOW_CTRL_PROTECT_FRAME		BIT(16)
#define MSCC_MS_SAM_FLOW_CTRL_REPLAY_PROTECT		BIT(16)
#define MSCC_MS_SAM_FLOW_CTRL_SA_IN_USE			BIT(17)
#define MSCC_MS_SAM_FLOW_CTRL_INCLUDE_SCI		BIT(18)
#define MSCC_MS_SAM_FLOW_CTRL_USE_ES			BIT(19)
#define MSCC_MS_SAM_FLOW_CTRL_USE_SCB			BIT(20)
#define MSCC_MS_SAM_FLOW_CTRL_VALIDATE_FRAMES(x)	((x) << 19)
#define MSCC_MS_SAM_FLOW_CTRL_TAG_BYPASS_SIZE(x)	((x) << 21)
#define MSCC_MS_SAM_FLOW_CTRL_TAG_BYPASS_SIZE_M		GENMASK(22, 21)
#define MSCC_MS_SAM_FLOW_CTRL_RESV_23			BIT(23)
#define MSCC_MS_SAM_FLOW_CTRL_CONFIDENTIALITY_OFFSET(x)	((x) << 24)
#define MSCC_MS_SAM_FLOW_CTRL_CONFIDENTIALITY_OFFSET_M	GENMASK(30, 24)
#define MSCC_MS_SAM_FLOW_CTRL_CONF_PROTECT		BIT(31)

/* MACSEC_SAM_CP_TAG */
#define MSCC_MS_SAM_CP_TAG_MAP_TBL(x)			(x)
#define MSCC_MS_SAM_CP_TAG_MAP_TBL_M			GENMASK(23, 0)
#define MSCC_MS_SAM_CP_TAG_DEF_UP(x)			((x) << 24)
#define MSCC_MS_SAM_CP_TAG_DEF_UP_M			GENMASK(26, 24)
#define MSCC_MS_SAM_CP_TAG_STAG_UP_EN			BIT(27)
#define MSCC_MS_SAM_CP_TAG_QTAG_UP_EN			BIT(28)
#define MSCC_MS_SAM_CP_TAG_PARSE_QINQ			BIT(29)
#define MSCC_MS_SAM_CP_TAG_PARSE_STAG			BIT(30)
#define MSCC_MS_SAM_CP_TAG_PARSE_QTAG			BIT(31)

/* MACSEC_SAM_NM_FLOW_NCP */
#define MSCC_MS_SAM_NM_FLOW_NCP_UNTAGGED_FLOW_TYPE(x)	(x)
#define MSCC_MS_SAM_NM_FLOW_NCP_UNTAGGED_DEST_PORT(x)	((x) << 2)
#define MSCC_MS_SAM_NM_FLOW_NCP_UNTAGGED_DROP_ACTION(x)	((x) << 6)
#define MSCC_MS_SAM_NM_FLOW_NCP_TAGGED_FLOW_TYPE(x)	((x) << 8)
#define MSCC_MS_SAM_NM_FLOW_NCP_TAGGED_DEST_PORT(x)	((x) << 10)
#define MSCC_MS_SAM_NM_FLOW_NCP_TAGGED_DROP_ACTION(x)	((x) << 14)
#define MSCC_MS_SAM_NM_FLOW_NCP_BADTAG_FLOW_TYPE(x)	((x) << 16)
#define MSCC_MS_SAM_NM_FLOW_NCP_BADTAG_DEST_PORT(x)	((x) << 18)
#define MSCC_MS_SAM_NM_FLOW_NCP_BADTAG_DROP_ACTION(x)	((x) << 22)
#define MSCC_MS_SAM_NM_FLOW_NCP_KAY_FLOW_TYPE(x)	((x) << 24)
#define MSCC_MS_SAM_NM_FLOW_NCP_KAY_DEST_PORT(x)	((x) << 26)
#define MSCC_MS_SAM_NM_FLOW_NCP_KAY_DROP_ACTION(x)	((x) << 30)

/* MACSEC_SAM_NM_FLOW_CP */
#define MSCC_MS_SAM_NM_FLOW_CP_UNTAGGED_FLOW_TYPE(x)	(x)
#define MSCC_MS_SAM_NM_FLOW_CP_UNTAGGED_DEST_PORT(x)	((x) << 2)
#define MSCC_MS_SAM_NM_FLOW_CP_UNTAGGED_DROP_ACTION(x)	((x) << 6)
#define MSCC_MS_SAM_NM_FLOW_CP_TAGGED_FLOW_TYPE(x)	((x) << 8)
#define MSCC_MS_SAM_NM_FLOW_CP_TAGGED_DEST_PORT(x)	((x) << 10)
#define MSCC_MS_SAM_NM_FLOW_CP_TAGGED_DROP_ACTION(x)	((x) << 14)
#define MSCC_MS_SAM_NM_FLOW_CP_BADTAG_FLOW_TYPE(x)	((x) << 16)
#define MSCC_MS_SAM_NM_FLOW_CP_BADTAG_DEST_PORT(x)	((x) << 18)
#define MSCC_MS_SAM_NM_FLOW_CP_BADTAG_DROP_ACTION(x)	((x) << 22)
#define MSCC_MS_SAM_NM_FLOW_CP_KAY_FLOW_TYPE(x)		((x) << 24)
#define MSCC_MS_SAM_NM_FLOW_CP_KAY_DEST_PORT(x)		((x) << 26)
#define MSCC_MS_SAM_NM_FLOW_CP_KAY_DROP_ACTION(x)	((x) << 30)

/* MACSEC_MISC_CONTROL */
#define MSCC_MS_MISC_CONTROL_MC_LATENCY_FIX(x)		(x)
#define MSCC_MS_MISC_CONTROL_MC_LATENCY_FIX_M		GENMASK(5, 0)
#define MSCC_MS_MISC_CONTROL_STATIC_BYPASS		BIT(8)
#define MSCC_MS_MISC_CONTROL_NM_MACSEC_EN		BIT(9)
#define MSCC_MS_MISC_CONTROL_VALIDATE_FRAMES(x)		((x) << 10)
#define MSCC_MS_MISC_CONTROL_VALIDATE_FRAMES_M		GENMASK(11, 10)
#define MSCC_MS_MISC_CONTROL_XFORM_REC_SIZE(x)		((x) << 24)
#define MSCC_MS_MISC_CONTROL_XFORM_REC_SIZE_M		GENMASK(25, 24)

/* MACSEC_COUNT_CONTROL */
#define MSCC_MS_COUNT_CONTROL_RESET_ALL			BIT(0)
#define MSCC_MS_COUNT_CONTROL_DEBUG_ACCESS		BIT(1)
#define MSCC_MS_COUNT_CONTROL_SATURATE_CNTRS		BIT(2)
#define MSCC_MS_COUNT_CONTROL_AUTO_CNTR_RESET		BIT(3)

/* MACSEC_PARAMS2_IG_CC_CONTROL */
#define MSCC_MS_PARAMS2_IG_CC_CONTROL_NON_MATCH_CTRL_ACT	BIT(14)
#define MSCC_MS_PARAMS2_IG_CC_CONTROL_NON_MATCH_ACT	BIT(15)

/* MACSEC_PARAMS2_IG_CP_TAG */
#define MSCC_MS_PARAMS2_IG_CP_TAG_MAP_TBL(x)		(x)
#define MSCC_MS_PARAMS2_IG_CP_TAG_MAP_TBL_M		GENMASK(23, 0)
#define MSCC_MS_PARAMS2_IG_CP_TAG_DEF_UP(x)		((x) << 24)
#define MSCC_MS_PARAMS2_IG_CP_TAG_DEF_UP_M		GENMASK(26, 24)
#define MSCC_MS_PARAMS2_IG_CP_TAG_STAG_UP_EN		BIT(27)
#define MSCC_MS_PARAMS2_IG_CP_TAG_QTAG_UP_EN		BIT(28)
#define MSCC_MS_PARAMS2_IG_CP_TAG_PARSE_QINQ		BIT(29)
#define MSCC_MS_PARAMS2_IG_CP_TAG_PARSE_STAG		BIT(30)
#define MSCC_MS_PARAMS2_IG_CP_TAG_PARSE_QTAG		BIT(31)

/* MACSEC_VLAN_MTU_CHECK */
#define MSCC_MS_VLAN_MTU_CHECK_MTU_COMPARE(x)		(x)
#define MSCC_MS_VLAN_MTU_CHECK_MTU_COMPARE_M		GENMASK(14, 0)
#define MSCC_MS_VLAN_MTU_CHECK_MTU_COMP_DROP		BIT(15)

/* MACSEC_NON_VLAN_MTU_CHECK */
#define MSCC_MS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(x)	(x)
#define MSCC_MS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE_M	GENMASK(14, 0)
#define MSCC_MS_NON_VLAN_MTU_CHECK_NV_MTU_COMP_DROP	BIT(15)

/* MACSEC_PP_CTRL */
#define MSCC_MS_PP_CTRL_MACSEC_OCTET_INCR_MODE		BIT(0)

/* MACSEC_INTR_CTRL_STATUS */
#define MSCC_MS_INTR_CTRL_STATUS_INTR_CLR_STATUS(x)	(x)
#define MSCC_MS_INTR_CTRL_STATUS_INTR_CLR_STATUS_M	GENMASK(15, 0)
#define MSCC_MS_INTR_CTRL_STATUS_INTR_ENABLE(x)		((x) << 16)
#define MSCC_MS_INTR_CTRL_STATUS_INTR_ENABLE_M		GENMASK(31, 16)
#define MACSEC_INTR_CTRL_STATUS_ROLLOVER		BIT(5)

#endif /* _MSCC_PHY_MACSEC_H_ */
