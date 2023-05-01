#ifndef TINYLANG_CODEGEN_CODEGENERATOR_H
#define TINYLANG_CODEGEN_CODEGENERATOR_H

#include "tinylang/AST/AST.h"
#include "llvm/Target/TargetMachine.h"
#include <string>

namespace tinylang {

class CodeGenerator {
  llvm::LLVMContext &Ctx;
  llvm::TargetMachine *TM;
  ModuleDeclaration *CM;

protected:
  CodeGenerator(llvm::LLVMContext &Ctx, llvm::TargetMachine *TM)
      : Ctx(Ctx), TM(TM), CM(nullptr) {}

public:
  static CodeGenerator *create(llvm::LLVMContext &Ctx, llvm::TargetMachine *TM);

  std::unique_ptr<llvm::Module> run(ModuleDeclaration *CM, std::string FileName);
};
} // namespace tinylang
#endif