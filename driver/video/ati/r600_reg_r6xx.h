/*
 * RadeonHD R6xx, R7xx Register documentation
 *
 * Copyright (C) 2008-2009  Advanced Micro Devices, Inc.
 * Copyright (C) 2008-2009  Matthias Hopf
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _R600_REG_R6xx_H_
#define _R600_REG_R6xx_H_

/*
 * Registers for R6xx chips that are not documented yet
 */

enum
{

    MM_INDEX = 0x0000,
    MM_DATA  = 0x0004,

    SRBM_STATUS               = 0x0e50,
    RLC_RQ_PENDING_bit        = 1 << 3,
    RCU_RQ_PENDING_bit        = 1 << 4,
    GRBM_RQ_PENDING_bit       = 1 << 5,
    HI_RQ_PENDING_bit         = 1 << 6,
    IO_EXTERN_SIGNAL_bit      = 1 << 7,
    VMC_BUSY_bit              = 1 << 8,
    MCB_BUSY_bit              = 1 << 9,
    MCDZ_BUSY_bit             = 1 << 10,
    MCDY_BUSY_bit             = 1 << 11,
    MCDX_BUSY_bit             = 1 << 12,
    MCDW_BUSY_bit             = 1 << 13,
    SEM_BUSY_bit              = 1 << 14,
    SRBM_STATUS__RLC_BUSY_bit = 1 << 15,
    PDMA_BUSY_bit             = 1 << 16,
    IH_BUSY_bit               = 1 << 17,
    CSC_BUSY_bit              = 1 << 20,
    CMC7_BUSY_bit             = 1 << 21,
    CMC6_BUSY_bit             = 1 << 22,
    CMC5_BUSY_bit             = 1 << 23,
    CMC4_BUSY_bit             = 1 << 24,
    CMC3_BUSY_bit             = 1 << 25,
    CMC2_BUSY_bit             = 1 << 26,
    CMC1_BUSY_bit             = 1 << 27,
    CMC0_BUSY_bit             = 1 << 28,
    BIF_BUSY_bit              = 1 << 29,
    IDCT_BUSY_bit             = 1 << 30,

    SRBM_READ_ERROR         = 0x0e98,
    READ_ADDRESS_mask       = 0xffff << 2,
    READ_ADDRESS_shift      = 2,
    READ_REQUESTER_HI_bit   = 1 << 24,
    READ_REQUESTER_GRBM_bit = 1 << 25,
    READ_REQUESTER_RCU_bit  = 1 << 26,
    READ_REQUESTER_RLC_bit  = 1 << 27,
    READ_ERROR_bit          = 1 << 31,

    SRBM_INT_STATUS              = 0x0ea4,
    RDERR_INT_STAT_bit           = 1 << 0,
    GFX_CNTX_SWITCH_INT_STAT_bit = 1 << 1,
    SRBM_INT_ACK                 = 0x0ea8,
    RDERR_INT_ACK_bit            = 1 << 0,
    GFX_CNTX_SWITCH_INT_ACK_bit  = 1 << 1,

    R6XX_MC_VM_FB_LOCATION = 0x2180,

    VENDOR_DEVICE_ID = 0x4000,

    HDP_MEM_COHERENCY_FLUSH_CNTL = 0x5480,

    D1GRPH_PRIMARY_SURFACE_ADDRESS = 0x6110,
    D1GRPH_PITCH                   = 0x6120,
    D1GRPH_Y_END                   = 0x6138,

