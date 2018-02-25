functor LambdaCalcLrValsFun(structure Token : TOKEN)
 : sig structure ParserData : PARSER_DATA
       structure Tokens : LambdaCalc_TOKENS
   end
 = 
struct
structure ParserData=
struct
structure Header = 
struct

(*  fun mkprint (expr,pos)  = A.PrintS(expr,pos) *)
(*  fun mkassign name value pos= A.AssignS(name,value,pos) *)
(*  fun mkadd(e1,e2,pos) = A.AddE(e1,e2,pos) *)
(*  fun mkfloat value = A.FloatE(value) *)
(*  fun mkref (id, pos) = (Absyn.make_id(id, pos)) *)


end
structure LrTable = Token.LrTable
structure Token = Token
local open LrTable in 
val table=let val actionRows =
"\
\\001\000\001\000\007\000\002\000\006\000\004\000\005\000\006\000\004\000\000\000\
\\001\000\001\000\007\000\002\000\006\000\004\000\005\000\006\000\004\000\
\\007\000\013\000\008\000\012\000\009\000\011\000\000\000\
\\001\000\001\000\009\000\000\000\
\\001\000\001\000\016\000\000\000\
\\001\000\003\000\014\000\000\000\
\\001\000\005\000\020\000\000\000\
\\001\000\005\000\025\000\000\000\
\\001\000\005\000\026\000\000\000\
\\001\000\005\000\029\000\000\000\
\\001\000\010\000\021\000\000\000\
\\001\000\011\000\027\000\000\000\
\\001\000\012\000\000\000\000\000\
\\001\000\012\000\008\000\000\000\
\\031\000\000\000\
\\032\000\000\000\
\\033\000\000\000\
\\034\000\000\000\
\\035\000\000\000\
\\036\000\000\000\
\\037\000\000\000\
\\038\000\000\000\
\"
val actionRowNumbers =
"\000\000\012\000\002\000\001\000\
\\015\000\014\000\013\000\004\000\
\\000\000\003\000\000\000\000\000\
\\000\000\005\000\009\000\000\000\
\\000\000\016\000\017\000\000\000\
\\006\000\007\000\010\000\019\000\
\\018\000\000\000\008\000\020\000\
\\011\000"
val gotoT =
"\
\\001\000\028\000\002\000\001\000\000\000\
\\000\000\
\\000\000\
\\002\000\008\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\013\000\000\000\
\\000\000\
\\002\000\015\000\000\000\
\\002\000\016\000\000\000\
\\002\000\017\000\000\000\
\\000\000\
\\000\000\
\\002\000\020\000\000\000\
\\002\000\021\000\000\000\
\\000\000\
\\000\000\
\\002\000\022\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\026\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\"
val numstates = 29
val numrules = 8
val s = ref "" and index = ref 0
val string_to_int = fn () => 
let val i = !index
in index := i+2; Char.ord(String.sub(!s,i)) + Char.ord(String.sub(!s,i+1)) * 256
end
val string_to_list = fn s' =>
    let val len = String.size s'
        fun f () =
           if !index < len then string_to_int() :: f()
           else nil
   in index := 0; s := s'; f ()
   end
val string_to_pairlist = fn (conv_key,conv_entry) =>
     let fun f () =
         case string_to_int()
         of 0 => EMPTY
          | n => PAIR(conv_key (n-1),conv_entry (string_to_int()),f())
     in f
     end
val string_to_pairlist_default = fn (conv_key,conv_entry) =>
    let val conv_row = string_to_pairlist(conv_key,conv_entry)
    in fn () =>
       let val default = conv_entry(string_to_int())
           val row = conv_row()
       in (row,default)
       end
   end
