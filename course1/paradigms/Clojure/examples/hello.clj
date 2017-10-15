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




(chapter "Custom Functions")

(section "Simple Functions")
(example "Define function" '(defn square [x] (* x x)))
(example "Use function" '(square 8))
(example "Nullary function" '(defn nullary [] 10))
(example '(nullary))
(example "Anonymous functions" '((fn [x] (+ x x)) 10))
(example "Functions as values" (defn twice [f] (fn [a] (f (f a)))))
(example '((twice square) 3))

(section "Recursive Functions")

(defn rec-fib [n]
  (cond
    (= 0 n) 1
    (= 1 n) 1
    :else (+ (rec-fib (- n 1)) (rec-fib (- n 2)))))

(defn iter-fib [n]
  (letfn [(iter-fib' [n a b]
            (if (= 0 n)
              a
              (iter-fib' (- n 1) b (+' a b))))]
    (iter-fib' n 1 1)))

(defn loop-fib [n]
  (loop [n n a 1 b 1]
    (if (= 0 n)
      a
      (recur (- n 1) b (+' a b)))))

(example "Recursive" '(rec-fib 40))
(example "Tail-recursive" '(iter-fib 90))
(example "Loop" '(loop-fib 90))

(section "Pre and Post conditions")
(defn power [a b]
  {:pre [(<= 0 b)]
   :post [(or (= 0 b) (= 0 a) (= 0 (rem % a)))]}
  (cond
    (= 0 b) 1
    (= 1 b) a
    (even? b) (power (* a a) (quot b 2))
    (odd? b) (* a (power a (- b 1)))))

(defn ipower
  "Invalid postcondition"
  [a b]
  {:pre [(<= 0 b)]
   :post [(= 0 (rem % a)), (<= 0 %)]}
  (power a b))

(example "Pre and posconditions ok" '(power 2 5))
(example "Precondition violated" '(power 2 -5))
(example '(power 2 0))
(example "First part of invalid postcondition violated" '(ipower 2 0))
(example '(power -2 3))
(example "Second part of invalid postcondition violated" '(ipower -2 3))



(chapter "Lists")

(example "List" '(list 1 2 "Hello" 3 4))
(example "List variable" '(def lst (list 1 2 "Hello" 3 4)))
(example "List test" '(list? lst))

(println "Operations")
(example "Length" '(count lst))
(example "Head" '(first lst))
(example "Tail" '(rest lst))
(example "Add element" '(cons 0 lst))
(example "Add elements" '(conj lst 0 -1))

(println "Empty list")
(example '(empty? (rest (list 1))))
(example '(empty? (list)))
(example '(empty? ()))
(example '(empty? lst))

(println "Custom functions")

(defn foldLeft
  "Applies a binary operator f to a zero value and all elements of the list, going left to right"
  [zero f items]
  (if (empty? items)
    zero
    (foldLeft (f zero (first items)) f (rest items))))

(defn foldRight [zero f items]
  "Applies a binary operator f to a zero value and all elements of the list, going right to left"
  (if (empty? items)
    zero
    (f (first items) (foldRight zero f (rest items)))))

(example '(foldLeft 0 + (list 1 2 3 4)))
(example '(foldRight 1 * (list 1 2 3 4)))

(section "Tail-call optimisation")

(defn foldLeft' [zero f items]
  (if (empty? items)
    zero
    (recur (f zero (first items)) f (rest items))))

(example '(count (range 1000000)))
(example '(foldLeft 0 + (range 1000000)))
(example '(foldLeft' 0 + (range 1000000)))







(section "Maps")

(example "Map" '{"x" 1 "y" 2})
(def m {"x" 1 "y" 2})
(example 'm)

(println "Tests")
(example '(map? m))
(example '(empty? {}))
(example '(contains? m "x"))

(println "Queries")
(example '(get m "x"))
(example '(get m "z"))
(example '(count m))
(example '(keys m))
(example '(vals m))
(example '(contains? m "x"))

(println "Modifications")
(example '(assoc m "z" 3))
(example '(assoc m "x" 3))




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
