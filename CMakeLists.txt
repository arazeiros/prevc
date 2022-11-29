CMAKE_MINIMUM_REQUIRED(VERSION 3.4.3)
PROJECT(prevc C CXX)
SET(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(LLVM 13...<14 CONFIG)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})
ADD_DEFINITIONS(${LLVM_DEFINITIONS})
LLVM_MAP_COMPONENTS_TO_LIBNAMES(llvm_libs x86codegen)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/include)

SET(DTG_generator_script  ${CMAKE_SOURCE_DIR}/script/derivation-tree-generator-generator.py)
SET(DTG_generator         python3 ${DTG_generator_script})
SET(DTG_grammar           ${CMAKE_SOURCE_DIR}/src/pipeline/syntax_analysis/grammar.txt)
SET(DTG_enum_header       ${CMAKE_CURRENT_BINARY_DIR}/include/prevc/pipeline/syntax_analysis/variable-type.hxx)
SET(DTG_header            ${CMAKE_CURRENT_BINARY_DIR}/include/prevc/pipeline/syntax_analysis/derivation-tree-generator.hxx)
SET(DTG_source            ${CMAKE_CURRENT_BINARY_DIR}/src/pipeline/syntax_analysis/derivation-tree-generator.cxx)

GET_FILENAME_COMPONENT(DTG_include ${DTG_enum_header} DIRECTORY)
GET_FILENAME_COMPONENT(DTG_src     ${DTG_source}      DIRECTORY)

ADD_CUSTOM_COMMAND(
    OUTPUT ${DTG_enum_header} ${DTG_header} ${DTG_source}
    COMMAND mkdir -p ${DTG_include} ${DTG_src}
    COMMAND ${DTG_generator} -vh ${DTG_enum_header} -bh ${DTG_header} -bs ${DTG_source} ${DTG_grammar}
    DEPENDS ${DTG_grammar} ${DTG_generator_script}
)
ADD_CUSTOM_TARGET(generate_DTG DEPENDS ${DTG_enum_header} ${DTG_header} ${DTG_source})

ADD_EXECUTABLE(prevc
    src/error.cxx
    src/prevc.cxx
    src/settings.cxx
    src/pipeline/phase.cxx
    src/pipeline/pipeline.cxx
    src/pipeline/lexical_analysis/lexical-analysis.cxx
    src/pipeline/lexical_analysis/symbol.cxx
    src/pipeline/lexical_analysis/symbols-vector.cxx
    src/pipeline/semantic_analysis/array-type.cxx
    src/pipeline/semantic_analysis/atom-type.cxx
    src/pipeline/semantic_analysis/concrete-type.cxx
    src/pipeline/semantic_analysis/frame.cxx
    src/pipeline/semantic_analysis/frame-system.cxx
    src/pipeline/semantic_analysis/link-type.cxx
    src/pipeline/semantic_analysis/namespace.cxx
    src/pipeline/semantic_analysis/pointer-type.cxx
    src/pipeline/semantic_analysis/record-type.cxx
    src/pipeline/semantic_analysis/semantic_analysis.cxx
    src/pipeline/semantic_analysis/type.cxx
    src/pipeline/semantic_analysis/type-system.cxx
    src/pipeline/syntax_analysis/syntax-analysis.cxx
    src/pipeline/syntax_analysis/syntax-node.cxx
    src/pipeline/derivation_analysis/derivation-analysis.cxx
    src/pipeline/output_generation/output-generation.cxx
    src/pipeline/AST/arguments.cxx
    src/pipeline/AST/array-access.cxx
    src/pipeline/AST/array-type.cxx
    src/pipeline/AST/assignment.cxx
    src/pipeline/AST/atom.cxx
    src/pipeline/AST/binary-operation.cxx
    src/pipeline/AST/cast.cxx
    src/pipeline/AST/component.cxx
    src/pipeline/AST/component-access.cxx
    src/pipeline/AST/components.cxx
    src/pipeline/AST/compound.cxx
    src/pipeline/AST/declaration.cxx
    src/pipeline/AST/declarations.cxx
    src/pipeline/AST/expression.cxx
    src/pipeline/AST/expression-statement.cxx
    src/pipeline/AST/function-call.cxx
    src/pipeline/AST/function-declaration.cxx
    src/pipeline/AST/if.cxx
    src/pipeline/AST/named-type.cxx
    src/pipeline/AST/new.cxx
    src/pipeline/AST/node.cxx
    src/pipeline/AST/parenthesis.cxx
    src/pipeline/AST/parameter.cxx
    src/pipeline/AST/parameters.cxx
    src/pipeline/AST/pointer-type.cxx
    src/pipeline/AST/primitive-type.cxx
    src/pipeline/AST/record-type.cxx
    src/pipeline/AST/statement.cxx
    src/pipeline/AST/statements.cxx
    src/pipeline/AST/type.cxx
    src/pipeline/AST/unary-operation.cxx
    src/pipeline/AST/type-declaration.cxx
    src/pipeline/AST/variable-declaration.cxx
    src/pipeline/AST/variable-name.cxx
    src/pipeline/AST/while.cxx
    src/util/location.cxx
    src/util/reader.cxx
    src/util/string.cxx
    ${DTG_source}
)
SET_PROPERTY(TARGET prevc PROPERTY CXX_STANDARD 17)
TARGET_LINK_LIBRARIES(prevc ${llvm_libs})
ADD_DEPENDENCIES(prevc generate_DTG)
