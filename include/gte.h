/* PS1 GTE (COP2) macros in the style of the PSY-Q SDK's inline GTE header.
 *
 * The game called the geometry coprocessor through inline macros like these (gte_ldv0,
 * gte_rtps, gte_stsxy...), so its compiled code holds fixed lwc2/swc2/mtc2/mfc2/cfc2/ctc2
 * sequences and two nops before every GTE command. This file is the only C header allowed
 * to hold inline asm (tools/hooks/pre-commit exempts it). Written from the COP2 encodings:
 *   command word = 0x4A000000 | sf << 19 | mx << 17 | v << 15 | cv << 13 | lm << 10 | opcode,
 *   with the "fake" command number in bits 20..24 (see include/gte_macros.inc).
 * GTE data registers: $0-$5 VXY0..VZ2, $6 RGBC, $7 OTZ, $8 IR0, $9-$11 IR1..IR3,
 * $12-$14 SXY0..SXY2, $16-$19 SZ0..SZ3, $20-$22 RGB0..RGB2, $24 MAC0.
 * Control registers: $0-$4 rotation matrix, $5-$7 translation, $31 FLAG.
 * Scratch CPU registers $12-$14 (t4-t6) are declared clobbered where used.
 */
#ifndef GTE_H
#define GTE_H

#if !defined(M2CTX) && !defined(PERMUTER)

/* ---- commands: two nops cover the previous GTE access, then the command word ---- */
#define gte_cmd_(word) __asm__ volatile("nop\n\tnop\n\t.word " #word)

#define gte_rtps()   gte_cmd_(0x4A180001)
#define gte_rtpt()   gte_cmd_(0x4A280030)
#define gte_nclip()  gte_cmd_(0x4B400006)
#define gte_avsz3()  gte_cmd_(0x4B58002D)
#define gte_avsz4()  gte_cmd_(0x4B68002E)
#define gte_ncs()    gte_cmd_(0x4AC8041E)
#define gte_nct()    gte_cmd_(0x4AD80420)
#define gte_ncds()   gte_cmd_(0x4AE80413)
#define gte_ncdt()   gte_cmd_(0x4AF80416)
#define gte_nccs()   gte_cmd_(0x4B08041B)
#define gte_ncct()   gte_cmd_(0x4B18043F)
#define gte_cdp()    gte_cmd_(0x4B280414)
#define gte_cc()     gte_cmd_(0x4B38041C)
#define gte_dpcs()   gte_cmd_(0x4A780010)
#define gte_dpct()   gte_cmd_(0x4AF8002A)
#define gte_dpcl()   gte_cmd_(0x4A680029)
#define gte_intpl()  gte_cmd_(0x4A980011)
#define gte_sqr0()   gte_cmd_(0x4AA00428)
#define gte_sqr12()  gte_cmd_(0x4AA80428)
#define gte_op0()    gte_cmd_(0x4B70000C)
#define gte_op12()   gte_cmd_(0x4B78000C)
#define gte_gpf0()   gte_cmd_(0x4B90003D)
#define gte_gpf12()  gte_cmd_(0x4B98003D)
#define gte_gpl0()   gte_cmd_(0x4BA0003E)
#define gte_gpl12()  gte_cmd_(0x4BA8003E)
/* mvmva: rotation matrix (mx 0), light matrix (mx 1), color matrix (mx 2) */
#define gte_rtv0()   gte_cmd_(0x4A486012)
#define gte_rtv1()   gte_cmd_(0x4A48E012)
#define gte_rtv2()   gte_cmd_(0x4A496012)
#define gte_rtir()   gte_cmd_(0x4A49E012)
#define gte_rtir_sf0() gte_cmd_(0x4A41E012)
#define gte_rtv0tr() gte_cmd_(0x4A480012)
#define gte_rtv1tr() gte_cmd_(0x4A488012)
#define gte_rtv2tr() gte_cmd_(0x4A490012)
#define gte_rtirtr() gte_cmd_(0x4A498012)
#define gte_llv0()   gte_cmd_(0x4A4A6012)
#define gte_llir()   gte_cmd_(0x4A4BE012)
#define gte_lcv0()   gte_cmd_(0x4A4C6012)
#define gte_lcir()   gte_cmd_(0x4A4DE012)

/* ---- loads into GTE data registers ---- */
#define gte_ldv0(r0) __asm__ volatile( \
    "lwc2\t$0, 0(%0)\n\tlwc2\t$1, 4(%0)" : : "r"(r0))
