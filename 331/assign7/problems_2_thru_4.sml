use "infinite_seq.sml";

(*   Number 2   *)

fun fib 0 = 0
  | fib 1 = 1
  | fib n = fib(n-2) + fib(n-1);
fun fff (Cons(p,thunk))=Cons(fib p,Freeze(fn()=>fff (Seq.thaw(thunk))));
val fib_stream = fff (Seq.from 1);
Seq.take(fib_stream, 6);

(*   Number 3   *)

fun merge (Nil, A) = A
  | merge (A, Nil) = A
  | merge (Cons(a, thunk), Cons(b,thunk2)) = if a<b then Cons(a, Cons(b, Freeze(fn()=>merge(Seq.thaw(thunk),Seq.thaw(thunk2))))) else Cons(b, Cons(a, Freeze(fn()=>merge(Seq.thaw(thunk),Seq.thaw(thunk2)))));

val ints=Seq.from 1;
val abc=merge(ints,primes);
Seq.take(abc,30);

(*   Number 4   *)

val fb2 = Seq.iterates (fn n=> (2+n)) 2;
val fb3 = Seq.iterates (fn n=> (3+n)) 3;
val fb5 = Seq.iterates (fn n=> (5+n)) 5;
val strange_sequence = Cons(1, merge(merge(fb2, fb3), fb5));
Seq.take(strange_sequence,30);
