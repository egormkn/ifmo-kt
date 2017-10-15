(section "Read")

(example '(read-string "(+ x 10 (- x y))"))
(def r (read-string "(+ x 10 (- x y))"))
(example 'r)
(example '(type r))

(println "Types")
(example '(type (nth r 0)))
(example '(type (nth r 1)))
(example '(type (nth r 2)))
(example '(type (nth r 3)))

(println "Symbol conversion")
(example '(= (symbol "x") 'x))
(example '(= "x" (str (symbol "x"))))