    GRBM_STATUS               = 0x8010,
    CMDFIFO_AVAIL_mask        = 0x1f << 0,
    CMDFIFO_AVAIL_shift       = 0,
    SRBM_RQ_PENDING_bit       = 1 << 5,
    CP_RQ_PENDING_bit         = 1 << 6,
    CF_RQ_PENDING_bit         = 1 << 7,
    PF_RQ_PENDING_bit         = 1 << 8,
    GRBM_EE_BUSY_bit          = 1 << 10,
    GRBM_STATUS__VC_BUSY_bit  = 1 << 11,
    DB03_CLEAN_bit            = 1 << 12,
    CB03_CLEAN_bit            = 1 << 13,
    VGT_BUSY_NO_DMA_bit       = 1 << 16,
    GRBM_STATUS__VGT_BUSY_bit = 1 << 17,
    TA03_BUSY_bit             = 1 << 18,
    GRBM_STATUS__TC_BUSY_bit  = 1 << 19,
    SX_BUSY_bit               = 1 << 20,
    SH_BUSY_bit               = 1 << 21,
    SPI03_BUSY_bit            = 1 << 22,
    SMX_BUSY_bit              = 1 << 23,
    SC_BUSY_bit               = 1 << 24,
    PA_BUSY_bit               = 1 << 25,
    DB03_BUSY_bit             = 1 << 26,
    CR_BUSY_bit               = 1 << 27,
    CP_COHERENCY_BUSY_bit     = 1 << 28,
    GRBM_STATUS__CP_BUSY_bit  = 1 << 29,
    CB03_BUSY_bit             = 1 << 30,
    GUI_ACTIVE_bit            = 1 << 31,
    GRBM_STATUS2              = 0x8014,
    CR_CLEAN_bit              = 1 << 0,
    SMX_CLEAN_bit             = 1 << 1,
    SPI0_BUSY_bit             = 1 << 8,
    SPI1_BUSY_bit             = 1 << 9,
    SPI2_BUSY_bit             = 1 << 10,
    SPI3_BUSY_bit             = 1 << 11,
    TA0_BUSY_bit              = 1 << 12,
    TA1_BUSY_bit              = 1 << 13,
    TA2_BUSY_bit              = 1 << 14,
    TA3_BUSY_bit              = 1 << 15,
    DB0_BUSY_bit              = 1 << 16,
    DB1_BUSY_bit              = 1 << 17,
    DB2_BUSY_bit              = 1 << 18,
    DB3_BUSY_bit              = 1 << 19,
    CB0_BUSY_bit              = 1 << 20,
    CB1_BUSY_bit              = 1 << 21,
    CB2_BUSY_bit              = 1 << 22,
    CB3_BUSY_bit              = 1 << 23,
    GRBM_SOFT_RESET           = 0x8020,
    SOFT_RESET_CP_bit         = 1 << 0,
    SOFT_RESET_CB_bit         = 1 << 1,
    SOFT_RESET_CR_bit         = 1 << 2,
    SOFT_RESET_DB_bit         = 1 << 3,
    SOFT_RESET_PA_bit         = 1 << 5,
    SOFT_RESET_SC_bit         = 1 << 6,
    SOFT_RESET_SMX_bit        = 1 << 7,
    SOFT_RESET_SPI_bit        = 1 << 8,
    SOFT_RESET_SH_bit         = 1 << 9,
    SOFT_RESET_SX_bit         = 1 << 10,
    SOFT_RESET_TC_bit         = 1 << 11,
    SOFT_RESET_TA_bit         = 1 << 12,
    SOFT_RESET_VC_bit         = 1 << 13,
    SOFT_RESET_VGT_bit        = 1 << 14,
    SOFT_RESET_GRBM_GCA_bit   = 1 << 15,

    WAIT_UNTIL            = 0x8040,
    WAIT_CP_DMA_IDLE_bit  = 1 << 8,
    WAIT_CMDFIFO_bit      = 1 << 10,
    WAIT_2D_IDLE_bit      = 1 << 14,
    WAIT_3D_IDLE_bit      = 1 << 15,
    WAIT_2D_IDLECLEAN_bit = 1 << 16,
    WAIT_3D_IDLECLEAN_bit = 1 << 17,
    WAIT_EXTERN_SIG_bit   = 1 << 19,
    CMDFIFO_ENTRIES_mask  = 0x1f << 20,
    CMDFIFO_ENTRIES_shift = 20,

    GRBM_READ_ERROR            = 0x8058,
/* 	READ_ADDRESS_mask                                 = 0xffff << 2, */
/* 	READ_ADDRESS_shift                                = 2, */
    READ_REQUESTER_SRBM_bit    = 1 << 28,
    READ_REQUESTER_CP_bit      = 1 << 29,
    READ_REQUESTER_WU_POLL_bit = 1 << 30,
/* 	READ_ERROR_bit                                    = 1 << 31, */

