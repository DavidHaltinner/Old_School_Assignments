functor LambdaCalcLexFun(structure Tokens: LambdaCalc_TOKENS)=
   struct
    structure UserDeclarations =
      struct

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

end (* end of user routines *)
exception LexError (* raised if illegal leaf action tried *)
structure Internal =
	struct

datatype yyfinstate = N of int
type statedata = {fin : yyfinstate list, trans: string}
(* transition & final state table *)
val tab = let
val s = [ 
 (0, 
"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000"
),
 (1, 
"\005\005\005\005\005\005\005\005\005\032\034\005\005\005\005\005\
\\005\005\005\005\005\005\005\005\005\005\005\005\005\005\005\005\
\\032\031\005\005\005\030\029\005\028\027\026\025\005\024\023\022\
\\020\020\020\020\020\020\020\020\020\020\005\005\019\018\017\005\
\\005\007\007\007\007\007\007\007\007\007\007\007\007\007\007\007\
\\007\007\007\007\007\007\007\007\007\007\007\005\005\005\005\005\
\\005\007\015\007\007\007\007\007\007\012\007\007\009\007\007\007\
\\007\007\007\007\007\007\007\007\007\007\007\005\006\005\005\005\
\\005"
),
 (7, 
"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\000\
\\000\008\008\008\008\008\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000\008\008\008\008\008\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000"
),
 (9, 
"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\000\
\\000\008\008\008\008\008\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000\008\008\008\008\010\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000"
),
 (10, 
"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\000\
\\000\008\008\008\008\008\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000\008\008\008\008\008\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\011\008\008\008\008\008\008\000\000\000\000\000\
\\000"
),
 (12, 
"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\000\
\\000\008\008\008\008\008\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000\008\008\008\008\008\014\008\008\008\008\008\008\008\013\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000"
),
 (15, 
"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\000\
\\000\008\008\008\008\008\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000\008\008\008\008\016\008\008\008\008\008\008\008\008\008\008\
\\008\008\008\008\008\008\008\008\008\008\008\000\000\000\000\000\
\\000"
),
 (20, 
"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\021\021\021\021\021\021\021\021\021\021\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000"
),
 (32, 
"\000\000\000\000\000\000\000\000\000\033\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\033\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\\000"
),
(0, "")]
fun f x = x 
val s = map f (rev (tl (rev s))) 
exception LexHackingError 
fun look ((j,x)::r, i) = if i = j then x else look(r, i) 
  | look ([], i) = raise LexHackingError
fun g {fin=x, trans=i} = {fin=x, trans=look(s,i)} 
in Vector.fromList(map g 
[{fin = [], trans = 0},
{fin = [], trans = 1},
{fin = [], trans = 1},
{fin = [], trans = 1},
{fin = [], trans = 1},
{fin = [(N 53)], trans = 0},
{fin = [(N 39),(N 53)], trans = 0},
{fin = [(N 10),(N 53)], trans = 7},
{fin = [(N 10)], trans = 7},
{fin = [(N 10),(N 53)], trans = 9},
{fin = [(N 10)], trans = 10},
{fin = [(N 10),(N 45)], trans = 7},
{fin = [(N 10),(N 53)], trans = 12},
{fin = [(N 10),(N 51)], trans = 7},
{fin = [(N 10),(N 29)], trans = 7},
{fin = [(N 10),(N 53)], trans = 15},
{fin = [(N 10),(N 48)], trans = 7},
{fin = [(N 33),(N 53)], trans = 0},
{fin = [(N 35),(N 53)], trans = 0},
{fin = [(N 31),(N 53)], trans = 0},
{fin = [(N 7),(N 53)], trans = 20},
{fin = [(N 7)], trans = 20},
{fin = [(N 24),(N 53)], trans = 0},
{fin = [(N 12),(N 53)], trans = 0},
{fin = [(N 22),(N 53)], trans = 0},
{fin = [(N 18),(N 53)], trans = 0},
{fin = [(N 20),(N 53)], trans = 0},
{fin = [(N 16),(N 53)], trans = 0},
{fin = [(N 14),(N 53)], trans = 0},
{fin = [(N 37),(N 53)], trans = 0},
{fin = [(N 26),(N 53)], trans = 0},
{fin = [(N 41),(N 53)], trans = 0},
{fin = [(N 4),(N 53)], trans = 32},
{fin = [(N 4)], trans = 32},
{fin = [(N 1)], trans = 0}])
end
structure StartStates =
	struct
	datatype yystartstate = STARTSTATE of int

(* start state definitions *)

val INITIAL = STARTSTATE 1;
val SkipComment = STARTSTATE 3;

