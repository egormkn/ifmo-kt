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
