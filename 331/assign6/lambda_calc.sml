Compiler.Control.Print.printDepth := 80;

structure Parser :
	  sig 
              val file_parse : string -> Absyn.LambdaExp

              val console_parse : unit -> Absyn.LambdaExp

	  end = 
struct

structure LambdaCalcLrVals = LambdaCalcLrValsFun(structure Token = LrParser.Token)
structure Lex = LambdaCalcLexFun(structure Tokens = LambdaCalcLrVals.Tokens)
structure LambdaCalcParser = Join(structure ParserData = LambdaCalcLrVals.ParserData
			   structure Lex=Lex
			   structure LrParser = LrParser)
		      
fun make_get stream = fn _:int => TextIO.input stream
val get_stdIn = make_get TextIO.stdIn
		
fun parseerror(s,p1,p2) = ErrorMsg.error p1 s
			  
fun parse (lexer,outstream:TextIO.outstream) =
    let
	val (absyn, _) = LambdaCalcParser.parse(30,lexer,parseerror,())
    in 
	(TextIO.outputSubstr(TextIO.stdErr,Substring.all 
					       ("Compilation OK: \n"));
	 absyn)
    end handle LrParser.ParseError => raise ErrorMsg.Error
					    
fun parse_stdin ()=
    LrParser.Stream.streamify (Lex.makeLexer get_stdIn)
    
fun file_parse s =
    let
	val _ = ErrorMsg.reset()
	val dev = TextIO.openIn s
	val stream = LrParser.Stream.streamify (Lex.makeLexer(fn i => TextIO.inputN(dev,i)))
	fun parseerror(s,p1,p2) = ErrorMsg.error p1 s
    in 
	let val (absyn, _) = LambdaCalcParser.parse(30,stream,parseerror,())
	in absyn
           before TextIO.closeIn dev
	end
    end

fun console_parse () =
    let
	val _ = ErrorMsg.reset()
	val lexer = parse_stdin()
	fun parseerror(s,p1,p2) = ErrorMsg.error p1 s
    in 
	let val (absyn, _) = LambdaCalcParser.parse(30,lexer,parseerror,())
	in
	    absyn
	end
    end

end
