CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(prevc CXX)
SET(CMAKE_CXX_STANDARD 14)

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
    src/prevc.cxx
    src/error.cxx
    src/pipeline/phase.cxx
    src/pipeline/pipeline.cxx
    src/pipeline/lexical_analysis/lexical-analysis.cxx
    src/pipeline/lexical_analysis/symbol.cxx
    src/pipeline/lexical_analysis/symbols-vector.cxx
    src/pipeline/syntax_analysis/syntax-analysis.cxx
    src/pipeline/syntax_analysis/syntax-node.cxx
    src/pipeline/derivation_analysis/derivation-analysis.cxx
    src/pipeline/output_generation/output-generation.cxx
    src/pipeline/AST/atom.cxx
    src/pipeline/AST/binary-operation.cxx
    src/pipeline/AST/compound.cxx
    src/pipeline/AST/declaration.cxx
    src/pipeline/AST/declarations.cxx
    src/pipeline/AST/expression.cxx
    src/pipeline/AST/expression-statement.cxx
    src/pipeline/AST/new.cxx
    src/pipeline/AST/node.cxx
    src/pipeline/AST/parenthesis.cxx
    src/pipeline/AST/primitive-type.cxx
    src/pipeline/AST/statement.cxx
    src/pipeline/AST/statements.cxx
    src/pipeline/AST/type.cxx
    src/pipeline/AST/unary-operation.cxx
    src/pipeline/AST/variable-declaration.cxx
    src/util/location.cxx
    src/util/reader.cxx
    src/util/string.cxx
    ${DTG_source}
)
TARGET_LINK_LIBRARIES(prevc LLVM)
ADD_DEPENDENCIES(prevc generate_DTG)
