structure SECD = struct

(* ----------Helper function to convert number to string--------------- *)

fun StringOfNum 0 = "0"
 |  StringOfNum 1 = "1"
 |  StringOfNum 2 = "2"
 |  StringOfNum 3 = "3"
 |  StringOfNum 4 = "4"
 |  StringOfNum 5 = "5"
 |  StringOfNum 6 = "6"
 |  StringOfNum 7 = "7"
 |  StringOfNum 8 = "8"
 |  StringOfNum 9 = "9"
 |  StringOfNum n = 
     (StringOfNum(n div 10)) ^ (StringOfNum(n mod 10));


(* ---------This tells the SECD machine how to "fire" a built-in function ----- *)

fun ConApply(Absyn.Op1(_,f1), Absyn.Num m) = Absyn.Num(f1 m)
 |  ConApply(Absyn.Op2(x,f2), Absyn.Num m) = Absyn.Op1((StringOfNum m^x), fn n => f2(m,n))
 |  ConApply(Absyn.Op3(x,f3), Absyn.Num m) = Absyn.Op1((StringOfNum m^x), fn n => f3(m,n,n))
 |  ConApply(_, Absyn.Num m) = Absyn.Num m;

(* --------"Values" on the SECD stack and bound to variables in the environment ------ *)

datatype item = Atomic of Absyn.atom
              | Closure of (Absyn.LambdaExp * env)
and      env  = EmptyEnv
              | Env of string * item * env;

(* --------Return value bound to symbol in environment ---------------- *)

exception LookupErr;

fun Lookup(s,EmptyEnv)       = raise LookupErr
 |  Lookup(s,Env(s',i,env))  = if s=s' then i else Lookup(s,env);

(* -------Instructions in the SECD Control----------------------------- *)

datatype instruction = Ap | Exp of Absyn.LambdaExp;

(* -------------------------------------------------------------------- *)

type stack   = item list
and  control = instruction list;

datatype state = NullState
               | State of (stack * env * control * state);

(* -------All transitions are simulated here--------------------------- *)

fun Step(State(v::S, E, [], State(S',E',C',D'))) = 
      State(v::S', E', C', D')
 |  Step(State(S, E, Exp(Absyn.Var x)::C, D)) = 
      State(Lookup(x,E)::S, E, C, D)
 |  Step(State(S, E, Exp(Absyn.Con v)::C, D)) = 
      State(Atomic v::S, E, C, D)
 |  Step(State(S, E, Exp(Absyn.Abs(x,e))::C, D )) =
      State(Closure(Absyn.Abs(x,e),E)::S, E, C, D)
 |  Step(State(Closure(Absyn.Abs(x,e),E')::(v::S), E, Ap::C, D)) =
      State([], Env(x,v,E'), [Exp e], State(S,E,C,D))
 |  Step(State(Atomic v1::(Atomic v2::S), E, Ap::C, D )) =
      State(Atomic(ConApply(v1,v2))::S, E, C, D)
 |  Step(State(S, E, Exp(Absyn.App(e1,e2))::C, D)) =
      State(S, E, Exp e2::(Exp e1::(Ap::C)), D);

(* -------------------------------------------------------------------- *)

fun Eval e =
 let fun EvalAux(State([v],EmptyEnv,[],NullState)) = v
      |  EvalAux state = EvalAux(Step state)
 in EvalAux(State([],EmptyEnv,[Exp e],NullState)) end;


(* -------------------------------------------------------------------- *)

fun file_eval s = Eval(Parser.file_parse s);

fun console_eval () = Eval(Parser.console_parse());

end
