(**** Sequences, or Infinite Lists -- An illustration of call-by-name ***)

datatype 'a seq  = Nil
       | Freeze of unit -> 'a seq
       | Cons of 'a * ('a seq);

signature SEQUENCE = 
  sig
  (* Test if sequence is empty *)
  val null : 'a seq -> bool
  (* Return the head of a sequence *)
  val hd : 'a seq -> 'a
  (* Return the tail of a sequence *)
  val tl : 'a seq -> 'a seq
  (* Return a list consisting of first n elements of a sequence *)
  val take : 'a seq * int -> 'a list
  (* Return the sequence of integers from designated starting point*)
  val from : int -> int seq
  (* Return the result of evaluating a delayed sequence *)
  val thaw : 'a seq -> 'a seq

  (* Drop, i.e., lose, the first n elements of a sequence *)
  val drop : 'a seq * int -> 'a seq
  (* The sequence flavor of map *)
  val map : ('a -> 'b) -> 'a seq -> 'b seq
  (* The sequence flavor of filter *)
  val filter : ('a -> bool) -> 'a seq -> 'a seq
  (* Given f and x, form the sequence x, f(x), f(f(x)), f(f(f(x))), ... *)
  val iterates : ('a -> 'a) -> 'a -> 'a seq

  end;

structure Seq : SEQUENCE =
  struct
  exception Empty;

  fun thaw thunk = case thunk of
                     Freeze f => f()
                   | s => s;

  fun hd (Cons(x,thunk)) = x
    | hd Nil = raise Empty;

  fun tl (Cons(x,thunk)) = thaw(thunk)
    | tl Nil = raise Empty;

  fun null (Cons _) = false
    | null Nil      = true;

  fun take (xq, 0) = []
    | take (Cons(x,thunk), n) = x :: take (thaw(thunk), n-1);

  fun from k = Cons(k, Freeze(fn()=> from(k+1)));

  fun drop (xq, 0) = xq
    | drop (Cons(x,thunk), n) = drop (thaw(thunk), n-1);

  fun map f Nil  = Nil
    | map f (Cons(x,thunk)) = Cons(f x, Freeze(fn()=> map f (thaw(thunk))));

  fun filter pred Nil = Nil
    | filter pred (Cons(x,thunk)) =
     if pred x then Cons(x, Freeze(fn()=> filter pred (thaw(thunk))))
          else filter pred (thaw(thunk));

  fun iterates f x = Cons(x, Freeze(fn()=> iterates f (f x)));

  end;

Seq.take(Seq.from 30, 2);

fun squares Nil : int seq = Nil
    | squares (Cons(x,thunk)) = Cons (x*x, Freeze(fn() => squares(Seq.thaw(thunk))));

(** Iterates can generate sequences defined by recurrence relations *)

val powersof2 =  Seq.iterates (fn n => (2 * n)) 1;

(** prime numbers by the sieve of erasthosthenes **)

fun sift p = Seq.filter (fn n => n mod p <> 0);

fun sieve (Cons(p,thunk)) = Cons(p, Freeze(fn()=> sieve (sift p (Seq.thaw(thunk)))));

val primes = sieve (Seq.from 2);


