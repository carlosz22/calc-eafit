
Gem::Specification.new do |s|
  s.name    = 'calc'
  s.version = '0.9'
  s.date    = '2015-11-25'
  s.summary = 'Another calculator in ruby'
  s.description = 'An calculator implementation on ruby'
  s.author  = 'Kent D. Lee - Juan Francisco Cardona Mc - Carlos Eduardo Zuluaga Pulgarin'
  s.email   = 'czulua20@eafit.edu.co'
  s.homepage = 'http://rubycalc.carloszuluaga.net'
  s.files    = ["lib/token.rb",
                "lib/scanner.rb",
                "lib/ast.rb",
                "lib/parser.rb",
                "lib/calculator.rb",
                "lib/calcex.rb"]
  s.license  = 'ARTISTIC'
  s.executables << 'calc'
end