    SCRATCH_REG0 = 0x8500,
    SCRATCH_REG1 = 0x8504,
    SCRATCH_REG2 = 0x8508,
    SCRATCH_REG3 = 0x850c,
    SCRATCH_REG4 = 0x8510,
    SCRATCH_REG5 = 0x8514,
    SCRATCH_REG6 = 0x8518,
    SCRATCH_REG7 = 0x851c,
    SCRATCH_UMSK = 0x8540,
    SCRATCH_ADDR = 0x8544,

    CP_COHER_CNTL           = 0x85f0,
    DEST_BASE_0_ENA_bit     = 1 << 0,
    DEST_BASE_1_ENA_bit     = 1 << 1,
    SO0_DEST_BASE_ENA_bit   = 1 << 2,
    SO1_DEST_BASE_ENA_bit   = 1 << 3,
    SO2_DEST_BASE_ENA_bit   = 1 << 4,
    SO3_DEST_BASE_ENA_bit   = 1 << 5,
    CB0_DEST_BASE_ENA_bit   = 1 << 6,
    CB1_DEST_BASE_ENA_bit   = 1 << 7,
    CB2_DEST_BASE_ENA_bit   = 1 << 8,
    CB3_DEST_BASE_ENA_bit   = 1 << 9,
    CB4_DEST_BASE_ENA_bit   = 1 << 10,
    CB5_DEST_BASE_ENA_bit   = 1 << 11,
    CB6_DEST_BASE_ENA_bit   = 1 << 12,
    CB7_DEST_BASE_ENA_bit   = 1 << 13,
    DB_DEST_BASE_ENA_bit    = 1 << 14,
    CR_DEST_BASE_ENA_bit    = 1 << 15,
    TC_ACTION_ENA_bit       = 1 << 23,
    VC_ACTION_ENA_bit       = 1 << 24,
    CB_ACTION_ENA_bit       = 1 << 25,
    DB_ACTION_ENA_bit       = 1 << 26,
    SH_ACTION_ENA_bit       = 1 << 27,
    SMX_ACTION_ENA_bit      = 1 << 28,
    CR0_ACTION_ENA_bit      = 1 << 29,
    CR1_ACTION_ENA_bit      = 1 << 30,
    CR2_ACTION_ENA_bit      = 1 << 31,
    CP_COHER_SIZE           = 0x85f4,
    CP_COHER_BASE           = 0x85f8,
    CP_COHER_STATUS         = 0x85fc,
    MATCHING_GFX_CNTX_mask  = 0xff << 0,
    MATCHING_GFX_CNTX_shift = 0,
    MATCHING_CR_CNTX_mask   = 0xffff << 8,
    MATCHING_CR_CNTX_shift  = 8,
    STATUS_bit              = 1 << 31,