#define gte_ldv1(r0) __asm__ volatile( \
    "lwc2\t$2, 0(%0)\n\tlwc2\t$3, 4(%0)" : : "r"(r0))
#define gte_ldv2(r0) __asm__ volatile( \
    "lwc2\t$4, 0(%0)\n\tlwc2\t$5, 4(%0)" : : "r"(r0))
#define gte_ldv3(r0, r1, r2) __asm__ volatile( \
    "lwc2\t$0, 0(%0)\n\tlwc2\t$1, 4(%0)\n\t" \
    "lwc2\t$2, 0(%1)\n\tlwc2\t$3, 4(%1)\n\t" \
    "lwc2\t$4, 0(%2)\n\tlwc2\t$5, 4(%2)" : : "r"(r0), "r"(r1), "r"(r2))
/* three SVECTORs in a row */
#define gte_ldv3c(r0) __asm__ volatile( \
    "lwc2\t$0, 0(%0)\n\tlwc2\t$1, 4(%0)\n\t" \
    "lwc2\t$2, 8(%0)\n\tlwc2\t$3, 12(%0)\n\t" \
    "lwc2\t$4, 16(%0)\n\tlwc2\t$5, 20(%0)" : : "r"(r0))
#define gte_ldrgb(r0) __asm__ volatile( \
    "lwc2\t$6, 0(%0)" : : "r"(r0))
/* RGB0..RGB2 from three CVECTORs, RGBC (code byte) from the last one */
#define gte_ldrgb3(r0, r1, r2) __asm__ volatile( \
    "lwc2\t$20, 0(%0)\n\tlwc2\t$21, 0(%1)\n\t" \
    "lwc2\t$22, 0(%2)\n\tlwc2\t$6, 0(%2)" : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldrgb3c(r0) __asm__ volatile( \
    "lwc2\t$20, 0(%0)\n\tlwc2\t$21, 4(%0)\n\t" \
    "lwc2\t$22, 8(%0)\n\tlwc2\t$6, 8(%0)" : : "r"(r0))
#define gte_ldsxy3(r0, r1, r2) __asm__ volatile( \
    "lwc2\t$12, 0(%0)\n\tlwc2\t$13, 0(%1)\n\tlwc2\t$14, 0(%2)" \
    : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldsz3(r0, r1, r2) __asm__ volatile( \
    "mtc2\t%0, $17\n\tmtc2\t%1, $18\n\tmtc2\t%2, $19" \
    : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldsz4(r0, r1, r2, r3) __asm__ volatile( \
    "mtc2\t%0, $16\n\tmtc2\t%1, $17\n\tmtc2\t%2, $18\n\tmtc2\t%3, $19" \
    : : "r"(r0), "r"(r1), "r"(r2), "r"(r3))
#define gte_lddp(r0) __asm__ volatile( \
    "mtc2\t%0, $8" : : "r"(r0))
/* one column of a MATRIX (s16 m[3][3]) into IR1..IR3 */
#define gte_ldclmv(r0) __asm__ volatile( \
    "lhu\t$12, 0(%0)\n\tlhu\t$13, 6(%0)\n\tlhu\t$14, 12(%0)\n\t" \
    "mtc2\t$12, $9\n\tmtc2\t$13, $10\n\tmtc2\t$14, $11" \
    : : "r"(r0) : "$12", "$13", "$14")

/* ---- stores from GTE data registers ---- */
#define gte_stsxy(r0) __asm__ volatile( \
    "swc2\t$14, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy0(r0) __asm__ volatile( \
    "swc2\t$12, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy1(r0) __asm__ volatile( \
    "swc2\t$13, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy2(r0) gte_stsxy(r0)
#define gte_stsxy3(r0, r1, r2) __asm__ volatile( \
    "swc2\t$12, 0(%0)\n\tswc2\t$13, 0(%1)\n\tswc2\t$14, 0(%2)" \
    : : "r"(r0), "r"(r1), "r"(r2) : "memory")
/* SXY0..SXY2 straight into a primitive's first three vertices */
#define gte_stsxy3_prim_(r0, o1, o2) __asm__ volatile( \
    "swc2\t$12, 8(%0)\n\tswc2\t$13, " #o1 "(%0)\n\tswc2\t$14, " #o2 "(%0)" \
    : : "r"(r0) : "memory")
