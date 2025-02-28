#ifndef __R600_STATE_H__
#define __R600_STATE_H__

#include "xf86drm.h"

typedef int bool_t;

#define CLEAR(x) memset(&x, 0, sizeof(x))

/* Sequencer / thread handling */
typedef struct
{
    int ps_prio;
    int vs_prio;
    int gs_prio;
    int es_prio;
    int num_ps_gprs;
    int num_vs_gprs;
    int num_gs_gprs;
    int num_es_gprs;
    int num_temp_gprs;
    int num_ps_threads;
    int num_vs_threads;
    int num_gs_threads;
    int num_es_threads;
    int num_ps_stack_entries;
    int num_vs_stack_entries;
    int num_gs_stack_entries;
    int num_es_stack_entries;
} sq_config_t;

/* Color buffer / render target */
typedef struct
{
    int      id;
    int      w;
    int      h;
    uint64_t base;
    int      format;
    int      endian;
    int      array_mode;      // tiling
    int      number_type;
    int      read_size;
    int      comp_swap;
    int      tile_mode;
    int      blend_clamp;
    int      clear_color;
    int      blend_bypass;
    int      blend_float32;
    int      simple_float;
    int      round_mode;
    int      tile_compact;
    int      source_format;
    /* 2D related CB state */
    uint32_t               pmask;
    int                    rop;
    int                    blend_enable;
    uint32_t               blendcntl;
    struct radeon_bo      *bo;
    struct radeon_surface *surface;
} cb_config_t;

/* Depth buffer */
typedef struct
{
    int               w;
    int               h;
    uint64_t          base;
    int               format;
    int               read_size;
    int               array_mode;      // tiling
    int               tile_surface_en;
    int               tile_compact;
    int               zrange_precision;
    struct radeon_bo *bo;
} db_config_t;

/* Shader */
typedef struct
{
    uint64_t          shader_addr;
    uint32_t          shader_size;
    int               num_gprs;
    int               stack_size;
    int               dx10_clamp;
    int               prime_cache_pgm_en;
    int               prime_cache_on_draw;
    int               fetch_cache_lines;
    int               prime_cache_en;
    int               prime_cache_on_const;
    int               clamp_consts;
    int               export_mode;
    int               uncached_first_inst;
    struct radeon_bo *bo;
} shader_config_t;

/* Vertex buffer / vtx resource */
typedef struct
{
    int               id;
    uint64_t          vb_addr;
    uint32_t          vtx_num_entries;
    uint32_t          vtx_size_dw;
    int               clamp_x;
    int               format;
    int               num_format_all;
    int               format_comp_all;
    int               srf_mode_all;
    int               endian;
    int               mem_req_size;
    struct radeon_bo *bo;
} vtx_resource_t;

/* Texture resource */
typedef struct
{
    int                    id;
    int                    w;
    int                    h;
    int                    pitch;
    int                    depth;
    int                    dim;
    int                    tile_mode;
    int                    tile_type;
    int                    format;
    uint64_t               base;
    uint64_t               mip_base;
    uint32_t               size;
    int                    format_comp_x;
    int                    format_comp_y;
    int                    format_comp_z;
    int                    format_comp_w;
    int                    num_format_all;
    int                    srf_mode_all;
    int                    force_degamma;
    int                    endian;
    int                    request_size;
    int                    dst_sel_x;
    int                    dst_sel_y;
    int                    dst_sel_z;
    int                    dst_sel_w;
    int                    base_level;
    int                    last_level;
    int                    base_array;
    int                    last_array;
    int                    mpeg_clamp;
    int                    perf_modulation;
    int                    interlaced;
    struct radeon_bo      *bo;
    struct radeon_bo      *mip_bo;
    struct radeon_surface *surface;
} tex_resource_t;

/* Texture sampler */
typedef struct
{
    int id;
    /* Clamping */
    int clamp_x, clamp_y, clamp_z;
    int border_color;
    /* Filtering */
    int    xy_mag_filter, xy_min_filter;
    int    z_filter;
    int    mip_filter;
    bool_t high_precision_filter; /* ? */
    int    perf_mip;  /* ? 0-7 */
    int    perf_z;   /* ? 3 */
    /* LoD selection */
    int    min_lod, max_lod; /* 0-0x3ff */
    int    lod_bias;  /* 0-0xfff (signed?) */
    int    lod_bias2;  /* ? 0-0xfff (signed?) */
    bool_t lod_uses_minor_axis; /* ? */
    /* Other stuff */
    bool_t point_sampling_clamp; /* ? */
    bool_t tex_array_override; /* ? */
    bool_t mc_coord_truncate; /* ? */
    bool_t force_degamma;  /* ? */
    bool_t fetch_4;  /* ? */
    bool_t sample_is_pcf;  /* ? */
    bool_t type;   /* ? */
    int    depth_compare;  /* only depth textures? */
    int    chroma_key;
} tex_sampler_t;