    CP_STALLED_STAT1                  = 0x8674,
    RBIU_TO_DMA_NOT_RDY_TO_RCV_bit    = 1 << 0,
    RBIU_TO_IBS_NOT_RDY_TO_RCV_bit    = 1 << 1,
    RBIU_TO_SEM_NOT_RDY_TO_RCV_bit    = 1 << 2,
    RBIU_TO_2DREGS_NOT_RDY_TO_RCV_bit = 1 << 3,
    RBIU_TO_MEMWR_NOT_RDY_TO_RCV_bit  = 1 << 4,
    RBIU_TO_MEMRD_NOT_RDY_TO_RCV_bit  = 1 << 5,
    RBIU_TO_EOPD_NOT_RDY_TO_RCV_bit   = 1 << 6,
    RBIU_TO_RECT_NOT_RDY_TO_RCV_bit   = 1 << 7,
    RBIU_TO_STRMO_NOT_RDY_TO_RCV_bit  = 1 << 8,
    RBIU_TO_PSTAT_NOT_RDY_TO_RCV_bit  = 1 << 9,
    MIU_WAITING_ON_RDREQ_FREE_bit     = 1 << 16,
    MIU_WAITING_ON_WRREQ_FREE_bit     = 1 << 17,
    MIU_NEEDS_AVAIL_WRREQ_PHASE_bit   = 1 << 18,
    RCIU_WAITING_ON_GRBM_FREE_bit     = 1 << 24,
    RCIU_WAITING_ON_VGT_FREE_bit      = 1 << 25,
    RCIU_STALLED_ON_ME_READ_bit       = 1 << 26,
    RCIU_STALLED_ON_DMA_READ_bit      = 1 << 27,
    RCIU_HALTED_BY_REG_VIOLATION_bit  = 1 << 28,
    CP_STALLED_STAT2                  = 0x8678,
    PFP_TO_CSF_NOT_RDY_TO_RCV_bit     = 1 << 0,
    PFP_TO_MEQ_NOT_RDY_TO_RCV_bit     = 1 << 1,
    PFP_TO_VGT_NOT_RDY_TO_RCV_bit     = 1 << 2,
    PFP_HALTED_BY_INSTR_VIOLATION_bit = 1 << 3,
    MULTIPASS_IB_PENDING_IN_PFP_bit   = 1 << 4,
    ME_BRUSH_WC_NOT_RDY_TO_RCV_bit    = 1 << 8,
    ME_STALLED_ON_BRUSH_LOGIC_bit     = 1 << 9,
    CR_CNTX_NOT_AVAIL_TO_ME_bit       = 1 << 10,
    GFX_CNTX_NOT_AVAIL_TO_ME_bit      = 1 << 11,
    ME_RCIU_NOT_RDY_TO_RCV_bit        = 1 << 12,
    ME_TO_CONST_NOT_RDY_TO_RCV_bit    = 1 << 13,
    ME_WAITING_DATA_FROM_PFP_bit      = 1 << 14,
    ME_WAITING_ON_PARTIAL_FLUSH_bit   = 1 << 15,
    RECT_FIFO_NEEDS_CR_RECT_DONE_bit  = 1 << 16,
    RECT_FIFO_NEEDS_WR_CONFIRM_bit    = 1 << 17,
    EOPD_FIFO_NEEDS_SC_EOP_DONE_bit   = 1 << 18,
    EOPD_FIFO_NEEDS_SMX_EOP_DONE_bit  = 1 << 19,
    EOPD_FIFO_NEEDS_WR_CONFIRM_bit    = 1 << 20,
    EOPD_FIFO_NEEDS_SIGNAL_SEM_bit    = 1 << 21,
    SO_NUMPRIM_FIFO_NEEDS_SOADDR_bit  = 1 << 22,
    SO_NUMPRIM_FIFO_NEEDS_NUMPRIM_bit = 1 << 23,
    PIPE_STATS_FIFO_NEEDS_SAMPLE_bit  = 1 << 24,
    SURF_SYNC_NEEDS_IDLE_CNTXS_bit    = 1 << 30,
    SURF_SYNC_NEEDS_ALL_CLEAN_bit     = 1 << 31,
    CP_BUSY_STAT                      = 0x867c,
    REG_BUS_FIFO_BUSY_bit             = 1 << 0,
    RING_FETCHING_DATA_bit            = 1 << 1,
    INDR1_FETCHING_DATA_bit           = 1 << 2,
    INDR2_FETCHING_DATA_bit           = 1 << 3,
    STATE_FETCHING_DATA_bit           = 1 << 4,
    PRED_FETCHING_DATA_bit            = 1 << 5,
    COHER_CNTR_NEQ_ZERO_bit           = 1 << 6,
    PFP_PARSING_PACKETS_bit           = 1 << 7,
    ME_PARSING_PACKETS_bit            = 1 << 8,
    RCIU_PFP_BUSY_bit                 = 1 << 9,
    RCIU_ME_BUSY_bit                  = 1 << 10,
    OUTSTANDING_READ_TAGS_bit         = 1 << 11,
    SEM_CMDFIFO_NOT_EMPTY_bit         = 1 << 12,
    SEM_FAILED_AND_HOLDING_bit        = 1 << 13,
    SEM_POLLING_FOR_PASS_bit          = 1 << 14,
    _3D_BUSY_bit                      = 1 << 15,
    _2D_BUSY_bit                      = 1 << 16,
    CP_STAT                           = 0x8680,
    CSF_RING_BUSY_bit                 = 1 << 0,
    CSF_WPTR_POLL_BUSY_bit            = 1 << 1,
    CSF_INDIRECT1_BUSY_bit            = 1 << 2,
    CSF_INDIRECT2_BUSY_bit            = 1 << 3,
    CSF_STATE_BUSY_bit                = 1 << 4,
    CSF_PREDICATE_BUSY_bit            = 1 << 5,
    CSF_BUSY_bit                      = 1 << 6,
    MIU_RDREQ_BUSY_bit                = 1 << 7,
    MIU_WRREQ_BUSY_bit                = 1 << 8,
    ROQ_RING_BUSY_bit                 = 1 << 9,
    ROQ_INDIRECT1_BUSY_bit            = 1 << 10,
    ROQ_INDIRECT2_BUSY_bit            = 1 << 11,
    ROQ_STATE_BUSY_bit                = 1 << 12,
    ROQ_PREDICATE_BUSY_bit            = 1 << 13,
    ROQ_ALIGN_BUSY_bit                = 1 << 14,
    PFP_BUSY_bit                      = 1 << 15,
    MEQ_BUSY_bit                      = 1 << 16,
    ME_BUSY_bit                       = 1 << 17,
    QUERY_BUSY_bit                    = 1 << 18,
    SEMAPHORE_BUSY_bit                = 1 << 19,
    INTERRUPT_BUSY_bit                = 1 << 20,
    SURFACE_SYNC_BUSY_bit             = 1 << 21,
    DMA_BUSY_bit                      = 1 << 22,
    RCIU_BUSY_bit                     = 1 << 23,
    CP_STAT__CP_BUSY_bit              = 1 << 31,