#define gte_stsxy3_f3(r0)  gte_stsxy3_prim_(r0, 12, 16)
#define gte_stsxy3_g3(r0)  gte_stsxy3_prim_(r0, 16, 24)
#define gte_stsxy3_ft3(r0) gte_stsxy3_prim_(r0, 16, 24)
#define gte_stsxy3_gt3(r0) gte_stsxy3_prim_(r0, 20, 32)
#define gte_stsxy3_f4(r0)  gte_stsxy3_prim_(r0, 12, 16)
#define gte_stsxy3_g4(r0)  gte_stsxy3_prim_(r0, 16, 24)
#define gte_stsxy3_ft4(r0) gte_stsxy3_prim_(r0, 16, 24)
#define gte_stsxy3_gt4(r0) gte_stsxy3_prim_(r0, 20, 32)
#define gte_stotz(r0) __asm__ volatile( \
    "swc2\t$7, 0(%0)" : : "r"(r0) : "memory")
#define gte_stdp(r0) __asm__ volatile( \
    "swc2\t$8, 0(%0)" : : "r"(r0) : "memory")
#define gte_stopz(r0) __asm__ volatile( \
    "swc2\t$24, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsz(r0) __asm__ volatile( \
    "swc2\t$19, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsz3(r0, r1, r2) __asm__ volatile( \
    "swc2\t$17, 0(%0)\n\tswc2\t$18, 0(%1)\n\tswc2\t$19, 0(%2)" \
    : : "r"(r0), "r"(r1), "r"(r2) : "memory")
#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile( \
    "swc2\t$16, 0(%0)\n\tswc2\t$17, 0(%1)\n\tswc2\t$18, 0(%2)\n\tswc2\t$19, 0(%3)" \
    : : "r"(r0), "r"(r1), "r"(r2), "r"(r3) : "memory")
#define gte_strgb(r0) __asm__ volatile( \
    "swc2\t$22, 0(%0)" : : "r"(r0) : "memory")
#define gte_strgb3(r0, r1, r2) __asm__ volatile( \
    "swc2\t$20, 0(%0)\n\tswc2\t$21, 0(%1)\n\tswc2\t$22, 0(%2)" \
    : : "r"(r0), "r"(r1), "r"(r2) : "memory")
/* RGB0..RGB2 into a gouraud primitive's three colors */
#define gte_strgb3_g3(r0) __asm__ volatile( \
    "swc2\t$20, 4(%0)\n\tswc2\t$21, 12(%0)\n\tswc2\t$22, 20(%0)" \
    : : "r"(r0) : "memory")
#define gte_strgb3_gt3(r0) __asm__ volatile( \
    "swc2\t$20, 4(%0)\n\tswc2\t$21, 16(%0)\n\tswc2\t$22, 28(%0)" \
    : : "r"(r0) : "memory")
#define gte_strgb3_g4 gte_strgb3_g3
#define gte_strgb3_gt4 gte_strgb3_gt3
/* FLAG register; _4 keeps only bit 18 (SZ3 or OTZ saturated, the "too far" test) */
#define gte_stflg(r0) __asm__ volatile( \
    "cfc2\t$12, $31\n\tnop\n\tsw\t$12, 0(%0)" : : "r"(r0) : "$12", "memory")
#define gte_stflg_4(r0) __asm__ volatile( \
    "cfc2\t$12, $31\n\taddi\t$13, $0, 4\n\tsll\t$13, $13, 16\n\t" \
    "and\t$12, $12, $13\n\tsw\t$12, 0(%0)" : : "r"(r0) : "$12", "$13", "memory")
/* IR1..IR3 back into one column of a MATRIX */
#define gte_stclmv(r0) __asm__ volatile( \
    "mfc2\t$12, $9\n\tmfc2\t$13, $10\n\tmfc2\t$14, $11\n\t" \
    "sh\t$12, 0(%0)\n\tsh\t$13, 6(%0)\n\tsh\t$14, 12(%0)" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

/* ---- control registers: MATRIX is s16 m[3][3] (0x12 bytes, padded to 0x14) then s32 t[3] ---- */
#define gte_SetRotMatrix(r0) __asm__ volatile( \
    "lw\t$12, 0(%0)\n\tlw\t$13, 4(%0)\n\tctc2\t$12, $0\n\tctc2\t$13, $1\n\t" \
    "lw\t$12, 8(%0)\n\tlw\t$13, 12(%0)\n\tlw\t$14, 16(%0)\n\t" \
    "ctc2\t$12, $2\n\tctc2\t$13, $3\n\tctc2\t$14, $4" \
    : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile( \
    "lw\t$12, 20(%0)\n\tlw\t$13, 24(%0)\n\tctc2\t$12, $5\n\t" \
    "lw\t$14, 28(%0)\n\tctc2\t$13, $6\n\tctc2\t$14, $7" \
    : : "r"(r0) : "$12", "$13", "$14")
