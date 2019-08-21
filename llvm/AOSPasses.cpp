#include "AOSPasses.h"
#include <random>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

static std::vector<std::vector<uint16_t>> BEST10_SET = {
  {INSTCOMBINE, SIMPLIFYCFG, _GVN, INDVARS, LOOP_ROTATE, UNROLL_ALLOW_PARTIAL, LOOP_UNROLL,
    LOOP_ROTATE, LOOP_UNROLL, _GVN, INLINE, EARLY_CSE, BASICAA, REASSOCIATE, INSTCOMBINE},
  {SIMPLIFY_LIBCALLS, SIMPLIFYCFG, UNROLL_ALLOW_PARTIAL, INTERNALIZE, _GVN, INSTCOMBINE, INLINE,
    GLOBALOPT, SCALARREPL, LOOP_ROTATE, LOOP_UNROLL, LOOP_INSTSIMPLIFY},
  {_GVN, LOOP_ROTATE, INTERNALIZE, INLINE, LICM, TAILCALLELIM, INSTCOMBINE, BASICAA, INDVARS},
  {CODEGENPREPARE, LOOP_ROTATE, LOOP_IDIOM, LOOP_DELETION, _GVN},
  {LOOP_ROTATE, INLINE, SIMPLIFY_LIBCALLS, BASICAA, LICM, CONSTMERGE, INDVARS, UNROLL_ALLOW_PARTIAL,
    LOOP_UNROLL, REASSOCIATE, _GVN},
  {SIMPLIFYCFG, TAILCALLELIM, EARLY_CSE, LOOP_ROTATE, INTERNALIZE, PARTIAL_INLINER, INSTCOMBINE,
    INLINE, IPSCCP},
  {INTERNALIZE, INLINE, GLOBALOPT, EARLY_CSE, LICM, BASICAA, INDVARS, LOOP_REDUCE},
  {CODEGENPREPARE, _GVN, TAILCALLELIM, REASSOCIATE, BASICAA, INLINE, LOOP_ROTATE, INDVARS,
    REASSOCIATE},
  {SIMPLIFYCFG, TAILCALLELIM, INSTCOMBINE, EARLY_CSE},
  {EARLY_CSE, SIMPLIFYCFG, _GVN, INLINE, LOOP_REDUCE, LICM, INSTCOMBINE, _GVN, REASSOCIATE}
};