    CP_ME_CNTL       = 0x86d8,
    ME_STATMUX_mask  = 0xff << 0,
    ME_STATMUX_shift = 0,
    ME_HALT_bit      = 1 << 28,
    CP_ME_STATUS     = 0x86dc,

    CP_RB_RPTR            = 0x8700,
    RB_RPTR_mask          = 0xfffff << 0,
    RB_RPTR_shift         = 0,
    CP_RB_WPTR_DELAY      = 0x8704,
    PRE_WRITE_TIMER_mask  = 0xfffffff << 0,
    PRE_WRITE_TIMER_shift = 0,
    PRE_WRITE_LIMIT_mask  = 0x0f << 28,
    PRE_WRITE_LIMIT_shift = 28,

    CP_ROQ_RB_STAT           = 0x8780,
    ROQ_RPTR_PRIMARY_mask    = 0x3ff << 0,
    ROQ_RPTR_PRIMARY_shift   = 0,
    ROQ_WPTR_PRIMARY_mask    = 0x3ff << 16,
    ROQ_WPTR_PRIMARY_shift   = 16,
    CP_ROQ_IB1_STAT          = 0x8784,
    ROQ_RPTR_INDIRECT1_mask  = 0x3ff << 0,
    ROQ_RPTR_INDIRECT1_shift = 0,
    ROQ_WPTR_INDIRECT1_mask  = 0x3ff << 16,
    ROQ_WPTR_INDIRECT1_shift = 16,
    CP_ROQ_IB2_STAT          = 0x8788,
    ROQ_RPTR_INDIRECT2_mask  = 0x3ff << 0,
    ROQ_RPTR_INDIRECT2_shift = 0,
    ROQ_WPTR_INDIRECT2_mask  = 0x3ff << 16,
    ROQ_WPTR_INDIRECT2_shift = 16,

    CP_MEQ_STAT    = 0x8794,
    MEQ_RPTR_mask  = 0x3ff << 0,
    MEQ_RPTR_shift = 0,
    MEQ_WPTR_mask  = 0x3ff << 16,
    MEQ_WPTR_shift = 16,

