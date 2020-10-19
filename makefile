CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mphpi
OBJS=mphpi.o lexical/SymbolTable.o \
	 lexical/LexicalAnalysis.o \
	 syntatic/SyntaticAnalysis.o \
	 interpreter/util/Memory.o \
	 interpreter/value/IntegerValue.o \
	 interpreter/value/StringValue.o \
	 interpreter/value/ArrayValue.o \
	 interpreter/expr/ExprUtils.o \
	 interpreter/expr/ConstExpr.o \
	 interpreter/expr/ReadExpr.o \
	 interpreter/expr/ArrayExpr.o \
	 interpreter/expr/VarVarExpr.o \
	 interpreter/expr/Variable.o \
	 interpreter/expr/AccessExpr.o \
	 interpreter/expr/UnaryExpr.o \
	 interpreter/expr/BinaryExpr.o \
	 interpreter/expr/SingleBoolExpr.o \
	 interpreter/expr/NotBoolExpr.o \
	 interpreter/expr/CompositeBoolExpr.o \
	 interpreter/command/BlocksCommand.o \
	 interpreter/command/EchoCommand.o \
	 interpreter/command/WhileCommand.o \
	 interpreter/command/AssignCommand.o \
	 interpreter/command/IfCommand.o \
	 interpreter/command/ForeachCommand.o 

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	cp $(TARGET) /usr/local/bin

mphpi.o: lexical/LexicalAnalysis.h syntatic/SyntaticAnalysis.h

lexical/SymbolTable.o: lexical/TokenType.h
lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

syntatic/SyntaticAnalysis.o: syntatic/SyntaticAnalysis.h

interpreter/util/Memory.o: interpreter/util/Memory.h

interpreter/value/IntegerValue.o: interpreter/value/IntegerValue.h
interpreter/value/StringValue.o: interpreter/value/StringValue.h
interpreter/value/ArrayValue.o: interpreter/value/ArrayValue.h

interpreter/expr/ExprUtils.o: interpreter/expr/ExprUtils.h
interpreter/expr/ConstExpr.o: interpreter/expr/ConstExpr.h 
interpreter/expr/ReadExpr.o: interpreter/expr/ReadExpr.h
interpreter/expr/ArrayExpr.o: interpreter/expr/ArrayExpr.h
interpreter/expr/VarVarExpr.o: interpreter/expr/VarVarExpr.h
interpreter/expr/Variable.o: interpreter/expr/Variable.h
interpreter/expr/AccessExpr.o: interpreter/expr/AccessExpr.h
interpreter/expr/UnaryExpr.o: interpreter/expr/UnaryExpr.h
interpreter/expr/BinaryExpr.o: interpreter/expr/BinaryExpr.h
interpreter/expr/SingleBoolExpr.o: interpreter/expr/SingleBoolExpr.h
interpreter/expr/NotBoolExpr.o: interpreter/expr/NotBoolExpr.h
interpreter/expr/CompositeBoolExpr.o: interpreter/expr/CompositeBoolExpr.h

interpreter/command/BlocksCommand.o: interpreter/command/BlocksCommand.h
interpreter/command/EchoCommand.o: interpreter/command/EchoCommand.h
interpreter/command/WhileCommand.o: interpreter/command/WhileCommand.h
interpreter/command/AssignCommand.o: interpreter/command/AssignCommand.h
interpreter/command/IfCommand.o: interpreter/command/IfCommand.h
interpreter/command/ForeachCommand.o: interpreter/command/ForeachCommand.h

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<