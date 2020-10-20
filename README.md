# Interpretador para miniPHP

Este projeto contém a implementação de um interpetador para a linguage miniPHP. É uma linguagem criada para este projeto, utilizado como primeiro trabalho prático para a disciplina de Linguagens de Programação do CEFET-MG, no segundo semestre de 2020, ministrada pelo professor Andrei Rimsa.

## Características da linguagem
miniPHP é uma linguagem interpretada com sintaxe e semântica similares a de PHP.

* A linguagem possui 5 tipos de comando: comando condicional (**if**), comando de repetição (**while**), comando de iteração (**foreach**), comandos de atribuição (**=**, **+=**, **+=**, **-=**, ***=**, **/=**, **.=**), e comando de saída (**echo**).

* Esses comandos podem ser combinados para formar blocos de comando.

* Identificadores (variáveis) começam com o símbolo **$** e são seguidas de letras, dígitos e undescores. Eles podem armazenar números inteiros, strings ou arrays.

* Também são suportados varvar (variáveis para variáveis) de forma bem semelhante a existente em PHP.

* A linguagem permite avaliação de expressões lógicas em comandos condicionais e de repetição.

* As expressões lógicas suportadas são: igual (==), diferente (!=), menor (<), maior (>), menor igual (<=), maior igual (>=). Elas podem ser combinadas através do comando **and** (e) e **or** (ou).

* As expressões lógicas também podem ser negadas através do símbolo **!**.

* A linguagem suporta leitura de valores inteiros e strings através do comando read.

* Expressões artiméticas são suportadas sobre números inteiros: adição (+), subtração (-), multiplicação (*), divisão (/) e resto da divisão (%). Expressões artiméticas compostas são suportadas e podem fazer uso dos separadores **(  )** para garantir a ordem de execução.

* A linguagem possui comentários multilinhas por meio dos símbolos **/*** (início do bloco de comentário) e ***/** (término do bloco de comentário).

```
/* Calcula o somatorio de numeros obtidos pela entrada */

$sum = read "Digite um número: ";

while (1 == 1) {
    $sum += read "Digite um outro número: ";
    echo "Somatório atual: " . $sum . "\n";
}
```

Esse programa calcula o somatório dos números digitados pelo usuário.

## Implementação do interpretador