    CC_GC_SHADER_PIPE_CONFIG   = 0x8950,
    INACTIVE_QD_PIPES_mask     = 0xff << 8,
    INACTIVE_QD_PIPES_shift    = 8,
    R6XX_MAX_QD_PIPES          = 8,
    INACTIVE_SIMDS_mask        = 0xff << 16,
    INACTIVE_SIMDS_shift       = 16,
    R6XX_MAX_SIMDS             = 8,
    GC_USER_SHADER_PIPE_CONFIG = 0x8954,

    VC_ENHANCE                    = 0x9714,
    DB_DEBUG                      = 0x9830,
    PREZ_MUST_WAIT_FOR_POSTZ_DONE = 1 << 31,

    DB_WATERMARKS              = 0x00009838,
    DEPTH_FREE_mask            = 0x1f << 0,
    DEPTH_FREE_shift           = 0,
    DEPTH_FLUSH_mask           = 0x3f << 5,
    DEPTH_FLUSH_shift          = 5,
    FORCE_SUMMARIZE_mask       = 0x0f << 11,
    FORCE_SUMMARIZE_shift      = 11,
    DEPTH_PENDING_FREE_mask    = 0x1f << 15,
    DEPTH_PENDING_FREE_shift   = 15,
    DEPTH_CACHELINE_FREE_mask  = 0x1f << 20,
    DEPTH_CACHELINE_FREE_shift = 20,
    EARLY_Z_PANIC_DISABLE_bit  = 1 << 25,
    LATE_Z_PANIC_DISABLE_bit   = 1 << 26,
    RE_Z_PANIC_DISABLE_bit     = 1 << 27,
    DB_EXTRA_DEBUG_mask        = 0x0f << 28,
    DB_EXTRA_DEBUG_shift       = 28,

    CP_RB_BASE       = 0xc100,
    CP_RB_CNTL       = 0xc104,
    RB_BUFSZ_mask    = 0x3f << 0,
    CP_RB_WPTR       = 0xc114,
    RB_WPTR_mask     = 0xfffff << 0,
    RB_WPTR_shift    = 0,
    CP_RB_RPTR_WR    = 0xc108,
    RB_RPTR_WR_mask  = 0xfffff << 0,
    RB_RPTR_WR_shift = 0,

