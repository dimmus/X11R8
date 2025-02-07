/* $XTermId: VTparse.h,v 1.69 2019/02/10 23:34:21 tom Exp $ */

/*
 * Copyright 1996-2018,2019 by Thomas E. Dickey
 *
 *                         All Rights Reserved
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE ABOVE LISTED COPYRIGHT HOLDER(S) BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above copyright
 * holders shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization.
 */

#ifndef included_VTparse_h
#define included_VTparse_h 1

#include <xterm.h>

#ifndef Const
#  if defined(__STDC__) && !defined(__cplusplus)
#    define Const const
#  else
#    define Const /**/
#  endif
#endif

/*
 * PARSE_T has to be large enough to handle the number of cases enumerated here.
 */
typedef unsigned char PARSE_T;

extern Const PARSE_T ansi_table[];
extern Const PARSE_T cigtable[];
extern Const PARSE_T csi2_table[];
extern Const PARSE_T csi_ex_table[];
extern Const PARSE_T csi_quo_table[];
extern Const PARSE_T csi_sp_table[];
extern Const PARSE_T csi_table[];
extern Const PARSE_T dec2_table[];
extern Const PARSE_T dec3_table[];
extern Const PARSE_T dec_table[];
extern Const PARSE_T eigtable[];
extern Const PARSE_T esc_sp_table[];
extern Const PARSE_T esc_table[];
extern Const PARSE_T scrtable[];
extern Const PARSE_T scs96table[];
extern Const PARSE_T scstable[];
extern Const PARSE_T sos_table[];
extern Const PARSE_T csi_dec_dollar_table[];
extern Const PARSE_T csi_tick_table[];

#if OPT_DEC_RECTOPS
extern Const PARSE_T csi_dollar_table[];
extern Const PARSE_T csi_star_table[];
#endif /* OPT_DEC_LOCATOR */

#if OPT_VT52_MODE
extern Const PARSE_T vt52_table[];
extern Const PARSE_T vt52_esc_table[];
extern Const PARSE_T vt52_ignore_table[];
#endif

#if OPT_WIDE_CHARS
extern Const PARSE_T esc_pct_table[];
extern Const PARSE_T scs_amp_table[];
extern Const PARSE_T scs_pct_table[];
extern Const PARSE_T scs_2qt_table[];
#endif

#if OPT_XTERM_SGR
extern Const PARSE_T csi_hash_table[];
#endif