A implementação do interpretador pode ser dividida em três fases:
[analisador léxico](#analisador-léxico),
[analisador sintático](#analisador-sintático),
[interpretador](#interpretador).
Cada uma dessas fases será detalhada a seguir.

### Analisador léxico

O analisador léxico é responsável por separar os *tokens* da linguagem. *Tokens* são os menores elementos que podem ser formados por um programa.

#### Lexema

O lexema é uma estrutura que carrega um *token* e o tipo desse *token*. Opcionalmente, um lexema pode carregar informações adicionais, porém essas não serão utilizadas no escopo da implementação dessa linguagem.

```C++
struct Lexeme {
    std::string token;
    enum TokenType type;
};
```
O lexema possui seus membros públicos para facilitar sua utilização pelo
analisador léxico.
O *token* é uma string com o elemento formado, e *type* é o tipo do *token*.
Os tipos possíveis são listados pela enumeração *TokenType* que inclui símbolos
da linguagem (ex.: **+**, **;**, ...), palavras-reservadas (ex.: **if**,
**while**, ...), além de alguns tipos especiais (ex.: *token* inválido,
constantes inteiras, constantes strings, ...).

```C++
enum TokenType {
    //Specials
    TT_UNEXPECTED_EOF = -2,
    TT_INVALID_TOKEN = -1,
    TT_END_OF_FILE = 0,

    //Symbols
    TT_SEMICOLON,             // ;
    TT_OPEN_BRACES,           // (
    TT_CLOSE_BRACES,          // )
    TT_OPEN_BRACKETS,         // [
    TT_CLOSE_BRACKETS,        // ]
    TT_OPEN_CURLY_BRACKETS,   // {
    TT_CLOSE_CURLY_BRACKETS,  // }
    TT_COMMA,                 // ,

    //Commands
    TT_IF,
    TT_ELSE,
    TT_ELSEIF,
    TT_WHILE,
    TT_FOREACH,
    TT_FOREACH_AS,
    TT_ECHO,

    //Constants
    TT_INTEGER, 
    TT_STRING,
    TT_LOGIC,

    //Values
    TT_READ,
    TT_ARRAY,

    //Operators
    TT_ADD,              // +
    TT_SUB,              // -
    TT_MUL,              // *
    TT_DIV,              // /
    TT_MOD,              // %

    TT_CONCAT,           // .

    TT_EQUALS,           // ==
    TT_NOT_EQUALS,       // !=
    TT_LESSER,           // <
    TT_GREATER,          // >
    TT_LESSER_EQUALS,    // <=
    TT_GREATER_EQUALS,   // >=
    TT_NOT,              // !

    TT_AND,              // and
    TT_OR,               // or
    
    TT_ASSIGN,           // =
    TT_ADD_ASSIGN,       // +=
    TT_SUB_ASSIGN,       // -=
    TT_MUL_ASSIGN,       // *=
    TT_DIV_ASSIGN,       // /=
    TT_MOD_ASSIGN,       // %=
    TT_CONCAT_ASSIGN,    // .=

    TT_INCREMENT,        // ++
    TT_DECREMENT,        // --

    TT_ARRAY_ASSIGN,     // =>

    //Variables
    TT_VAR,
    TT_VAR_VAR           // $
};
```

Os três primeiros são tipos especiais usados para identificar as seguintes
situações: fim de arquivo inesperado (`TT_UNEXPECTED_EOF`), *token* inválido
(`TT_INVALID_TOKEN`), e fim de arquivo normal/esperado (`TT_END_OF_FILE`). Outros são utilizados para identificar constantes inteiras (`TT_INTEGER`), constantes strings (`TT_STRING`) e tipos lógicos (`TT_LOGIC`). Já os dois últimos tipos são usados para representar os tipos varvar (`TT_VAR_VAR`) e identificadores (`TT_VAR`).

Todos os outros são designados para palavras-reservadas ou símbolos da
linguagem.
Para o programa de exemplo, os lexemas obtidos podem ser vistos na seção de
[resultado](#resultado).

#### Tabela de Símbolos

A tabela de símbolos (`SymbolTable`) é uma estrutura auxiliar utilizada para
facilitar o casamento de um *token* com seu tipo.
A tabela de símbolos é um dicionário que mapeia uma chave (**token**) com seu
valor (**TokenType**).
Essa tabela é pré-populada para todas as palavras-reservadas e símbolos da
linguagem.

| *Token* | *TokenType* |
| ------- | ----------- |
| ";"     | SEMICOLON   |
| "="     | ASSIGN      |
| "=="    | EQUAL       |
| "!="    | NOT_EQUAL   |
| "<"     | LOWER       |
| ...     | ...         |

Note que não é possível preencher essa tabela com todos os números existentes,
nem com todos os possíveis identificadores que possam vir a ser criados por um
programa.
Também não deve ser preenchida com os três tipos especiais (`TT_UNEXPECTED_EOF`,
`TT_INVALID_TOKEN`, `TT_END_OF_FILE`).
Como a linguagem possui escopo global, uma vez populada essa tabela não será
modificada.
Além disso, qualquer consulta a esse mapa cujo *token* não seja
encontrado deve retornar o tipo *token* inválido (`TT_INVALID_TOKEN`).

#### Autômato Finito Determinístico

Existem várias estratégias para formação de lexemas. Na implementação desse
interpretador será utilizado um autômato finito determinístico, também conhecido
como máquina de estados, conforme diagrama a seguir.

<p align="center">
  <img src="images/lexico.jpg?raw=true" width="500" height="300">
</p>

O autômato possui estados (nomeados de 1 a 16) e arestas (rotuladas com
símbolos, caracteres do programa).
Existe um único estado inicial, estado 1 representado pelo estado com uma aresta
entrante sem origem, e dois estados finais, estados 15 e 16 representados pela
oval dupla.
A transição é dada de um estado x (*e<sub>x</sub>*) para um estado y
(*e<sub>y</sub>*) sob um caracter do programa (*'s'*):
*T(e<sub>x</sub>, 's') = e<sub>y</sub>*.
O rótulo `ungetc` é um marcador especial que permite que um símbolo lido seja
devolvido ao buffer para que seja lido novamente posteriormente.
O analisador léxico implementa esse autômato.

```C++
class LexicalAnalysis {
    public:
        LexicalAnalysis(const char* filename);
        virtual ~LexicalAnalysis();

        Lexeme nextToken();
        int line() const { return m_line; }
    private:
        int isLetter(char c);
        int isDigit(char c);
        int m_line;
        SymbolTable m_st;
        FILE* m_input;
};
```
O analisador léxico abre o arquivo de entrada que se deseja interpretar.
É ser possível *devolver* um caracter para o buffer de leitura, por meio do descritor `FILE\*` com a função `fungetc` nativa.
Assim, o analisador léxico sempre mantém: (1) um apontador para o número da linha
atual (`int m_line;`); (2) uma instância com a tabela de símbolos
(`SymbolTable m_st;`); e (3) o descritor do arquivo aberto
(`FILE* m_input;`).

```C++
Lexeme LexicalAnalysis::nextToken() {    
    Lexeme lex;
    SymbolTable sb;

    int state = 1;

    while (state != 15 && state != 16) {
        int c = fgetc(m_input);

        switch (state) {            
            case 1:
                    ...
                break;
            case 2:
                    ...
                break;
            case 3:
                    ...
                break;
            case 4:
                    ...
                break;
            case 5:
                    ...
                break;
            case 6:
                    ...
                break;
            case 7:
                    ...
                break;
            case 8:
                    ...
                break;
            case 9:
                    ...
                break;
            case 10:
                    ...
                break;
            case 11:
                    ...
                break;
            case 12:
                    ...
                break;
            case 13:
                    ...
                break;
            case 14:
                    ...
                break;
            default:
                throw std::string("Invalid State");
        }
    }

    if (state == 15) {
        lex.type = sb.find(lex.token);
    }

    return lex;
}
````

O autômato foi implementado na função `nextToken` do analisador léxico.
A cada chamada dessa função ativa-se o autômato que retorna próximo lexema do
programa de entrada. 
O autômato é iniciado no estado 1 (`int state = 1;`).

Enquanto não se atingir os estados finais 15 ou 16
(`while (state != 15 && state != 16)`) deve-se ler um caracter da entrada
(`int c = fgetc(m_input);`).
Esse caracter pode ser ou não usado na formação do *token*.
Note que o caracter lido é do tipo inteiro (`int`), já que o fim do arquivo
é denotado pelo inteiro `-1`.
Esse inteiro deve ser convertido de volta para caracter quando for concatená-lo
ao *token*.
Os caminhos que levam ao estado 16 devem anotar explicitamente o tipo do *token*
formado, enquanto os caminhos que leval ao estado 15 devem consultar a tabela
de símbolos (`lex.type = sb.find(lex.token);`).
A implementação de cada transição depende do estado em que a máquina se
encontra.

#### Resultado

O resultado obtido pelo analisador léxico é a sequência de lexemas produzidos
pelo programa de entrada. Para o programa de exemplo, obtêm-se os seguintes
lexemas, nessa ordem:

```
Expected (...,VAR), found ("$sum", VAR)
Expected (...,ASSIGN), found ("=", ASSIGN)
Expected (...,READ), found ("read", READ)
Expected (...,STRING), found (""Digite um número: "", STRING)
Expected (...,SEMICOLON), found (";", SEMICOLON)
Expected (...,WHILE), found ("while", WHILE)
Expected (...,OPEN_BRACES), found ("(", OPEN_BRACES)
Expected (...,INTEGER), found ("1", INTEGER)
Expected (...,EQUALS), found ("==", EQUALS)
Expected (...,INTEGER), found ("1", INTEGER)
Expected (...,CLOSE_BRACES), found (")", CLOSE_BRACES)
Expected (...,OPEN_CURLY_BRACKETS), found ("{", OPEN_CURLY_BRACKETS)
Expected (...,VAR), found ("$sum", VAR)
Expected (...,ADD_ASSIGN), found ("+=", ADD_ASSIGN)
Expected (...,READ), found ("read", READ)
Expected (...,STRING), found (""Digite um outro número: "", STRING)
Expected (...,SEMICOLON), found (";", SEMICOLON)
Expected (...,ECHO), found ("echo", ECHO)
Expected (...,STRING), found (""Somatório atual: "", STRING)
Expected (...,CONCAT), found (".", CONCAT)
Expected (...,VAR), found ("$sum", VAR)
Expected (...,CONCAT), found (".", CONCAT)
Expected (...,STRING), found (""
"", STRING)
Expected (...,SEMICOLON), found (";", SEMICOLON)
Expected (...,CLOSE_CURLY_BRACKETS), found ("}", CLOSE_CURLY_BRACKETS)
Expected (...,END_OF_FILE), found ("", END_OF_FILE)
```

Note que ao final do processo obtém-se o lexema `("", END_OF_FILE)`
que é um marcador que o analisador léxico processou o arquivo de entrada
corretamente e chegou-se a um fim de arquivo sem erros léxicos.

### Analisador sintático

O analisador sintático é responsável por verificar se os *tokens* de um programa
se encontram em uma ordem válida.
Para isso, é definida uma gramática com regras de como os *tokens* são
organizados na linguagem.

#### Gramática

Gramáticas são normalmente expressas no formato EBNF (Extended Backus-Naur
Form), um tipo de gramática livre de contexto.
Nela é possível definir produções opcionais--aquelas separadas por `|` ou entre
`[` e `]`--, repetições de zero ou mais vezes--aquelas entre `{` e `}`--, e
agrupamentos de expressões--aquelas entre `(` e `)`.
A gramática da linguagem miniPHP é mostrada a seguir nesse formato:

```
<code> ::= { <statement> }
<statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
<if> ::= if '(' <boolexpr> ')' '{' <code> '}'
         { elseif '(' <boolexpr> ')' '{' <code> '}' } [ else '{' <code> '}' ]
<while> ::= while '(' <boolexpr> ')' '{' <code> '}'
<foreach> ::= foreach '(' <expr> as <var> [ '=>' <var> ] ')' '{' <code> '}'
<echo> ::= echo <expr> ';'
<assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
<boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
<cmpexpr> ::= <expr> ('==' | '!=' | '<' | '>' | '<=' | '>=') <expr>
<expr> ::= <term> { ('+' | '-' | '.') <term> }
<term> ::= <factor> { ('*' | '/' | '%') <factor> }
<factor> ::= <number> | <string> | <array> | <read> | <value>
<array> ::= array '(' [ <expr> '=>' <expr> { ',' <expr> '=>' <expr> } ] ')'
<read> ::= read <expr>
<value> ::= [ ('++' | '—-') ] <access> | <access> [ ('++' | '--') ]
<access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
<varvar> ::= '$' <varvar> | <var>
```

Os nomes entre chaves chevron, `<` e `>`, são símbolos não terminais, ou seja,
regras de produções; já os outros são símbolos terminais, ou símbolos da
linguagem.
A regra de partida é dada pela primeira regra `<code>`.

Essa gramática foi especialmente desenhada como LL(1), um tipo de gramática
que permite a criação de um parser recursivo descendente olhando apenas um
*token* a frente (*1-symbol lookahead*).

#### Parser

O parser depende do analisador léxico (`LexicalAnalysis lex`) para fornecer
os *tokens* para um programa da entrada.
O parser mantém sempre um lexema ativo (`Lexeme current`), ou seja, o *token*
a ser processado.

```C++
class SyntaticAnalysis {
    public:
        SyntaticAnalysis(LexicalAnalysis& lex);
        virtual ~SyntaticAnalysis();

        BlocksCommand* start();
    private:
        LexicalAnalysis& m_lex;
        Lexeme m_current;

        void advance();
        void eat(enum TokenType type);
        void showError();

        ...

};
```

O analisador sintático possui um método `advance` que passa o lexema atual
para o próximo (`m_current = m_lex.nextToken();`).
Também possui um método `eat` que verifica o casamento do lexema atual com um
tipo de *token* esperado (`if (type == m_current.type)`).
Em caso positivo, deve-se avançar para o próximo lexema (`advance();`), caso
contrário deve-se exibir um erro (`showError();`).

```C++
void SyntaticAnalysis::advance() {
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
    if (type == m_current.type) {
        advance();
    }
    else {
        showError();
    }
}
```

Existem três tipos de erros sintático para essa linguagem: (1) **lexema
inválido** produzido pelo analisador léxico; (2) **fim de arquivo inesperado**
produzido pelo analisador léxico ou sintático; (3) e **lexema não esperado**
caso o próximo *token* não seja o esperado.
O interpretador exibe uma mensagem de acordo com o tipo de erro com o número
da linha onde ele ocorreu e inclui o *token* formado (exceto para fim
de arquivo inesperado).
No caso dessa implementação, o parsing é imediatamente interrompido ao se
encontrar o primeiro erro sintático (`exit(1);`).

```C++
void SyntaticAnalysis::showError() {
    std::cout << std::setw(2) << std::setfill('0') << m_lex.line() << ": ";

    switch (m_current.type) {
        case TT_INVALID_TOKEN:
            std::cout << "Lexema invalido [" << m_current.token << "]" << std::endl;
            break;
        case TT_UNEXPECTED_EOF:
        case TT_END_OF_FILE:
            std::cout << "Fim de arquivo inesperado" << std::endl;
            break;
        default:
            std::cout << "Lexema nao esperado [" << m_current.token << "]" << std::endl;
            break;
    }

    exit(1);
}
```

O parsing deve implementar um procedimento para cada nome de regra (lado
esquerdo da produção).
É interessante manter a descrição da regra completa como um cabeçalho
comentado antes de cada método.

```C++
//<code> ::= { <statement> }
BlocksCommand* SyntaticAnalysis::procCode() { ... }

//<statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
Command* SyntaticAnalysis::procStatement() { ... }

//<if> ::= if '(' <boolexpr> ')' '{' <code> '}'
//         { elseif '(' <boolexpr> ')' '{' <code> '}' } [ else '{' <code> '}' ]
IfCommand* SyntaticAnalysis::procIf() { ... }

//<while> ::= while '(' <boolexpr> ')' '{' <code> '}'
WhileCommand* SyntaticAnalysis::procWhile() { ... }

//<foreach> ::= foreach '(' <expr> as <var> [ '=>' <var> ] ')' '{' <code> '}'
ForeachCommand* SyntaticAnalysis::procForeach() { ... }

//<echo> ::= echo <expr> ';'
EchoCommand* SyntaticAnalysis::procEcho() { ... }

//<assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
AssignCommand* SyntaticAnalysis::procAssign() { ... }

//<boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBoolexpr() { ... }

//<cmpexpr> ::= <expr> ('==' | '!=' | '<' | '>' | '<=' | '>=') <expr>
SingleBoolExpr* SyntaticAnalysis::procCmpexpr() { ... }

//<expr> ::= <term> { ('+' | '-' | '.') <term> }
Expr* SyntaticAnalysis::procExpr() { ... }

//<term> ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntaticAnalysis::procTerm() { ... }

//<factor> ::= <number> | <string> | <array> | <read> | <value>
Expr* SyntaticAnalysis::procFactor() { ... }

//<array> ::= array '(' [ <expr> '=>' <expr> { ',' <expr> '=>' <expr> } ] ')'
ArrayExpr* SyntaticAnalysis::procArray() { ... }

//<read> ::= read <expr>
ReadExpr* SyntaticAnalysis::procRead() { ... }

//<value> ::= [ ('++' | '—-') ] <access> | <access> [ ('++' | '--') ]
Expr* SyntaticAnalysis::procValue() { ... }

//<access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
AccessExpr* SyntaticAnalysis::procAccess() { ... }

//<varvar> ::= '$' <varvar> | <var>
Expr* SyntaticAnalysis::procVarvar() { ... }
```
Existe um método especial `start` para dar início ao processo de parsing.
Ele tem uma chamada para a regra de partida (`<code>`) e um casamento de
*token* com o fim de arquivo normal/esperado.

```C++
BlocksCommand* SyntaticAnalysis::start() {
    BlocksCommand* code = procCode();
    eat(TT_END_OF_FILE);
    return code;
}
```

Para implementar uma regra deve-se olhar as produções do seu lado direito.
Por exemplo, para a regra `<while>` tem-se `<while> ::= while '(' <boolexpr> ')' '{' <code> '}'`.
Para os símbolos não terminais, entre chaves chevron (ex.: `<boolexpr>`),
deve-se chamar o procedimento respectivo: `procBoolExpr();`.
Para os símbolos terminais (ex.: `while`) deve-se chamar casar o padrão com o
tipo de *token* respectivo: `eat(TT_WHILE);`.
Assim, a implementação do regra `<while>` é dada a seguir.

```C++
//<while> ::= while '(' <boolexpr> ')' '{' <code> '}'
WhileCommand* SyntaticAnalysis::procWhile() {
    eat(TT_WHILE);
    int line = (m_lex.line());

    eat(TT_OPEN_BRACES);
    BoolExpr* cond = procBoolexpr();
    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    Command* cmds = procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

    return new WhileCommand(line, cond, cmds);
}
```

Quando se tem uma regra com várias opções, separados pelo símbolo `|` na
gramática, deve-se verificar o tipo do lexema atual para verificar como
proceder.
Repare que, nos casos onde existe a produção na esquerda é uma regra, deve-se
olhar nessa regra qual *token* usar.
Para chamar a regra `<if>`, deve-se olhar
dentro dessa regra qual é primeiro *token* de sua produção, nesse caso `if` cujo
tipo do *token* é `TT_IF`.
O mesmo vale para a regra `<while>`, onde `while` tem como tipo de *token*
`TT_WHILE`.

```C++
//<statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
Command* SyntaticAnalysis::procStatement() {
    switch (m_current.type) {
        case TT_IF:
            return procIf();
        case TT_WHILE:
            return procWhile();
        case TT_FOREACH:
            return procForeach();
        case TT_ECHO:
            return procEcho();
        default:
            return procAssign();
    }
}
```

Quando se tem uma regra com um trecho opcional, entre `[` e `]`, deve-se usar
a mesma estratégia da implementação anterior.
Note que, se verificado que o *token* é do tipo `!`
(`if (current.type == TT_NOT)`), esse token é tratado no comando
(`eat(TT_NOT); notBool = true;`).

```C++
//<boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBoolexpr() {
    int line;
    bool notBool = false;
    BoolOp op;

    if (m_current.type == TT_NOT) {
        eat(TT_NOT);
        notBool = true;
    }

    BoolExpr* left = procCmpexpr();
    line = m_lex.line();

    if (notBool) {
        left = new NotBoolExpr(line, left);
    }

    if (m_current.type == TT_AND || m_current.type == TT_OR) {
        if (m_current.type == TT_AND) op = BoolOp::And;
        else op = BoolOp::Or;

        eat(m_current.type);
        line = m_lex.line();
        BoolExpr* right = procBoolexpr();

        return new CompositeBoolExpr(line, left, op, right);
    }

    return left;    
}
```

Por fim, regras que possuem repetições de zero ou mais vezes, entre os símbolos
`{` e `}`, são implementadas como laços.
Repare que, para a regra `<code>` que possui repetição da regra `<statement>`,
deve-se olhar quais *tokens* podem atingir essa regra, que nesse caso são:
`TT_IF`, `TT_WHILE`, `TT_FOREACH`, `TT_ECHO`, `TT_INCREMENT`, `TT_DECREMENT`, `TT_VAR_VAR`, `TT_VAR` e `TT_OPEN_BRACES`.

```C++
//<code> ::= { <statement> }
BlocksCommand* SyntaticAnalysis::procCode() {
    BlocksCommand* code = new BlocksCommand(m_lex.line());

    while (m_current.type == TT_IF || m_current.type == TT_WHILE || m_current.type == TT_FOREACH || 
           m_current.type == TT_ECHO || m_current.type == TT_INCREMENT || m_current.type == TT_DECREMENT || 
           m_current.type == TT_VAR_VAR || m_current.type == TT_VAR || m_current.type == TT_OPEN_BRACES) {
        
        code->addCommand(procStatement());

    }
    return code;
}
```

### Interpretador
O interpretador é responsável por modelar o comportamento de um programa.
Um diagrama de classes é dado na seção [modelo](#modelo) e como ele deve ser
usado é mostrado na seção de [implementação](#implementação).

#### Modelo

O interpretador foi modelado de acordo com o diagrama de classes a seguir.
Esse modelo pode ser divido em três partes: **valores**, **comandos** e **expressões**.
Valores armazenam um valor. Esses podem ser primitivos (inteiros ou strings) ou compostos (arrays).
Comandos executam uma ação e não produzem uma saída, ex.: comandos de atribução,
condicionais (`if`), de repetição (`while`), etc.
Já as expressões são avaliadas e produzem um resultado, ex.: expressão,
aritmética, expressão booleana, etc.
O modelo separa essas duas partes nos pacotes: `value`, `command` e `expr`.
Os valores devem herdar da classe abstrata `Value<T>` e implementar o método `T value()`. Em C++ foi utilizada uma classe `Type` acima da classe `Value`, que contém um *enum* para indicar o tipo do valor utilizado pelo objeto.
Os comandos devem herdar da classe abstrata `Command` e implementar o método
`void execute()`.
As expressões inteiras devem herdar de `IntExpr` e implementar o método
`Type expr()`, enquanto as expressões lógicas devem herdar de `BoolExpr` e
implementar o método `boolean expr()`.
Todas as classes de comando e de expressões incluem o número da linha onde suas construções aparecem no programa fonte.

<p align="center">
  <img src="images/interpretador1.jpg?raw=true" width="936" height="650">
</p>

<p align="center">
  <img src="images/interpretador2.jpg?raw=true" width="936" height="650">
</p>

Cada classe desse modelo deve implementar um comportamento, conforme explicado
nas tabelas a seguir para cada uma das classes base:

- `Value`:
  | *Classe*         | *Comportamento* |
  | ---------------- | --------------- |
  | `IntegerValue`   | Armazena um valor inteiro |
  | `StringValue`    | Armazena um valor textual (string) |
  | `ArrayValue`     | Armazena um array de values |


- `Command`:
  | *Classe*         | *Comportamento* |
  | ---------------- | --------------- |
  | `BlocksCommand`  | Executar cada um dos comandos da lista do bloco em sequência |
  | `AssignCommand`  | Atribuir o resultado de uma expressão em uma variável |
  | `EchoCommand`    | Mostrar a saída de uma expressão na tela |
  | `IfCommand`      | Executar o bloco *then* se a expressão for verdadeira, caso contrário executar o bloco *else* se esse existir |
  | `WhileCommand`   | Executar o bloco do corpo da repetição enquanto a expressão for verdadeira |
  | `ForeachCommand` | Iterar pelo array fornecido e atribuir os valores em variáveis `key` e `value` |

- `BoolExpr`:
  | *Classe*          | *Comportamento* |
  | ----------------  | --------------- |
  | `SingleBoolExpr`  | Comparar dois valores de acordo com uma operação lógica |
  | `NotBoolExpr`     | Negar uma expressão lógica |
  |`CompositeBoolExpr`| Comparar duas expressões booleanas de acordo com uma operação lógica |

- `Expr`:
  | *Classe*         | *Comportamento* |
  | ---------------- | --------------- |
  | `ConstExpr`      | Obter o valor de uma constante |
  | `ReadExpr`       | Ler um valor dado por um usuário pela entrada de teclado |
  | `UnaryExpr`      | Realizar uma operação unária entre dois valores inteiros |
  | `BinaryExpr`     | Realizar uma operação entre dois valores |
  | `ArrayExpr`      | Inserir dados em um array e retornar um array |
  | `Variable`       | Armazenar o valor em uma variável |
  | `VarvarExpr`     | Armazenar o valor de um Varvar |
  | `AccessExpr`     | Armazenar o valor de um acesso a um dado |

#### Implementação

Cada regra da gramática deve instanciar um objeto do modelo dado com os
argumentos necessários para sua execução.
A seguir é detalhado quais classes devem ser retornadas para todas as regras.
As regras que podem retornar mais de um tipo de objeto devem usar a classe
base genérica.
Por exemplo, a regra `<varvar>` pode retornar uma expressão varvar ou uma variável portanto deve-se usar a classe base `SetExpr`.

| *Regra*      | *Retorno*       |
| ------------ | --------------- |
| `<code>`     | `BlocksCommand` |
| `<statement>`| `Command`       |
| `<if>`       | `IfCommand`     |
| `<while>`    | `WhileCommand`  |
| `<foreach>`  | `ForeachCommand`|
| `<echo>`     | `EchoCommand`   |
| `<assign>`   | `AssignCommand` |
| `<boolexpr>` | `BoolExpr`      |
| `<cmpexpr>`  | `SingleBoolExpr`|
| `<expr>`     | `Expr`          |
| `<term>`     | `Epr`           |
| `<factor>`   | `Expr`          |
| `<array>`    | `ArrayExpr`     |
| `<read>`     | `ReadExpr`      |
| `<value>`    | `Expr`          |
| `<access>`   | `AccessExpr`    |
| `<varvar>`   | `SetExpr`       |
| `<var>`      | `Variable`      |

Considere a implementação da regra `<while>` que chama a regra `<boolexpr>` para
obter a expressão condicional (retorna uma instância de `BoolExpr`) e que
chama a regra `<code>` com uma lista de comandos (retorna uma instância
de `BlocksCommand`).
Esses são os dois objetos necessários para a construção do objeto `WhileCommand`
conforme definido no modelo.
Além disso, para construir esse objeto deve-se obter o número da linha onde
ele se encontra no programa fonte.
O número da linha deve ser obtido (`int line = m_lex.line();`) sempre depois do
casamento do primeiro *token* da regra (nesse caso `eat(TT_WHILE);`).
Assim, o procedimento completo para essa regra é dado a seguir.

```C++
//<while> ::= while '(' <boolexpr> ')' '{' <code> '}'
WhileCommand* SyntaticAnalysis::procWhile() {
    eat(TT_WHILE);
    int line = (m_lex.line());

    eat(TT_OPEN_BRACES);
    BoolExpr* cond = procBoolexpr();
    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    Command* cmds = procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

    return new WhileCommand(line, cond, cmds);
}
```

A implementação das classe dos modelos devem: (1) inicializar os atribuitos da
classe com os objetos passados pelo construtor; e (2) implementar o método
abstrato de sua classe base de acordo com o comportamento esperado dado de sua
regra.
Por exemplo, a implementação da classe `WhileCommand` é dada a seguir:

```C++

class WhileCommand : public Command {
    public:
        WhileCommand(int line, BoolExpr* cond, Command* cmds);
        virtual ~WhileCommand();

        void execute();

    private:
        BoolExpr* m_cond;
        Command* m_cmds;
};

WhileCommand::WhileCommand(int line, BoolExpr* cond, Command* cmds) : Command(line), m_cond(cond), m_cmds(cmds) {

}

WhileCommand::~WhileCommand() {

}

void WhileCommand::execute() {
    while (ExprUtils::getExpr(m_cond)) {
        m_cmds->execute();
    }
}
```

O mesmo vale para a implementação de uma expressão.
Por exemplo para a classe `BinaryExpr`:

```C++

enum BinaryOp {
    AddOp = 1,
    SubOp,
    ConcatOp,
    MulOp,
    DivOp,
    ModOp
};

class BinaryExpr : public Expr {
    public:
        BinaryExpr(int line, Expr* left, BinaryOp op, Expr* right);
        virtual ~BinaryExpr();

        Type* expr();
        
    private:
        Expr *m_left;
        BinaryOp m_op;
        Expr *m_right;
};

BinaryExpr::BinaryExpr(int line, Expr* left, BinaryOp op, Expr* right) : Expr(line, Expr::BinaryExpr), m_left(left), m_op(op), m_right(right) {

}

BinaryExpr::~BinaryExpr() {

}

Type* BinaryExpr::expr() {
    std::stringstream error;

    Type* typeLeft = ExprUtils::getExpr(m_left);
    Type* typeRight = ExprUtils::getExpr(m_right);

    IntegerValue *integerLeft, *integerRight;
    StringValue *stringLeft, *stringRight;

    if (typeLeft->type() == Type::ArrayType || typeRight->type() == Type::ArrayType) {
        error << std::setw(2) << std::setfill('0') << m_line << ": ";
        error << "Operacoes binarias sao invalidas para arrays";
        throw error.str();
    }

    if (typeLeft->type() == Type::StringType || typeRight->type() == Type::StringType) {
        if (typeLeft->type() == Type::StringType) {
            stringLeft = (StringValue*) typeLeft;
        }
        else {
            integerLeft = (IntegerValue*) typeLeft;
            stringLeft = new StringValue(std::to_string(integerLeft->value()));
        }

        if (typeRight->type() == Type::StringType) {
            stringRight = (StringValue*) typeRight;
        }
        else {
            integerRight = (IntegerValue*) typeRight;
            stringRight = new StringValue(std::to_string(integerRight->value()));
        }

        switch (m_op) {
            case ConcatOp:
                return new StringValue(stringLeft->value() + stringRight->value());
            case AddOp:
            case SubOp:            
            case MulOp:
            case DivOp:
            case ModOp:
            default:
                error << std::setw(2) << std::setfill('0') << m_line << ": ";
                error << "Operacao binaria invalida para strings";
                throw error.str();
        }

    }

    integerLeft = (IntegerValue*) typeLeft;
    integerRight = (IntegerValue*) typeRight;

    switch (m_op) {
            case AddOp:
                return new IntegerValue(integerLeft->value() + integerRight->value());
            case SubOp:
                return new IntegerValue(integerLeft->value() - integerRight->value());
            case MulOp:
                return new IntegerValue(integerLeft->value() * integerRight->value());
            case DivOp:
                return new IntegerValue(integerLeft->value() / integerRight->value());
            case ModOp:
                return new IntegerValue(integerLeft->value() % integerRight->value());
            case ConcatOp:
            default:
                return new StringValue(std::to_string(integerLeft->value()) + std::to_string(integerRight->value()));
        }
}
```

O analisador sintático retorna um objeto do tipo `BlocksCommand`. Esse bloco contém todo o código, e é necessário apenas executá-lo através do comando `code -> execute ();`.