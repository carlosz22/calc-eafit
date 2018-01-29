require 'ast'
require 'scanner'
require 'token'
require 'calcex'

class Parser
  def initialize(istream)
    @scan = Scanner.new(istream)
    @arrayexpr = []
  end

  def parse
    Prog()
  end

  private
  def Prog
    ListExpr()
    @arrayexpr
  end

  def ListExpr
    t = @scan.getToken
    unless t.type == :eof
      @scan.putBackToken
      newexpr = Expr()
      @arrayexpr.push(newexpr)
      ListExpr()
    end
  end

  def Expr
    RestExpr(Term())
  end

  def RestExpr(e)
    t = @scan.getToken

    if t.type == :add then
         return RestExpr(AddNode.new(e,Term()))
    end

    if t.type == :sub then
      return RestExpr(SubNode.new(e,Term()))
    end

    @scan.putBackToken

    e
  end

  def Term
    # # Write your Term() code here. This code is just temporary
    # # so you can try the calculator out before finishing it.


    return RestTerm(Storable())
  end

  def RestTerm(e)

    t =  @scan.getToken

    if t.type == :times
      return RestTerm(TimesNode.new(e,Storable()))
    end

    if t.type == :divide
      return RestTerm(DivideNode.new(e,Storable()))
    end

    if t.type == :module
      return RestTerm(ModulNode.new(e,Storable()))
    end

    @scan.putBackToken

    e
  end
   def Storable()
     MemOperation(Factor())
   end

  def MemOperation(e)

    t = @scan.getToken
    if t.type == :keyword
      if t.lex == "S"
        return StoreNode.new(e)
      end
      if t.lex == "P"
        return PlusNode.new(e)
      end
      if t.lex == "M"
        return MinNode.new(e)
      end
     end

    @scan.putBackToken
    e

  end

  def Factor

    t = @scan.getToken

    if t.type == :number then
      val = t.lex.to_i
      return NumNode.new(val)
    end

    if t.type == :keyword
      if t.lex == "R"
        return RecallNode.new
      elsif t.lex == "C"
        return ClearNode.new
      elsif
        raise ParseError.new
      end
    end

    if t.type == :lparen
      result = Expr()
      t = @scan.getToken
      if t.type == :rparen
        return result
      end
      raise ParseError.new
    end
    if t.type == :identifier
      cadena = t.lex.to_s
      return Assignable(cadena)
    end
    raise ParseError.new
  end

  def Assignable(val)
    t = @scan.getToken
    if(t.type==:igual)
      return Assign(val)
    end
    @scan.putBackToken
    return ValueNode.new(val)
  end

  def Assign(val)
    result = Expr()
    return AssignNode.new(result,val)
  end
end
