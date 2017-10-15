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

(example '(defn foldLeft
  "Applies a binary operator f to a zero value and all elements of the list, going left to right"
  [zero f items]
  (if (empty? items)
    zero
    (foldLeft (f zero (first items)) f (rest items)))))

(example '(defn foldRight [zero f items]
  "Applies a binary operator f to a zero value and all elements of the list, going right to left"
  (if (empty? items)
    zero
    (f (first items) (foldRight zero f (rest items))))))

(example '(foldLeft 0 + (list 1 2 3 4)))
(example '(foldRight 1 * (list 1 2 3 4)))

(section "Tail-call optimisation")

(example '(defn foldLeft' [zero f items]
  (if (empty? items)
    zero
    (recur (f zero (first items)) f (rest items)))))

(example '(count (range 1000000)))
(example '(foldLeft 0 + (range 1000000)))
(example '(foldLeft' 0 + (range 1000000)))