end
type result = UserDeclarations.lexresult
	exception LexerError (* raised if illegal leaf action tried *)
end

fun makeLexer yyinput =
let	val yygone0=1
	val yyb = ref "\n" 		(* buffer *)
	val yybl = ref 1		(*buffer length *)
	val yybufpos = ref 1		(* location of next character to use *)
	val yygone = ref yygone0	(* position in file of beginning of buffer *)
	val yydone = ref false		(* eof found yet? *)
	val yybegin = ref 1		(*Current 'start state' for lexer *)

	val YYBEGIN = fn (Internal.StartStates.STARTSTATE x) =>
		 yybegin := x

fun lex () : Internal.result =
let fun continue() = lex() in
  let fun scan (s,AcceptingLeaves : Internal.yyfinstate list list,l,i0) =
	let fun action (i,nil) = raise LexError
	| action (i,nil::l) = action (i-1,l)
	| action (i,(node::acts)::l) =
		case node of
		    Internal.N yyk => 
			(let val yytext = substring(!yyb,i0,i-i0)
			     val yypos = i0+ !yygone
			open UserDeclarations Internal.StartStates
 in (yybufpos := i; case yyk of 

			(* Application actions *)

  1 => (inc_row(); linePos := yypos :: !linePos;lex())
| 10 => (keyword (toLower yytext,yypos))
| 12 => (Tokens.DOT (make_pos(yypos, 1)))
| 14 => (Tokens.LPAREN (make_pos(yypos, 1)))
| 16 => (Tokens.RPAREN (make_pos(yypos, 1)))
| 18 => (Tokens.PLUS (make_pos(yypos, 1)))
| 20 => (Tokens.MULT (make_pos(yypos, 1)))
| 22 => (Tokens.MINUS (make_pos(yypos, 1)))
| 24 => (Tokens.DIVIDE (make_pos(yypos, 1)))
| 26 => (Tokens.MOD (make_pos(yypos, 1)))
| 29 => (Tokens.IF (make_pos(yypos, 1)))
| 31 => (Tokens.LT (make_pos(yypos, 1)))
| 33 => (Tokens.GT (make_pos(yypos, 1)))
| 35 => (Tokens.EQ (make_pos(yypos, 1)))
| 37 => (Tokens.AND (make_pos(yypos, 1)))
| 39 => (Tokens.OR (make_pos(yypos, 1)))
| 4 => (lex())
| 41 => (Tokens.NOT (make_pos(yypos, 1)))
| 45 => (Tokens.LET (make_pos(yypos, 1)))
| 48 => (Tokens.BE (make_pos(yypos, 1)))
| 51 => (Tokens.IN (make_pos(yypos, 1)))
| 53 => (ErrorMsg.error yypos 
			 ("Illegal symbol in input: " ^ yytext ^ "\n");
			 lex())
| 7 => (case Int.fromString yytext of
			   NONE => 
			       ErrorMsg.impossible ("Cannot convert" ^ yytext)
			 | SOME f => 
			       let val (start, stop) =
				   make_pos(yypos, String.size yytext) 
			       in
				   Tokens.INT(f,start,stop)
			       end)
| _ => raise Internal.LexerError

		) end )

	val {fin,trans} = Vector.sub(Internal.tab, s)
	val NewAcceptingLeaves = fin::AcceptingLeaves
	in if l = !yybl then
	     if trans = #trans(Vector.sub(Internal.tab,0))
	       then action(l,NewAcceptingLeaves
) else	    let val newchars= if !yydone then "" else yyinput 1024
	    in if (size newchars)=0
		  then (yydone := true;
		        if (l=i0) then UserDeclarations.eof ()
		                  else action(l,NewAcceptingLeaves))
		  else (if i0=l then yyb := newchars
		     else yyb := substring(!yyb,i0,l-i0)^newchars;
		     yygone := !yygone+i0;
		     yybl := size (!yyb);
		     scan (s,AcceptingLeaves,l-i0,0))
	    end
	  else let val NewChar = Char.ord(String.sub(!yyb,l))
		val NewState = if NewChar<128 then Char.ord(String.sub(trans,NewChar)) else Char.ord(String.sub(trans,128))
		in if NewState=0 then action(l,NewAcceptingLeaves)
		else scan(NewState,NewAcceptingLeaves,l+1,i0)
	end
	end
(*
	val start= if substring(!yyb,!yybufpos-1,1)="\n"
then !yybegin+1 else !yybegin
*)
	in scan(!yybegin (* start *),nil,!yybufpos,!yybufpos)
    end
end
  in lex
  end
end