/* Draw command */
typedef struct
{
    uint32_t prim_type;
    uint32_t vgt_draw_initiator;
    uint32_t index_type;
    uint32_t num_instances;
    uint32_t num_indices;
} draw_config_t;

#define BEGIN_BATCH(n)                                                 \
    do                                                                 \
    {                                                                  \
        radeon_ddx_cs_start(pScrn, (n), __FILE__, __func__, __LINE__); \
    }                                                                  \
    while (0)
#define END_BATCH()                                            \
    do                                                         \
    {                                                          \
        radeon_cs_end(info->cs, __FILE__, __func__, __LINE__); \
    }                                                          \
    while (0)
#define RELOC_BATCH(bo, rd, wd)                                      \
    do                                                               \
    {                                                                \
        int _ret;                                                    \
        _ret = radeon_cs_write_reloc(info->cs, (bo), (rd), (wd), 0); \
        if (_ret)                                                    \
            ErrorF("reloc emit failure %d (%s %d)\n",                \
                   _ret,                                             \
                   __func__,                                         \
                   __LINE__);                                        \
    }                                                                \
    while (0)
#define E32(dword)                                \
    do                                            \
    {                                             \
        radeon_cs_write_dword(info->cs, (dword)); \
    }                                             \
    while (0)

#define EFLOAT(val)     \
    do                  \
    {                   \
        union {         \
            float    f; \
            uint32_t d; \
        } a;            \
        a.f = (val);    \
        E32(a.d);       \
    }                   \
    while (0)

#define PACK3(cmd, num)                        \
    do                                         \
    {                                          \
        E32(RADEON_CP_PACKET3 | ((cmd) << 8) | \
            ((((num) - 1) & 0x3fff) << 16));   \
    }                                          \
    while (0)

/* write num registers, start at reg */
/* If register falls in a special area, special commands are issued */
#define PACK0(reg, num)                                                        \
    do                                                                         \
    {                                                                          \
        if ((reg) >= SET_CONFIG_REG_offset && (reg) < SET_CONFIG_REG_end)      \
        {                                                                      \
            PACK3(IT_SET_CONFIG_REG, (num) + 1);                               \
            E32(((reg) - SET_CONFIG_REG_offset) >> 2);                         \
        }                                                                      \
        else if ((reg) >= SET_CONTEXT_REG_offset &&                            \
                 (reg) < SET_CONTEXT_REG_end)                                  \
        {                                                                      \
            PACK3(IT_SET_CONTEXT_REG, (num) + 1);                              \
            E32(((reg) - SET_CONTEXT_REG_offset) >> 2);                        \
        }                                                                      \
        else if ((reg) >= SET_ALU_CONST_offset && (reg) < SET_ALU_CONST_end)   \
        {                                                                      \
            PACK3(IT_SET_ALU_CONST, (num) + 1);                                \
            E32(((reg) - SET_ALU_CONST_offset) >> 2);                          \
        }                                                                      \
        else if ((reg) >= SET_RESOURCE_offset && (reg) < SET_RESOURCE_end)     \
        {                                                                      \
            PACK3(IT_SET_RESOURCE, num + 1);                                   \
            E32(((reg) - SET_RESOURCE_offset) >> 2);                           \
        }                                                                      \
        else if ((reg) >= SET_SAMPLER_offset && (reg) < SET_SAMPLER_end)       \
        {                                                                      \
            PACK3(IT_SET_SAMPLER, (num) + 1);                                  \
            E32((reg - SET_SAMPLER_offset) >> 2);                              \
        }                                                                      \
        else if ((reg) >= SET_CTL_CONST_offset && (reg) < SET_CTL_CONST_end)   \
        {                                                                      \
            PACK3(IT_SET_CTL_CONST, (num) + 1);                                \
            E32(((reg) - SET_CTL_CONST_offset) >> 2);                          \
        }                                                                      \
        else if ((reg) >= SET_LOOP_CONST_offset && (reg) < SET_LOOP_CONST_end) \
        {                                                                      \
            PACK3(IT_SET_LOOP_CONST, (num) + 1);                               \
            E32(((reg) - SET_LOOP_CONST_offset) >> 2);                         \
        }                                                                      \
        else if ((reg) >= SET_BOOL_CONST_offset && (reg) < SET_BOOL_CONST_end) \
        {                                                                      \
            PACK3(IT_SET_BOOL_CONST, (num) + 1);                               \
            E32(((reg) - SET_BOOL_CONST_offset) >> 2);                         \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            E32(CP_PACKET0((reg), (num) - 1));                                 \
        }                                                                      \
    }                                                                          \
    while (0)