namespace aos {
void populatePassManager(llvm::legacy::PassManager* MPM, llvm::legacy::FunctionPassManager* FPM,
    std::vector<uint16_t> Passes) {
  for (unsigned int PassIndex = 0; PassIndex < Passes.size(); PassIndex++) {
    switch (Passes[PassIndex]) {
      case BASICAA:
        FPM->add(llvm::createBasicAAWrapperPass());
        break;
      case EARLY_CSE:
        FPM->add(llvm::createEarlyCSEPass());
        break;
      case _GVN: //**
        FPM->add(llvm::createNewGVNPass());
        break;
      case INSTCOMBINE: //**
        FPM->add(llvm::createInstructionCombiningPass());
        break;
      case INDVARS: //**
        FPM->add(llvm::createIndVarSimplifyPass());
        break;
      case LICM: //**
        FPM->add(llvm::createLICMPass());
        break;
      case LOOP_INSTSIMPLIFY:
        FPM->add(llvm::createLoopInstSimplifyPass());
        break;
      case LOOP_REDUCE:
        FPM->add(llvm::createLoopStrengthReducePass());
        break;
      case LOOP_IDIOM:
        FPM->add(llvm::createLoopIdiomPass());
        break;
      case LOOP_DELETION: //**
        FPM->add(llvm::createLoopDeletionPass());
        break;
      case LOOP_ROTATE:
        FPM->add(llvm::createLoopRotatePass());
        break;
      case LOOP_UNROLL: //**
        FPM->add(llvm::createSimpleLoopUnrollPass());
        break;
      case REASSOCIATE: //**
        FPM->add(llvm::createReassociatePass());
        break;
      case SIMPLIFYCFG: //**
        FPM->add(llvm::createCFGSimplificationPass());
        break;
      case TAILCALLELIM:
        FPM->add(llvm::createTailCallEliminationPass());
        break;
      case UNROLL_ALLOW_PARTIAL:
        // doesn't exist anymore
        break;
      case SIMPLIFY_LIBCALLS:
        // doesn't exist anymore
        break;
      case SCALARREPL:
        // doesn't exist anymore
        break;
      case CONSTPROP:
        FPM->add(llvm::createConstantPropagationPass());
        break;
      case ALIGNMENT_FROM_ASSSUMPTIONS:
        FPM->add(llvm::createAlignmentFromAssumptionsPass());
        break;
      case SCCP:
        FPM->add(llvm::createSCCPPass());
        break;
      case DCE: //**
        FPM->add(llvm::createDeadCodeEliminationPass());
        break;
      case DIE: //**
        FPM->add(llvm::createDeadInstEliminationPass());
        break;
      case DSE:
        FPM->add(llvm::createDeadStoreEliminationPass());
        break;
      case CALLSITE_SPLITTING:
        FPM->add(llvm::createCallSiteSplittingPass());
        break;
      case ADCE:
        FPM->add(llvm::createAggressiveDCEPass());
        break;
      case GUARD_WIDENING:
        FPM->add(llvm::createGuardWideningPass());
        break;
      case BDCE:
        FPM->add(llvm::createBitTrackingDCEPass());
        break;
      case IRCE:
        FPM->add(llvm::createInductiveRangeCheckEliminationPass());
        break;
      case LOOP_SINK:
        FPM->add(llvm::createLoopSinkPass());
        break;
      case LOOP_PREDICATION: //**
        FPM->add(llvm::createLoopPredicationPass());
        break;
      case LOOP_UNSWITCH: //**
        FPM->add(llvm::createLoopUnswitchPass());
        break;
      // case LOOP_UNROLL_AND_JAM:
      //   FPM->add(llvm::createLoopUnrollAndJamPass());
      //   break;
      case LOOP_REROLL:
        FPM->add(llvm::createLoopRerollPass());
        break;
      case LOOP_VERSIONING_LICM:
        FPM->add(llvm::createLoopVersioningLICMPass());
        break;
      case JUMP_THREADING:
        FPM->add(llvm::createJumpThreadingPass());
        break;
      case FLATTENCFG:
        FPM->add(llvm::createFlattenCFGPass());
        break;
      case STRUCTURIZECFG:
        FPM->add(llvm::createStructurizeCFGPass());
        break;
      case _GVN_HOIST:
        FPM->add(llvm::createGVNHoistPass());
        break;
      case _GVN_SINK:
        FPM->add(llvm::createGVNSinkPass());
        break;
      case MLDST_MOTION:
        FPM->add(llvm::createMergedLoadStoreMotionPass());
        break;
      case NEWGVN:
        FPM->add(llvm::createNewGVNPass());
        break;
      case MEMCPYOPT: //**
        FPM->add(llvm::createMemCpyOptPass());
        break;
      case CONSTHOIST:
        FPM->add(llvm::createConstantHoistingPass());
        break;
      case SINK:
        FPM->add(llvm::createSinkingPass());
        break;
      case LOWERATOMIC:
        FPM->add(llvm::createLowerAtomicPass());
        break;
      case LOWER_GUARD_INTRINSIC:
        FPM->add(llvm::createLowerGuardIntrinsicPass());
        break;
      case MERGEICMPS:
        FPM->add(llvm::createMergeICmpsPass());
        break;
      case CORRELATED_PROPAGATION:
        FPM->add(llvm::createCorrelatedValuePropagationPass());
        break;
      case LOWER_EXPECT:
        FPM->add(llvm::createLowerExpectIntrinsicPass());
        break;
      case PARTIALLY_INLINE_LIBCALLS:
        FPM->add(llvm::createPartiallyInlineLibCallsPass());
        break;
      case SEPARATE_CONST_OFFSET_FROM_GEP:
        FPM->add(llvm::createSeparateConstOffsetFromGEPPass());
        break;
      case SLSR:
        FPM->add(llvm::createStraightLineStrengthReducePass());
        break;
      case PLACE_SAFEPOINTS:
        FPM->add(llvm::createPlaceSafepointsPass());
        break;
      case FLOAT2INT:
        FPM->add(llvm::createFloat2IntPass());
        break;
      case NARY_REASSOCIATE:
        FPM->add(llvm::createNaryReassociatePass());
        break;
      case LOOP_DISTRIBUTE:
        FPM->add(llvm::createLoopDistributePass());
        break;
      case LOOP_LEAD_ELIM:
        FPM->add(llvm::createLoopLoadEliminationPass());
        break;
      case LOOP_VERSIONING:
        FPM->add(llvm::createLoopVersioningPass());
        break;
      case LOOP_DATA_PREFETCH:
        FPM->add(llvm::createLoopDataPrefetchPass());
        break;
      // case INSTSIMPLIFY:
      //   FPM->add(llvm::createInstSimplifyLegacyPass());
      //   break;
      // case AGGRESSIVE_INSTCOMBINE:
      //   FPM->add(llvm::createAggressiveInstCombinerPass());
      //   break;
      case LOWERINVOKE:
        FPM->add(llvm::createLowerInvokePass());
        break;
      case INSTNAMER:
        FPM->add(llvm::createInstructionNamerPass());
        break;
      case LOWERSWITCH:
        FPM->add(llvm::createLowerSwitchPass());
        break;
      case BREAK_CRIT_EDGES:
        FPM->add(llvm::createBreakCriticalEdgesPass());
        break;
      case LCSSA:
        FPM->add(llvm::createLCSSAPass());
        break;
      case MEM2REG:
        FPM->add(llvm::createPromoteMemoryToRegisterPass());
        break;
      case LOOP_SINMPLIFY:
        FPM->add(llvm::createLoopSimplifyPass());
        break;
      case LOOP_VECTORIZE:
        FPM->add(llvm::createLoopVectorizePass());
        break;
      case SLP_VECTORIZER:
        FPM->add(llvm::createSLPVectorizerPass());
        break;
      case LOAD_STORE_VECTORIZER:
        FPM->add(llvm::createLoadStoreVectorizerPass());
        break;
      case LAZY_VALUE_INFO:
        FPM->add(llvm::createLazyValueInfoPass());
        break;
      case DA:
        FPM->add(llvm::createDependenceAnalysisWrapperPass());
        break;
      case COST_MODEL:
        FPM->add(llvm::createCostModelAnalysisPass());
        break;
      case DELINEARIZE:
        FPM->add(llvm::createDelinearizationPass());
        break;
      case DIVERGENCE:
        FPM->add(llvm::createDivergenceAnalysisPass());
        break;
      case INSTCOUNT:
        FPM->add(llvm::createInstCountPass());
        break;
      case REGIONS:
        FPM->add(llvm::createRegionInfoPass());
        break;
      case DOMTREE:
        FPM->add(llvm::createPostDomTree());
        break;
      case CONSTMERGE:
        MPM->add(llvm::createConstantMergePass());
        break;
      case GLOBALOPT:
        MPM->add(llvm::createGlobalOptimizerPass());
        break;
      case INLINE:
        MPM->add(llvm::createFunctionInliningPass());
        break;
      case IPSCCP:
        MPM->add(llvm::createIPSCCPPass());
        break;
      case PARTIAL_INLINER:
        MPM->add(llvm::createPartialInliningPass());
        break;
      case REWRITE_STATEPOINTS_FOR_GCC:
        MPM->add(llvm::createRewriteStatepointsForGCLegacyPass());
        break;
      case STRIP:
        MPM->add(llvm::createStripSymbolsPass());
        break;
      case SCALARIZER:
        FPM->add(llvm::createScalarizerPass());
        break;
      case STRIP_NONDEBUG:
        MPM->add(llvm::createStripNonDebugSymbolsPass());
        break;
      case STRIP_DEBUG_DECLARE:
        MPM->add(llvm::createStripDebugDeclarePass());
        break;
      case STRIP_DEAD_DEBUG_INFO:
        MPM->add(llvm::createStripDeadDebugInfoPass());
        break;
      case GLOBALDCE:
        MPM->add(llvm::createGlobalDCEPass());
        break;
      case ELIM_AVAIL_EXTERN:
        MPM->add(llvm::createEliminateAvailableExternallyPass());
        break;
      case PRUNE_EH:
        MPM->add(llvm::createPruneEHPass());
        break;
      case DEADARGELIM:
        MPM->add(llvm::createDeadArgEliminationPass());
        break;
      case ARGPROMOTION:
        MPM->add(llvm::createArgumentPromotionPass());
        break;
      case IPCONSTPROP:
        MPM->add(llvm::createIPConstantPropagationPass());
        break;
      case LOOP_EXTRACT:
        MPM->add(llvm::createLoopExtractorPass());
        break;
      case LOOP_EXTRACT_SINGLE:
        MPM->add(llvm::createSingleLoopExtractorPass());
        break;
      case EXTRACT_BLOCKS:
        MPM->add(llvm::createBlockExtractorPass());
        break;
      case STRIP_DEAD_PROTOTYPES:
        MPM->add(llvm::createStripDeadPrototypesPass());
        break;
      case MERGE_FUNC:
        MPM->add(llvm::createMergeFunctionsPass());
        break;
      case BARRIER:
        MPM->add(llvm::createBarrierNoopPass());
        break;
      case CALLED_VALUE_PROPAGATION:
        MPM->add(llvm::createCalledValuePropagationPass());
        break;
      case CROSS_DSO_CFI:
        MPM->add(llvm::createCrossDSOCFIPass());
        break;
      case GLOBALSPLIT:
        MPM->add(llvm::createGlobalSplitPass());
        break;
      case NONE:
        break;
      case METARENAMER:
        MPM->add(llvm::createMetaRenamerPass());
        break;
      case PA_EVAL:
        FPM->add(llvm::createPAEvalPass());
        break;
      case INTERNALIZE:
        //MPM->add(llvm::createInternalizePass());
        break;
      case INFER_ADDRESS_SPACES:
        FPM->add(llvm::createInferAddressSpacesPass());
        break;
      case SPECULATIVE_EXECUTION:
        FPM->add(llvm::createSpeculativeExecutionPass());
        break;
      case CODEGENPREPARE:
        FPM->add(llvm::createCodeGenPreparePass());
        break;
      // case LOOP_GUARD_WIDENING:
      //   FPM->add(llvm::createLoopGuardWideningPass());
      //   break;
      case DIV_REM_PAIRS:
        FPM->add(llvm::createDivRemPairsPass());
        break;
      case LOOP_INTERCHANGE:
        FPM->add(llvm::createLoopInterchangePass());
        break;
      case SROA:
        FPM->add(llvm::createSROAPass());
        break;
      default:
        std::cerr << "Trying to use an invalid optimization pass!\n";
        exit(1);
        break;
    }
  }
}

std::vector<uint16_t>& get_random_set(void) {
    return BEST10_SET[0];
    //srand(time(0));  // Initialize random number generator.
    //return BEST10_SET[rand()%BEST10_SET.size()];
}

}
