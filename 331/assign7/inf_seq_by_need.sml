datatype 'a seq  = Nil
       | Cons of 'a * ('a seq) ref
       | Freeze of unit -> 'a seq;

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
  end;

structure Seq : SEQUENCE =
  struct
  exception Empty;

  fun from k = Cons(k, ref (Freeze(fn()=> from(k+1))));

  fun thaw thunk = case !thunk of 
	Freeze f => (print "hello\n"; f())
	| s => s;

  fun null Nil = true
    | null (Cons _) = false;

  fun hd Nil = raise Empty
    | hd (Cons(x,_)) = x;

  fun tl Nil = raise Empty
    | tl (Cons(_,thunk)) = thaw thunk;

  fun take (xq, 0) = []
    | take (Nil, n) = []
    | take (Cons(x,thunk), n) = x :: take (thaw thunk, n-1);

  end;


val ints=Seq.from 1;
Seq.take(ints, 5);
