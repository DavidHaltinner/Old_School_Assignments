(*   Number 6   *)

fun simultaneous_assign ([], _) = ()
 |  simultaneous_assign(_, []) = ()
 |  simultaneous_assign (r::REF, e::EXP) =  
	let
		fun doit (x, y) = x:=y
	in		
		doit(r,e); 
		simultaneous_assign(REF, EXP) 
	end;

val p = ref 0;
val q = ref 1;
simultaneous_assign([p,q], [!q, !p]);
p;
q;



(*   Number 7   *)
	
abstype account =
 new_account of int * string

with

exception NotLoggedIn
val loggedin=false
fun balance (new_account(i,s)) = if loggedin then i else raise NotLoggedIn (*
fun login (pw) = if s=pw then loggedin:=true "Logged In" else "Wrong Password"

fun withdraw (new_account(i:int,s), money:int)= if loggedin then i:=i-money; i else raise NotLoggedIn
*)


end;