    CP_INT_STATUS                    = 0xc128,
    DISABLE_CNTX_SWITCH_INT_STAT_bit = 1 << 0,
    ENABLE_CNTX_SWITCH_INT_STAT_bit  = 1 << 1,
    SEM_SIGNAL_INT_STAT_bit          = 1 << 18,
    CNTX_BUSY_INT_STAT_bit           = 1 << 19,
    CNTX_EMPTY_INT_STAT_bit          = 1 << 20,
    WAITMEM_SEM_INT_STAT_bit         = 1 << 21,
    PRIV_INSTR_INT_STAT_bit          = 1 << 22,
    PRIV_REG_INT_STAT_bit            = 1 << 23,
    OPCODE_ERROR_INT_STAT_bit        = 1 << 24,
    SCRATCH_INT_STAT_bit             = 1 << 25,
    TIME_STAMP_INT_STAT_bit          = 1 << 26,
    RESERVED_BIT_ERROR_INT_STAT_bit  = 1 << 27,
    DMA_INT_STAT_bit                 = 1 << 28,
    IB2_INT_STAT_bit                 = 1 << 29,
    IB1_INT_STAT_bit                 = 1 << 30,
    RB_INT_STAT_bit                  = 1 << 31,

//  SX_ALPHA_TEST_CONTROL                                 = 0x00028410,
    ALPHA_FUNC__REF_NEVER        = 0,
    ALPHA_FUNC__REF_ALWAYS       = 7,
//  DB_SHADER_CONTROL                                     = 0x0002880c,
    Z_ORDER__EARLY_Z_THEN_LATE_Z = 2,
//  PA_SU_SC_MODE_CNTL                                    = 0x00028814,
//	POLY_MODE_mask                                    = 0x03 << 3,
    POLY_MODE__TRIANGLES         = 0,
    POLY_MODE__DUAL_MODE,
//	POLYMODE_FRONT_PTYPE_mask                         = 0x07 << 5,
    POLYMODE_PTYPE__POINTS = 0,
    POLYMODE_PTYPE__LINES,
    POLYMODE_PTYPE__TRIANGLES,
    PA_SC_AA_SAMPLE_LOCS_8S_WD1_M = 0x00028c20,
    DB_SRESULTS_COMPARE_STATE0 =
        0x00028d28, /* See autoregs: DB_SRESULTS_COMPARE_STATE1 */
//  DB_SRESULTS_COMPARE_STATE1                            = 0x00028d2c,
    DB_ALPHA_TO_MASK            = 0x00028d44,
    ALPHA_TO_MASK_ENABLE        = 1 << 0,
    ALPHA_TO_MASK_OFFSET0_mask  = 0x03 << 8,
    ALPHA_TO_MASK_OFFSET0_shift = 8,
    ALPHA_TO_MASK_OFFSET1_mask  = 0x03 << 10,
    ALPHA_TO_MASK_OFFSET1_shift = 10,
    ALPHA_TO_MASK_OFFSET2_mask  = 0x03 << 12,
    ALPHA_TO_MASK_OFFSET2_shift = 12,
    ALPHA_TO_MASK_OFFSET3_mask  = 0x03 << 14,
    ALPHA_TO_MASK_OFFSET3_shift = 14,

//  SQ_VTX_CONSTANT_WORD2_0                               = 0x00038008,
//    	SQ_VTX_CONSTANT_WORD2_0__DATA_FORMAT_mask         = 0x3f << 20,
    FMT_INVALID = 0,
    FMT_8,
    FMT_4_4,
    FMT_3_3_2,
    FMT_16 = 5,
    FMT_16_FLOAT,
    FMT_8_8,
    FMT_5_6_5,
    FMT_6_5_5,
    FMT_1_5_5_5,
    FMT_4_4_4_4,
    FMT_5_5_5_1,
    FMT_32,
    FMT_32_FLOAT,
    FMT_16_16,
    FMT_16_16_FLOAT = 16,
    FMT_8_24,
    FMT_8_24_FLOAT,
    FMT_24_8,
    FMT_24_8_FLOAT,
    FMT_10_11_11,
    FMT_10_11_11_FLOAT,
    FMT_11_11_10,
    FMT_11_11_10_FLOAT,
    FMT_2_10_10_10,
    FMT_8_8_8_8,
    FMT_10_10_10_2,
    FMT_X24_8_32_FLOAT,
    FMT_32_32,
    FMT_32_32_FLOAT,
    FMT_16_16_16_16,
    FMT_16_16_16_16_FLOAT = 32,
    FMT_32_32_32_32       = 34,
    FMT_32_32_32_32_FLOAT,
    FMT_1     = 37,
    FMT_GB_GR = 39,
    FMT_BG_RG,
    FMT_32_AS_8,
    FMT_32_AS_8_8,
    FMT_5_9_9_9_SHAREDEXP,
    FMT_8_8_8,
    FMT_16_16_16,
    FMT_16_16_16_FLOAT,
    FMT_32_32_32,
    FMT_32_32_32_FLOAT = 48,

//  High level register file lengths
    SQ_ALU_CONSTANT         = SQ_ALU_CONSTANT0_0, /* 256 PS, 256 VS */
    SQ_ALU_CONSTANT_ps_num  = 256,
    SQ_ALU_CONSTANT_vs_num  = 256,
    SQ_ALU_CONSTANT_all_num = 512,
    SQ_ALU_CONSTANT_offset  = 16,
    SQ_ALU_CONSTANT_ps      = 0,
    SQ_ALU_CONSTANT_vs      = SQ_ALU_CONSTANT_ps + SQ_ALU_CONSTANT_ps_num,
    SQ_TEX_RESOURCE =
        SQ_TEX_RESOURCE_WORD0_0, /* 160 PS, 160 VS, 16 FS, 160 GS */
    SQ_TEX_RESOURCE_ps_num  = 160,
    SQ_TEX_RESOURCE_vs_num  = 160,
    SQ_TEX_RESOURCE_fs_num  = 16,
    SQ_TEX_RESOURCE_gs_num  = 160,
    SQ_TEX_RESOURCE_all_num = 496,
    SQ_TEX_RESOURCE_offset  = 28,
    SQ_TEX_RESOURCE_ps      = 0,
    SQ_TEX_RESOURCE_vs      = SQ_TEX_RESOURCE_ps + SQ_TEX_RESOURCE_ps_num,
    SQ_TEX_RESOURCE_fs      = SQ_TEX_RESOURCE_vs + SQ_TEX_RESOURCE_vs_num,
    SQ_TEX_RESOURCE_gs      = SQ_TEX_RESOURCE_fs + SQ_TEX_RESOURCE_fs_num,
    SQ_VTX_RESOURCE =
        SQ_VTX_CONSTANT_WORD0_0, /* 160 PS, 160 VS, 16 FS, 160 GS */
    SQ_VTX_RESOURCE_ps_num     = 160,
    SQ_VTX_RESOURCE_vs_num     = 160,
    SQ_VTX_RESOURCE_fs_num     = 16,
    SQ_VTX_RESOURCE_gs_num     = 160,
    SQ_VTX_RESOURCE_all_num    = 496,
    SQ_VTX_RESOURCE_offset     = 28,
    SQ_VTX_RESOURCE_ps         = 0,
    SQ_VTX_RESOURCE_vs         = SQ_VTX_RESOURCE_ps + SQ_VTX_RESOURCE_ps_num,
    SQ_VTX_RESOURCE_fs         = SQ_VTX_RESOURCE_vs + SQ_VTX_RESOURCE_vs_num,
    SQ_VTX_RESOURCE_gs         = SQ_VTX_RESOURCE_fs + SQ_VTX_RESOURCE_fs_num,
    SQ_TEX_SAMPLER_WORD        = SQ_TEX_SAMPLER_WORD0_0, /* 18 per PS, VS, GS */
    SQ_TEX_SAMPLER_WORD_ps_num = 18,
    SQ_TEX_SAMPLER_WORD_vs_num = 18,
    SQ_TEX_SAMPLER_WORD_gs_num = 18,
    SQ_TEX_SAMPLER_WORD_all_num = 54,
    SQ_TEX_SAMPLER_WORD_offset  = 12,
    SQ_TEX_SAMPLER_WORD_ps      = 0,
    SQ_TEX_SAMPLER_WORD_vs =
        SQ_TEX_SAMPLER_WORD_ps + SQ_TEX_SAMPLER_WORD_ps_num,
    SQ_TEX_SAMPLER_WORD_gs =
        SQ_TEX_SAMPLER_WORD_vs + SQ_TEX_SAMPLER_WORD_vs_num,
    SQ_LOOP_CONST         = SQ_LOOP_CONST_0, /* 32 per PS, VS, GS */
    SQ_LOOP_CONST_ps_num  = 32,
    SQ_LOOP_CONST_vs_num  = 32,
    SQ_LOOP_CONST_gs_num  = 32,
    SQ_LOOP_CONST_all_num = 96,
    SQ_LOOP_CONST_offset  = 4,
    SQ_LOOP_CONST_ps      = 0,
    SQ_LOOP_CONST_vs      = SQ_LOOP_CONST_ps + SQ_LOOP_CONST_ps_num,
    SQ_LOOP_CONST_gs      = SQ_LOOP_CONST_vs + SQ_LOOP_CONST_vs_num,
    SQ_BOOL_CONST         = SQ_BOOL_CONST_0, /* 32 bits per PS, VS, GS */
    SQ_BOOL_CONST_ps_num  = 1,
    SQ_BOOL_CONST_vs_num  = 1,
    SQ_BOOL_CONST_gs_num  = 1,
    SQ_BOOL_CONST_all_num = 3,
    SQ_BOOL_CONST_offset  = 4,
    SQ_BOOL_CONST_ps      = 0,
    SQ_BOOL_CONST_vs      = SQ_BOOL_CONST_ps + SQ_BOOL_CONST_ps_num,
    SQ_BOOL_CONST_gs      = SQ_BOOL_CONST_vs + SQ_BOOL_CONST_vs_num,
};

#endif
