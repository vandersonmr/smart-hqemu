#include "llvm/IR/Module.h"

inline std::string encode(llvm::Function *Func) {
  std::string DNA;
  for (auto &BB : *Func) {
    // k marks a BB start
    DNA.push_back('k');
    for (auto &Inst : BB) {
      switch(Inst.getOpcode()) {
        case llvm::Instruction::Br:
          DNA.push_back('A');
          break;
        case llvm::Instruction::Switch:
          DNA.push_back('B');
          break;
        case llvm::Instruction::IndirectBr:
          DNA.push_back('C');
          break;
        case llvm::Instruction::Ret:
          DNA.push_back('D');
          break;
        case llvm::Instruction::Invoke:
          DNA.push_back('E');
          break;
        case llvm::Instruction::Resume:
          DNA.push_back('F');
          break;
        case llvm::Instruction::Unreachable:
          DNA.push_back('G');
          break;
        case llvm::Instruction::Add:
          DNA.push_back('H');
          break;
        case llvm::Instruction::Sub:
          DNA.push_back('I');
          break;
        case llvm::Instruction::Mul:
          DNA.push_back('J');
          break;
        case llvm::Instruction::UDiv:
          DNA.push_back('K');
          break;
        case llvm::Instruction::SDiv:
          DNA.push_back('L');
          break;
        case llvm::Instruction::URem:
          DNA.push_back('M');
          break;
        case llvm::Instruction::SRem:
          DNA.push_back('N');
          break;
        case llvm::Instruction::FAdd:
          DNA.push_back('O');
          break;
        case llvm::Instruction::FSub:
          DNA.push_back('P');
          break;
        case llvm::Instruction::FMul:
          DNA.push_back('Q');
          break;
        case llvm::Instruction::FDiv:
          DNA.push_back('R');
          break;
        case llvm::Instruction::FRem:
          DNA.push_back('S');
          break;
        case llvm::Instruction::Shl:
          DNA.push_back('T');
          break;
        case llvm::Instruction::LShr:
          DNA.push_back('U');
          break;
        case llvm::Instruction::AShr:
          DNA.push_back('V');
          break;
        case llvm::Instruction::And:
          DNA.push_back('X');
          break;
        case llvm::Instruction::Or:
          DNA.push_back('W');
          break;
        case llvm::Instruction::Xor:
          DNA.push_back('Y');
          break;
        case llvm::Instruction::ExtractElement:
          DNA.push_back('Z');
          break;
        case llvm::Instruction::InsertElement:
          DNA.push_back('a');
          break;
        case llvm::Instruction::ShuffleVector:
          DNA.push_back('b');
          break;
        case llvm::Instruction::ExtractValue:
          DNA.push_back('c');
          break;
        case llvm::Instruction::InsertValue:
          DNA.push_back('d');
          break;
        case llvm::Instruction::Load:
          DNA.push_back('e');
          break;
        case llvm::Instruction::Store:
          DNA.push_back('f');
          break;
        case llvm::Instruction::Alloca:
          DNA.push_back('g');
          break;
        case llvm::Instruction::Fence:
          DNA.push_back('h');
          break;
        case llvm::Instruction::AtomicRMW:
          DNA.push_back('i');
          break;
        case llvm::Instruction::AtomicCmpXchg:
          DNA.push_back('j');
          break;
        case llvm::Instruction::GetElementPtr:
          break;
        case llvm::Instruction::Trunc:
          DNA.push_back('l');
          break;
        case llvm::Instruction::ZExt:
          DNA.push_back('m');
          break;
        case llvm::Instruction::SExt:
          DNA.push_back('n');
          break;
        case llvm::Instruction::UIToFP:
          DNA.push_back('o');
          break;
        case llvm::Instruction::SIToFP:
          DNA.push_back('p');
          break;
        case llvm::Instruction::PtrToInt:
          DNA.push_back('q');
          break;
        case llvm::Instruction::IntToPtr:
          DNA.push_back('r');
          break;
        case llvm::Instruction::BitCast:
          //DNA.push_back('s');
          break;
        case llvm::Instruction::AddrSpaceCast:
          DNA.push_back('t');
          break;
        case llvm::Instruction::FPTrunc:
          DNA.push_back('u');
          break;
        case llvm::Instruction::FPExt:
          DNA.push_back('v');
          break;
        case llvm::Instruction::FPToUI:
          DNA.push_back('x');
          break;
        case llvm::Instruction::FPToSI:
          DNA.push_back('y');
          break;
        case llvm::Instruction::ICmp:
          DNA.push_back('w');
          break;
        case llvm::Instruction::FCmp:
          DNA.push_back('z');
          break;
        case llvm::Instruction::Select:
          DNA.push_back('0');
          break;
        case llvm::Instruction::VAArg:
          DNA.push_back('1');
          break;
        case llvm::Instruction::LandingPad:
          DNA.push_back('2');
          break;
        case llvm::Instruction::PHI:
          //DNA.push_back('3');
          break;
        case llvm::Instruction::Call:
          DNA.push_back('4');
          break;
        default:
          DNA.push_back('5');
          break;
      }
    }
  }

  return DNA;
}
