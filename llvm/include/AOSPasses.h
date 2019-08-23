#ifndef __AOS_PASSES_H
#define __AOS_PASSES_H

#include <vector>
#include <iostream>
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/LinkAllPasses.h"
#include <vector>
#include <iostream>

#define MIN_OPT 1
#define MAX_OPT 77

#define NONE 0

/* FUNCTION */
#define BASICAA 1
#define EARLY_CSE 2
#define INSTCOMBINE 3
#define INDVARS 4
#define LOOP_INSTSIMPLIFY 5
#define LOOP_IDIOM 6
#define LOOP_ROTATE 7
#define LOOP_UNROLL 8
#define REASSOCIATE 9
#define SIMPLIFYCFG 10
#define INFER_ADDRESS_SPACES 11
#define CONSTPROP 12
#define ALIGNMENT_FROM_ASSSUMPTIONS 13
#define SCCP 14
#define DCE 15
#define DIE 16
#define DSE 17
#define CALLSITE_SPLITTING 18
#define ADCE 19
#define BDCE 20
#define IRCE 21
#define LOOP_SINK 22
#define LOOP_PREDICATION 23
#define _GVN 24
#define LOOP_UNSWITCH 25
#define LOOP_UNROLL_AND_JAM 26
#define LOOP_REROLL 27
#define LOOP_VERSIONING_LICM 28
#define STRUCTURIZECFG 29
#define _GVN_HOIST 30
#define _GVN_SINK 31
#define MLDST_MOTION 32
#define NEWGVN 33
#define MEMCPYOPT 34
#define CONSTHOIST 35
#define SINK 36
#define LOWERATOMIC 37
#define LOWER_GUARD_INTRINSIC 38
#define MERGEICMPS 39
#define CORRELATED_PROPAGATION 40
#define LOWER_EXPECT 41
#define PARTIALLY_INLINE_LIBCALLS 42
#define LOOP_INTERCHANGE 43
#define PLACE_SAFEPOINTS 44
#define FLOAT2INT 45
#define LOOP_DISTRIBUTE 46
#define LOOP_LOAD_ELIM 47
#define LOOP_VERSIONING 48
#define LOOP_DATA_PREFETCH 49
#define INSTSIMPLIFY 50
#define AGGRESSIVE_INSTCOMBINE 51
#define LOWERINVOKE 52
#define INSTNAMER 53
#define LOWERSWITCH 54
#define BREAK_CRIT_EDGES 55
#define LCSSA 56
#define MEM2REG 57
#define LOOP_SINMPLIFY 58
#define SLP_VECTORIZER 59
#define LOAD_STORE_VECTORIZER 60
#define LAZY_VALUE_INFO 61
#define DA 62
#define COST_MODEL 63
#define DIVERGENCE 64
#define REGIONS 65
#define DOMTREE 66
#define SROA 67
#define FLATTENCFG 68
#define LOOP_REDUCE 69
#define DELINEARIZE 70
#define SEPARATE_CONST_OFFSET_FROM_GEP 71
#define LICM 72
#define LOOP_DELETION 73
#define NARY_REASSOCIATE 74
#define LOOP_VECTORIZE 75
#define TAILCALLELIM 76
#define JUMP_THREADING 77


/* MODULE */
#define CONSTMERGE 79
#define GLOBALOPT 80
#define INLINE 81
#define IPSCCP 82
#define PARTIAL_INLINER 83
#define REWRITE_STATEPOINTS_FOR_GCC 84
#define STRIP 85
#define SCALARIZER 86
#define STRIP_NONDEBUG 87
#define STRIP_DEBUG_DECLARE 88
#define STRIP_DEAD_DEBUG_INFO 89
#define	GLOBALDCE 90
#define ELIM_AVAIL_EXTERN 91
#define	PRUNE_EH 92
#define	DEADARGELIM 93
#define ARGPROMOTION 94
#define IPCONSTPROP 95
#define LOOP_EXTRACT 96
#define LOOP_EXTRACT_SINGLE 97
#define EXTRACT_BLOCKS 98
#define STRIP_DEAD_PROTOTYPES 99
#define MERGE_FUNC 100
#define BARRIER 101
#define CALLED_VALUE_PROPAGATION 102
#define CROSS_DSO_CFI 103
#define GLOBALSPLIT 104
#define METARENAMER 105

namespace aos {
void populatePassManager(llvm::legacy::PassManager*, llvm::legacy::FunctionPassManager*,
    std::vector<uint16_t>);

std::vector<uint16_t>& get_random_set(int size);
}


#endif /* __AOS_PASSES_H */
