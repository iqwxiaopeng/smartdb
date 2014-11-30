# included from ../CMakeLists.txt

SET(LEX_EXECUTABLE "flex")
SET(YACC_EXECUTABLE "bison")

SET(PROJ_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(PARSER_GENERATOR_SRC_DIR ${PROJ_ROOT_DIR}/parser)
SET(GENERATED_SRC_DIR ${PROJ_ROOT_DIR}/lib/parser)

MESSAGE(${GENERATED_SRC_DIR}/parser.cpp)

# Create custom command for flex/lex (note the outputs)
ADD_CUSTOM_COMMAND(
    OUTPUT ${GENERATED_SRC_DIR}/lexer.cpp
    COMMAND ${LEX_EXECUTABLE} -o ${GENERATED_SRC_DIR}/lexer.cpp -I ${PARSER_GENERATOR_SRC_DIR}/lexer.l
)
# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
    OUTPUT ${GENERATED_SRC_DIR}/parser.cpp
    COMMAND ${YACC_EXECUTABLE} -dv -o ${GENERATED_SRC_DIR}/parser.cpp ${PARSER_GENERATOR_SRC_DIR}/parser.y
)

# Add lexer.cpp, parser.cpp to the list of sources
SET(PARSER_SOURCE_FILES ${GENERATED_SRC_DIR}/lexer.cpp ${GENERATED_SRC_DIR}/parser.cpp)
