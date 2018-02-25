(* Absyn.sml  -- the abstract syntax datatype *)
structure Absyn = 
    struct

(* -------------------------------------------------------------------- *)

datatype atom = Num of int
              | Op1 of string * (int->int)
              | Op2 of string * (int*int->int)
	      | Op3 of string * (int*int*int->int);


(* -------------------------------------------------------------------- *)

type Variable = string;
datatype LambdaExp = Var of Variable 
             | Con of atom
             | App of (LambdaExp * LambdaExp)
             | Abs of (Variable * LambdaExp);

(* -------------------------------------------------------------------- *)



    end
