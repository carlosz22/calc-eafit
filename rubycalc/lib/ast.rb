require 'set'

class BinaryNode
  attr_reader :left, :right

  def initialize(left,right)
    @left = left
    @right = right
  end
end

class UnaryNode
  attr_reader :subTree

  def initialize(subTree)
    @subTree = subTree
  end
end

class AddNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end

  def evaluate
    left.evaluate + right.evaluate
  end
end

class SubNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end

  def evaluate
    left.evaluate - right.evaluate
  end
end

class NumNode
  def initialize(num)
    @num = num
  end

  def evaluate
    @num
  end
end

class TimesNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end

  def evaluate
    left.evaluate * right.evaluate
  end
end

class DivideNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end

  def evaluate
    left.evaluate / right.evaluate
  end
end

class ModulNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end

  def evaluate
    left.evaluate % right.evaluate
  end
end

class StoreNode < UnaryNode
  def initialize(sub)
    super(sub)
  end

  def evaluate
    $calc.memory=subTree.evaluate
  end
end

class NumNode
  def initialize(num)
    @num = num
  end

  def evaluate
    @num
  end
end

class PlusNode < UnaryNode
  def initialize(sub)
    super(sub)
  end
  def evaluate
    $calc.memory += subTree.evaluate
    $calc.memory
  end
end

class RecallNode
  def evaluate
    $calc.memory
  end
end

class MinNode < UnaryNode
  def initialize(sub)
    super(sub)
  end
  def evaluate
    $calc.memory -= subTree.evaluate
    $calc.memory
  end
end

class ValueNode
  def initialize(cadena)
    @key = cadena
  end
  def evaluate
    global = "CALCVAR" + @key
    if($calc.environ)
      if $calc.variables.has_key?(global)
        return $calc.variables[global]
      else
        return $calc.variables[@key]
      end
    else
      if $calc.variables.has_key?(@key)
        return $calc.variables[@key]
      else
        return $calc.variables[global]
      end
    end
  end
end

class ClearNode
  def evaluate
    $calc.memory=0
    $calc.memory
  end
end

class AssignNode < UnaryNode
  def initialize(sub, cadena)
    super(sub)
    @key = cadena
  end

  def evaluate
    val=subTree.evaluate
    $calc.assigned = true
    $calc.assignat2.insert(-1, ( @key + "=" + val.to_s ))
    $calc.variables[@key] = val
  end
end