#define CASE_GROUND_STATE 0
#define CASE_IGNORE 1
#define CASE_BELL 2
#define CASE_BS 3
#define CASE_CR 4
#define CASE_ESC 5
#define CASE_VMOT 6
#define CASE_TAB 7
#define CASE_SI 8
#define CASE_SO 9
#define CASE_SCR_STATE 10
#define CASE_SCS0_STATE 11
#define CASE_SCS1_STATE 12
#define CASE_SCS2_STATE 13
#define CASE_SCS3_STATE 14
#define CASE_ESC_IGNORE 15
#define CASE_ESC_DIGIT 16
#define CASE_ESC_SEMI 17
#define CASE_DEC_STATE 18
#define CASE_ICH 19
#define CASE_CUU 20
#define CASE_CUD 21
#define CASE_CUF 22
#define CASE_CUB 23
#define CASE_CUP 24
#define CASE_ED 25
#define CASE_EL 26
#define CASE_IL 27
#define CASE_DL 28
#define CASE_DCH 29
#define CASE_DA1 30
#define CASE_TRACK_MOUSE 31
#define CASE_TBC 32
#define CASE_SET 33
#define CASE_RST 34
#define CASE_SGR 35
#define CASE_CPR 36
#define CASE_DECSTBM 37
#define CASE_DECREQTPARM 38
#define CASE_DECSET 39
#define CASE_DECRST 40
#define CASE_DECALN 41
#define CASE_GSETS 42
#define CASE_DECSC 43
#define CASE_DECRC 44
#define CASE_DECKPAM 45
#define CASE_DECKPNM 46
#define CASE_IND 47
#define CASE_NEL 48
#define CASE_HTS 49
#define CASE_RI 50
#define CASE_SS2 51
#define CASE_SS3 52
#define CASE_CSI_STATE 53
#define CASE_OSC 54
#define CASE_RIS 55
#define CASE_LS2 56
#define CASE_LS3 57
#define CASE_LS3R 58
#define CASE_LS2R 59
#define CASE_LS1R 60
#define CASE_PRINT 61
#define CASE_XTERM_SAVE 62
#define CASE_XTERM_RESTORE 63
#define CASE_DECID 64
#define CASE_HP_MEM_LOCK 65
#define CASE_HP_MEM_UNLOCK 66
#define CASE_HP_BUGGY_LL 67
#define CASE_HPA 68
#define CASE_VPA 69
#define CASE_XTERM_WINOPS 70
#define CASE_ECH 71
#define CASE_CHT 72
#define CASE_CPL 73
#define CASE_CNL 74
#define CASE_CBT 75
#define CASE_SU 76
#define CASE_SD 77
#define CASE_S7C1T 78
#define CASE_S8C1T 79
#define CASE_ESC_SP_STATE 80
#define CASE_ENQ 81
#define CASE_DECSCL 82
#define CASE_DECSCA 83
#define CASE_DECSED 84
#define CASE_DECSEL 85
#define CASE_DCS 86
#define CASE_PM 87
#define CASE_SOS 88
#define CASE_ST 89
#define CASE_APC 90
#define CASE_EPA 91
#define CASE_SPA 92
#define CASE_CSI_QUOTE_STATE 93
#define CASE_DSR 94
#define CASE_ANSI_LEVEL_1 95
#define CASE_ANSI_LEVEL_2 96
#define CASE_ANSI_LEVEL_3 97
#define CASE_MC 98
#define CASE_DEC2_STATE 99
#define CASE_DA2 100
#define CASE_DEC3_STATE 101
#define CASE_DECRPTUI 102
#define CASE_VT52_CUP 103
#define CASE_REP 104
#define CASE_CSI_EX_STATE 105
#define CASE_DECSTR 106
#define CASE_DECDHL 107
#define CASE_DECSWL 108
#define CASE_DECDWL 109
#define CASE_DEC_MC 110
#define CASE_ESC_PERCENT 111
#define CASE_UTF8 112
#define CASE_CSI_TICK_STATE 113
#define CASE_DECELR 114
#define CASE_DECRQLP 115
#define CASE_DECEFR 116
#define CASE_DECSLE 117
#define CASE_CSI_IGNORE 118
#define CASE_VT52_IGNORE 119
#define CASE_VT52_FINISH 120
#define CASE_CSI_DOLLAR_STATE 121
#define CASE_DECCRA 122
#define CASE_DECERA 123
#define CASE_DECFRA 124
#define CASE_DECSERA 125
#define CASE_DECSACE 126
#define CASE_DECCARA 127
#define CASE_DECRARA 128
#define CASE_CSI_STAR_STATE 129
#define CASE_SET_MOD_FKEYS 130
#define CASE_SET_MOD_FKEYS0 131
#define CASE_HIDE_POINTER 132
#define CASE_SCS1A_STATE 133
#define CASE_SCS2A_STATE 134
#define CASE_SCS3A_STATE 135
#define CASE_CSI_SPACE_STATE 136
#define CASE_DECSCUSR 137
#define CASE_XTERM_SM_TITLE 138
#define CASE_XTERM_RM_TITLE 139
#define CASE_DECSMBV 140
#define CASE_DECSWBV 141
#define CASE_DECLL 142
#define CASE_DECRQM 143
#define CASE_RQM 144
#define CASE_CSI_DEC_DOLLAR_STATE 145
#define CASE_SL 146
#define CASE_SR 147
#define CASE_DECDC 148
#define CASE_DECIC 149
#define CASE_DECBI 150
#define CASE_DECFI 151
#define CASE_DECRQCRA 152
#define CASE_HPR 153
#define CASE_VPR 154
#define CASE_ANSI_SC 155
#define CASE_ANSI_RC 156
#define CASE_ESC_COLON 157
#define CASE_SCS_PERCENT 158
#define CASE_GSETS_PERCENT 159
#define CASE_GRAPHICS_ATTRIBUTES 160
#define CASE_DECRQPSR 161
#define CASE_DECSCPP 162
#define CASE_DECSNLS 163
#define CASE_CSI_HASH_STATE 164
#define CASE_XTERM_PUSH_SGR 165
#define CASE_XTERM_REPORT_SGR 166
#define CASE_XTERM_POP_SGR 167
#define CASE_XTERM_CHECKSUM 168
#define CASE_GSETS3 169
#define CASE_GSETS5 170
#define CASE_SCS_DQUOTE 171
#define CASE_GSETS_DQUOTE 172
#define CASE_SCS_AMPRSND 173
#define CASE_GSETS_AMPRSND 174
#define CASE_REPORT_VERSION 175
#define CASE_XTERM_PUSH_COLORS 176
#define CASE_XTERM_REPORT_COLORS 177
#define CASE_XTERM_POP_COLORS 178
#define CASE_XTERM_SHIFT_ESCAPE 179
#define CASE_DECSSDT 180
#define CASE_DECSASD 181
#define CASE_XTERM_REPORT_MOD_FKEYS 182

#endif /* included_VTparse_h */