#define gte_ReadRotMatrix(r0) __asm__ volatile( \
    "cfc2\t$12, $0\n\tcfc2\t$13, $1\n\tsw\t$12, 0(%0)\n\tsw\t$13, 4(%0)\n\t" \
    "cfc2\t$12, $2\n\tcfc2\t$13, $3\n\tcfc2\t$14, $4\n\t" \
    "sw\t$12, 8(%0)\n\tsw\t$13, 12(%0)\n\tsw\t$14, 16(%0)\n\t" \
    "cfc2\t$12, $5\n\tcfc2\t$13, $6\n\tcfc2\t$14, $7\n\t" \
    "sw\t$12, 20(%0)\n\tsw\t$13, 24(%0)\n\tsw\t$14, 28(%0)" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")
/* r3 = r1 * r2, column by column; r2 and r3 are evaluated once per column */
#define gte_MulMatrix0(r1, r2, r3) do { \
    gte_SetRotMatrix(r1); \
    gte_ldclmv(r2); gte_rtir(); gte_stclmv(r3); \
    gte_ldclmv((s8 *)(r2) + 2); gte_rtir(); gte_stclmv((s8 *)(r3) + 2); \
    gte_ldclmv((s8 *)(r2) + 4); gte_rtir(); gte_stclmv((s8 *)(r3) + 4); \
} while (0)

#else /* m2c and the permuter see no-ops */

#define gte_cmd_(word)
#define gte_rtps()
#define gte_rtpt()
#define gte_nclip()
#define gte_avsz3()
#define gte_avsz4()
#define gte_ncs()
#define gte_nct()
#define gte_ncds()
#define gte_ncdt()
#define gte_nccs()
#define gte_ncct()
#define gte_cdp()
#define gte_cc()
#define gte_dpcs()
#define gte_dpct()
#define gte_dpcl()
#define gte_intpl()
#define gte_sqr0()
#define gte_sqr12()
#define gte_op0()
#define gte_op12()
#define gte_gpf0()
#define gte_gpf12()
#define gte_gpl0()
#define gte_gpl12()
#define gte_rtv0()
#define gte_rtv1()
#define gte_rtv2()
#define gte_rtir()
#define gte_rtir_sf0()
#define gte_rtv0tr()
#define gte_rtv1tr()
#define gte_rtv2tr()
#define gte_rtirtr()
#define gte_llv0()
#define gte_llir()
#define gte_lcv0()
#define gte_lcir()
#define gte_ldv0(r0)
#define gte_ldv1(r0)
#define gte_ldv2(r0)
#define gte_ldv3(r0, r1, r2)
#define gte_ldv3c(r0)
#define gte_ldrgb(r0)
#define gte_ldrgb3(r0, r1, r2)
#define gte_ldrgb3c(r0)
#define gte_ldsxy3(r0, r1, r2)
#define gte_ldsz3(r0, r1, r2)
#define gte_ldsz4(r0, r1, r2, r3)
#define gte_lddp(r0)
#define gte_ldclmv(r0)
#define gte_stsxy(r0)
#define gte_stsxy0(r0)
#define gte_stsxy1(r0)
#define gte_stsxy2(r0)
#define gte_stsxy3(r0, r1, r2)
#define gte_stsxy3_prim_(r0, o1, o2)
#define gte_stsxy3_f3(r0)
#define gte_stsxy3_g3(r0)
#define gte_stsxy3_ft3(r0)
#define gte_stsxy3_gt3(r0)
#define gte_stsxy3_f4(r0)
#define gte_stsxy3_g4(r0)
#define gte_stsxy3_ft4(r0)
#define gte_stsxy3_gt4(r0)
#define gte_stotz(r0)
#define gte_stdp(r0)
#define gte_stopz(r0)
#define gte_stsz(r0)
#define gte_stsz3(r0, r1, r2)
#define gte_stsz4(r0, r1, r2, r3)
#define gte_strgb(r0)
#define gte_strgb3(r0, r1, r2)
#define gte_strgb3_g3(r0)
#define gte_strgb3_gt3(r0)
#define gte_strgb3_g4
#define gte_strgb3_gt4
#define gte_stflg(r0)
#define gte_stflg_4(r0)
#define gte_stclmv(r0)
#define gte_SetRotMatrix(r0)
#define gte_SetTransMatrix(r0)
#define gte_ReadRotMatrix(r0)
#define gte_MulMatrix0(r1, r2, r3)

#endif /* !defined(M2CTX) && !defined(PERMUTER) */

#endif /* GTE_H */