val string_to_table = fn (convert_row,s') =>
    let val len = String.size s'
        fun f ()=
           if !index < len then convert_row() :: f()
           else nil
     in (s := s'; index := 0; f ())
     end
local
  val memo = Array.array(numstates+numrules,ERROR)
  val _ =let fun g i=(Array.update(memo,i,REDUCE(i-numstates)); g(i+1))
       fun f i =
            if i=numstates then g i
            else (Array.update(memo,i,SHIFT (STATE i)); f (i+1))
          in f 0 handle Subscript => ()
          end
in
val entry_to_action = fn 0 => ACCEPT | 1 => ERROR | j => Array.sub(memo,(j-2))
end
val gotoT=Array.fromList(string_to_table(string_to_pairlist(NT,STATE),gotoT))
val actionRows=string_to_table(string_to_pairlist_default(T,entry_to_action),actionRows)
val actionRowNumbers = string_to_list actionRowNumbers
val actionT = let val actionRowLookUp=
let val a=Array.fromList(actionRows) in fn i=>Array.sub(a,i) end
in Array.fromList(map actionRowLookUp actionRowNumbers)
end
in LrTable.mkLrTable {actions=actionT,gotos=gotoT,numRules=numrules,
numStates=numstates,initialState=STATE 0}
end
end
local open Header in
type pos = int
type arg = unit
structure MlyValue = 
struct
datatype svalue = VOID | ntVOID of unit | INT of  (int)
 | VAR of  (string) | LambdaExp of  (Absyn.LambdaExp)
 | Program of  (Absyn.LambdaExp)
end
type svalue = MlyValue.svalue
type result = Absyn.LambdaExp
end
structure EC=
struct
open LrTable
val is_keyword =
fn _ => false
val preferred_change = 
nil
val noShift = 
fn _ => false
val showTerminal =
fn (T 0) => "VAR"
  | (T 1) => "INT"
  | (T 2) => "DOT"
  | (T 3) => "LPAREN"
  | (T 4) => "RPAREN"
  | (T 5) => "LAMBDA"
  | (T 6) => "PLUS"
  | (T 7) => "MULT"
  | (T 8) => "LETREC"
  | (T 9) => "BE"
  | (T 10) => "IN"
  | (T 11) => "EOF"
  | _ => "bogus-term"
local open Header in
val errtermvalue=
fn _ => MlyValue.VOID
end
val terms = (T 2) :: (T 3) :: (T 4) :: (T 5) :: (T 6) :: (T 7) :: (T 8
) :: (T 9) :: (T 10) :: (T 11) :: nil
end
structure Actions =
struct 
exception mlyAction of int
local open Header in
val actions = 
fn (i392,defaultPos,stack,
    (()):arg) =>
case (i392,stack)
of (0,(_,(_,_,EOF1right))::(_,(MlyValue.LambdaExp LambdaExp,
LambdaExp1left,_))::rest671) => let val result=MlyValue.Program((
LambdaExp))
 in (LrTable.NT 0,(result,LambdaExp1left,EOF1right),rest671) end
| (1,(_,(MlyValue.VAR VAR,VAR1left,VAR1right))::rest671) => let val 
result=MlyValue.LambdaExp((Absyn.Var(VAR)))
 in (LrTable.NT 1,(result,VAR1left,VAR1right),rest671) end
| (2,(_,(MlyValue.INT INT,INT1left,INT1right))::rest671) => let val 
result=MlyValue.LambdaExp((Absyn.Con(Absyn.Num(INT))))
 in (LrTable.NT 1,(result,INT1left,INT1right),rest671) end
| (3,(_,(MlyValue.LambdaExp LambdaExp,_,LambdaExp1right))::_::(_,(
MlyValue.VAR VAR,_,_))::(_,(_,LAMBDA1left,_))::rest671) => let val 
result=MlyValue.LambdaExp((Absyn.Abs(VAR, LambdaExp)))
 in (LrTable.NT 1,(result,LAMBDA1left,LambdaExp1right),rest671) end
| (4,(_,(_,_,RPAREN1right))::(_,(MlyValue.LambdaExp LambdaExp2,_,_))::
(_,(MlyValue.LambdaExp LambdaExp1,_,_))::(_,(_,LPAREN1left,_))::
rest671) => let val result=MlyValue.LambdaExp((
Absyn.App(LambdaExp1, LambdaExp2)))
 in (LrTable.NT 1,(result,LPAREN1left,RPAREN1right),rest671) end
| (5,(_,(_,_,RPAREN1right))::(_,(MlyValue.LambdaExp LambdaExp2,_,_))::
(_,(MlyValue.LambdaExp LambdaExp1,_,_))::_::(_,(_,LPAREN1left,_))::
rest671) => let val result=MlyValue.LambdaExp((
Absyn.App(Absyn.App(Absyn.Con(Absyn.Op2("+",(op +))),LambdaExp1),LambdaExp2)
))
 in (LrTable.NT 1,(result,LPAREN1left,RPAREN1right),rest671) end
| (6,(_,(_,_,RPAREN1right))::(_,(MlyValue.LambdaExp LambdaExp2,_,_))::
(_,(MlyValue.LambdaExp LambdaExp1,_,_))::_::(_,(_,LPAREN1left,_))::
rest671) => let val result=MlyValue.LambdaExp((
Absyn.App(Absyn.App(Absyn.Con(Absyn.Op2("*",(op * ))),LambdaExp1),LambdaExp2)
))
 in (LrTable.NT 1,(result,LPAREN1left,RPAREN1right),rest671) end
| (7,(_,(_,_,RPAREN1right))::(_,(MlyValue.LambdaExp LambdaExp2,_,_))::
_::(_,(MlyValue.LambdaExp LambdaExp1,_,_))::_::(_,(MlyValue.VAR VAR,_,
_))::_::(_,(_,LPAREN1left,_))::rest671) => let val result=
MlyValue.LambdaExp((Absyn.App(Absyn.Abs(VAR, LambdaExp2), LambdaExp1))
)
 in (LrTable.NT 1,(result,LPAREN1left,RPAREN1right),rest671) end
| _ => raise (mlyAction i392)
end
val void = MlyValue.VOID
val extract = fn a => (fn MlyValue.Program x => x
| _ => let exception ParseInternal
	in raise ParseInternal end) a 
end
end
structure Tokens : LambdaCalc_TOKENS =
struct
type svalue = ParserData.svalue
type ('a,'b) token = ('a,'b) Token.token
fun VAR (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 0,(
ParserData.MlyValue.VAR i,p1,p2))
fun INT (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 1,(
ParserData.MlyValue.INT i,p1,p2))
fun DOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 2,(
ParserData.MlyValue.VOID,p1,p2))
fun LPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 3,(
ParserData.MlyValue.VOID,p1,p2))
fun RPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 4,(
ParserData.MlyValue.VOID,p1,p2))
fun LAMBDA (p1,p2) = Token.TOKEN (ParserData.LrTable.T 5,(
ParserData.MlyValue.VOID,p1,p2))
fun PLUS (p1,p2) = Token.TOKEN (ParserData.LrTable.T 6,(
ParserData.MlyValue.VOID,p1,p2))
fun MULT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 7,(
ParserData.MlyValue.VOID,p1,p2))
fun LETREC (p1,p2) = Token.TOKEN (ParserData.LrTable.T 8,(
ParserData.MlyValue.VOID,p1,p2))
fun BE (p1,p2) = Token.TOKEN (ParserData.LrTable.T 9,(
ParserData.MlyValue.VOID,p1,p2))
fun IN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 10,(
ParserData.MlyValue.VOID,p1,p2))
fun EOF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 11,(
ParserData.MlyValue.VOID,p1,p2))
end
end
