(chapter "Functions")

(section "Ordinary functions")
(example "Identity function" '(identity [1 2 3]))
(example "Constant function" '((constantly 10) 20 30))

(section "High-order functions")
(example "Function composition" '((comp square square square) 2))
(example "Currying" '(def sum (partial foldLeft' 0 +)))
(example '(sum [1 2 3]))
(example "Juxtaposition" '((juxt + - * /) 1 2 3 4))
(example "Application" '(apply + [1 2 3]))
(example "Map" '(mapv (fn [n] (+ 1 n)) [1 2 3]))

(section "Variable-argument functions")
(defn sumSquares [& xs] (apply + (map square xs)))
(example '(sumSquares 10 20))
