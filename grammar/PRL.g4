grammar PRL;

/*
Whitespace policy:
    - trailing whitespace is allowed
    - whitespace between tokens is allowed
    - leading whitespace is forbidden unless the line is the n-th (n != 1) line of a pattern
    - Whitespace between pattern symbols is forbidden
 */

prog : BR* symbolSection BR+//symbol declaration
        ((ruleSection BR+)? initialStateSection | initialStateSection (BR+ ruleSection)?) //both orders are acceptable
        BR* EOF; //possible trailing line breaks, then end file

symbolSection : SYMBOL_KW SYMBOL_ID (COMMA SYMBOL_ID)*;

ruleSection : RULES_KW BR BR* rewritingRule (BR+ rewritingRule)*;
rewritingRule : lhs=pattern arrow rhs=pattern;
pattern : row (BR row)*;
arrow : ARROWTAIL NN_NUMBER? ARROWHEAD;
row : symbol+;
symbol : SYMBOL_ID | SYMBOL_WC;

initialStateSection : IS_KW BR* initialState;
initialState : SYMBOL_ID  shape #intensionalInitialState
                | pattern       #extensionalInitialState;
shape: LPAR  height=NN_NUMBER  COMMA  width=NN_NUMBER  RPAR ;


//LEXER

//Keyphrases
SYMBOL_KW : 'Symbols';          //Start the symbol declaration section
RULES_KW : 'Apply rules';       //Start rule section
IS_KW : 'Starting from';        //Start the starting field definition

LPAR : '(';
RPAR : ')';
COMMA: ',';
ARROWTAIL : '-';
ARROWHEAD : '>';

NN_NUMBER : [1-9][0-9]*;        //Positive natural numbers

SYMBOL_WC : '*';                //Wildcard Symbol
SYMBOL_ID : [!-~];              //Symbols

BR : '\r'? '\n';                //Line breaks
WS : [ \r\t]+ -> skip;          //Ignore whitespace
COM: '//' (~[\r\n])* -> skip;   //Ignore inline comments                      