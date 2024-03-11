add_executable (calc
  Calc.cpp
  CodeGen.cpp
  Lexer.cpp
  Parser.cpp
  Sema.cpp
  )

install(TARGETS calc
  RUNTIME DESTINATION bin
  COMPONENT calc)  
target_link_libraries(calc PRIVATE ${llvm_libs})
