require 'parser'
require 'ast'

class Calculator
attr_accessor :memory
attr_accessor :environ
attr_accessor :variables
attr_accessor :interactMod
attr_accessor :assignat
attr_accessor :assignat2
attr_accessor :assigned
def initialize
  @memory = 0
  @environ = false
  @interactMod = false
  @variables = Hash.new(0)
  @assignat = []
  @assignat2 = []
  @assigned = false
end

def eval(expr)
  parser = Parser.new(StringIO.new(expr))
  ast = parser.parse
  result = []
  ast.each do |temp|
    result.insert(-1, temp.evaluate)
    meter = ""
    if !@assigned then
      assignat.insert(-1, "")
    else
      assignat2.each do |k|
        meter = meter + k + ","
      end
      assignat.insert(-1,(" {" +meter.chomp(",")+"}"))
      assignat2.clear
    end
    @assigned=false
  end
  result
end
end