/* write a single register */
#define EREG(reg, val)   \
    do                   \
    {                    \
        PACK0((reg), 1); \
        E32((val));      \
    }                    \
    while (0)

void R600CPFlushIndirect(ScrnInfoPtr pScrn);
void R600IBDiscard(ScrnInfoPtr pScrn);

void r600_wait_3d_idle_clean(ScrnInfoPtr pScrn);
void r600_wait_3d_idle(ScrnInfoPtr pScrn);
void r600_start_3d(ScrnInfoPtr pScrn);
void r600_set_blend_color(ScrnInfoPtr pScrn, float *color);
void r600_set_render_target(ScrnInfoPtr  pScrn,
                            cb_config_t *cb_conf,
                            uint32_t     domain);
void r600_cp_wait_vline_sync(ScrnInfoPtr pScrn,
                             PixmapPtr   pPix,
                             xf86CrtcPtr crtc,
                             int         start,
                             int         stop);
void r600_set_spi(ScrnInfoPtr pScrn, int vs_export_count, int num_interp);
void
r600_fs_setup(ScrnInfoPtr pScrn, shader_config_t *fs_conf, uint32_t domain);
void
r600_vs_setup(ScrnInfoPtr pScrn, shader_config_t *vs_conf, uint32_t domain);
void
r600_ps_setup(ScrnInfoPtr pScrn, shader_config_t *ps_conf, uint32_t domain);
void
r600_set_alu_consts(ScrnInfoPtr pScrn, int offset, int count, float *const_buf);
void r600_set_bool_consts(ScrnInfoPtr pScrn, int offset, uint32_t val);
void r600_set_tex_resource(ScrnInfoPtr     pScrn,
                           tex_resource_t *tex_res,
                           uint32_t        domain);
void r600_set_tex_sampler(ScrnInfoPtr pScrn, tex_sampler_t *s);
void r600_set_screen_scissor(ScrnInfoPtr pScrn, int x1, int y1, int x2, int y2);
void r600_set_vport_scissor(ScrnInfoPtr pScrn,
                            int         id,
                            int         x1,
                            int         y1,
                            int         x2,
                            int         y2);
void
r600_set_generic_scissor(ScrnInfoPtr pScrn, int x1, int y1, int x2, int y2);
void r600_set_window_scissor(ScrnInfoPtr pScrn, int x1, int y1, int x2, int y2);
void
r600_set_clip_rect(ScrnInfoPtr pScrn, int id, int x1, int y1, int x2, int y2);
void r600_set_default_state(ScrnInfoPtr pScrn);
void
r600_draw_immd(ScrnInfoPtr pScrn, draw_config_t *draw_conf, uint32_t *indices);
void r600_draw_auto(ScrnInfoPtr pScrn, draw_config_t *draw_conf);

void r600_finish_op(ScrnInfoPtr pScrn, int vtx_size);

Bool R600SetAccelState(ScrnInfoPtr               pScrn,
                       struct r600_accel_object *src0,
                       struct r600_accel_object *src1,
                       struct r600_accel_object *dst,
                       uint32_t                  vs_offset,
                       uint32_t                  ps_offset,
                       int                       rop,
                       Pixel                     planemask);

extern Bool  RADEONPrepareAccess_CS(PixmapPtr pPix, int index);
extern void  RADEONFinishAccess_CS(PixmapPtr pPix, int index);
extern void *RADEONEXACreatePixmap2(ScreenPtr pScreen,
                                    int       width,
                                    int       height,
                                    int       depth,
                                    int       usage_hint,
                                    int       bitsPerPixel,
                                    int      *new_pitch);
extern void  RADEONEXADestroyPixmap(ScreenPtr pScreen, void *driverPriv);
extern Bool  RADEONEXAPixmapIsOffscreen(PixmapPtr pPix);
extern Bool  RADEONEXASharePixmapBacking(PixmapPtr ppix,
                                         ScreenPtr secondary,
                                         void    **handle_p);
extern Bool  RADEONEXASetSharedPixmapBacking(PixmapPtr ppix, void *handle);
#endif
