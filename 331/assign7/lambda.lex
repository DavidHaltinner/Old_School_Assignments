
type pos = int
type svalue = Tokens.svalue
type ('a,'b) token = ('a,'b) Tokens.token
type lexresult= (svalue,pos) token


val lineNum = ErrorMsg.lineNum
val linePos = ErrorMsg.linePos
fun err(p1,p2) = ErrorMsg.error p1
fun inc_row()  = lineNum := !lineNum+1;
fun row_val()  = !lineNum;

fun make_pos (pos,length) = (pos, pos+length)
fun eof() = Tokens.EOF(make_pos (0,0))


(* Since the language is case insensititve make all chars lower case *)
fun toLower s = 
    String.implode (map (Char.toLower) (String.explode s))
     
(* Recognize keywords *)
fun keyword (s, pos) =
    case s of
      "lambda"      => Tokens.LAMBDA (make_pos (pos, String.size s))
      (* Not a keyword, must be identifier. *)
      | _             => Tokens.VAR (s , pos, pos + String.size s)


	    (* ----  End of included code  ---- *)

%%
%header (functor LambdaCalcLexFun(structure Tokens: LambdaCalc_TOKENS));
%s SkipComment;
digit=[0-9];
newline=\n;
whitespace=[\ \t];
identifier=[a-zA-Z][a-zA-Z0-9]*;
int={digit}+;
exponent=((e|E)"-"?{int});
floats={int}"."{int}{exponent}?; 


%%
{newline}         =>  (inc_row(); linePos := yypos :: !linePos;lex());
{whitespace}+     =>  (lex());
{int}          =>  (case Int.fromString yytext of
			   NONE => 
			       ErrorMsg.impossible ("Cannot convert" ^ yytext)
			 | SOME f => 
			       let val (start, stop) =
				   make_pos(yypos, String.size yytext) 
			       in
				   Tokens.INT(f,start,stop)
			       end);
{identifier}   => (keyword (toLower yytext,yypos));
"."          => (Tokens.DOT (make_pos(yypos, 1)));
"("          => (Tokens.LPAREN (make_pos(yypos, 1)));
")"          => (Tokens.RPAREN (make_pos(yypos, 1)));
"+"          => (Tokens.PLUS (make_pos(yypos, 1)));
"*"          => (Tokens.MULT (make_pos(yypos, 1)));
"letrec"     => (Tokens.LETREC (make_pos(yypos, 1)));
"be"	     => (Tokens.BE (make_pos(yypos, 1)));
"in"	     => (Tokens.IN (make_pos(yypos, 1)));
. =>           (ErrorMsg.error yypos 
			 ("Illegal symbol in input: " ^ yytext ^ "\n");
			 lex());





