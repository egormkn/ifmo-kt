(chapter "Expressions and variables")

(section "Expressions")

(example "Add" '(+ 2 3))
(example "Subtract" '(- 2 3))
(example "Compound expression" '(+ 2 (- 3 1)))

(example "Variable-args functions" '(- 10 1 2 3))
(example "Special cases" '(- 10))
(example "Nullary functions" '(+))

(example "Equality" '(= (* 2 3) (+ 3 3)))

(section "Variables")
(example "Define variable" '(def x 10))
(example "Use variable" '(+ x (* x 3)))
(example "Output variable " '(println x))
(example "Output function" '+)
(example "Variable as a function" '(x 10))

(section "Simple types")
(example "Integers" '(type 10))
(example "Floating-point" '(type 10.0))
(example "Rational" '(type 2/3))
(example "String" '(type "\"Hello\""))
(example "Booleans" '(type true))
(example "Type conversion" '(double 2/3))
                            