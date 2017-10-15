(chapter "Evaluation Order")

(defn indented [& xs]
  (apply println (cons "       " xs)))

(defn list-concat [& xss]
  (apply list (apply concat xss)))

(defn trace [x]
  (indented "trace" x)
  x)

(section "Applicative evaluation order")
(defn add-app [a b]
  (indented "evaluate f")
  (+ a b))

(example '(add-app (trace 1) (trace 2)))
(example '(let [v (trace 2)] (add-app v v)))

(section "Normal evaluation order")
(defn add-norm [x y]
  (indented "evaluate f")
  (+ (eval x) (eval y)))
(example '(add-norm '(trace 1) '(trace 2)))
(example '(let [v '(trace 2)] (add-norm v v)))

(section "Lazy evaluation order")
(defn add-lazy [x y]
  (indented "evaluate f")
  (+ (force x) (force y)))
(example '(add-lazy (delay (trace 1)) (delay (trace 2))))
(example '(let [v (delay (trace 2))] (add-lazy v v)))

(section "Streams")
(defn sCons [head tail] [head tail])
(defn sFirst [[head tail]] head)
(defn sRest [[head tail]] (force tail))
(def sNil nil)
(def sEmpty? (partial = sNil))
(defn sTake [n stream]
  (if (pos? n)
    (sCons (sFirst stream) (delay (sTake (- n 1) (sRest stream))))))
(defn sToList [stream]
  (if (sEmpty? stream)
    '()
    (cons (sFirst stream) (sToList (sRest stream)))))
(defn sMap [f stream]
  (sCons (f (sFirst stream)) (delay (sMap f (sRest stream)))))
(defn sFilter [f stream]
  (cond
    (sEmpty? stream) sNil
    (f (first stream)) (sCons (first stream) (delay (sFilter f (sRest stream))))
    :else (sFilter f (sRest stream))))
(defn sTakeWhile [p? stream]
  (cond
    (sEmpty? stream) sNil
    (p? (sFirst stream)) (sCons (sFirst stream) (delay (sTakeWhile p? (sRest stream))))
    :else sNil))
(defn sAny? [p? stream]
  (cond
    (sEmpty? stream) false
    (p? (sFirst stream)) true
    :else (sAny? p? (sRest stream))))

(println "Finite streams")
(example '(sEmpty? sNil))
(example '(sEmpty? (sCons 1 nil)))
(example '(sCons 1 (sCons 2 (sCons 3 nil))))
(example '(sTake 2 (sCons 1 (sCons 2 (sCons 3 nil)))))
(example '(sToList (sTake 2 (sCons 1 (sCons 2 (sCons 3 nil))))))
(example '(sToList (sFilter odd? (sCons 1 (sCons 2 (sCons 3 nil))))))
(example '(sToList (sTakeWhile (partial >= 2) (sCons 1 (sCons 2 (sCons 3 nil))))))
(example '(sAny? (partial = 2) (sCons 1 (sCons 2 (sCons 3 nil)))))
(example '(sAny? (partial = 4) (sCons 1 (sCons 2 (sCons 3 nil)))))

(println "Infinite streams")
(def stream-ones (sCons 1 (delay stream-ones)))
(defn stream-integers [i] (sCons i (delay (stream-integers (+ i 1)))))
(def primes
  (letfn [(prime? [n] (not (sAny? (fn [d] (= 0 (mod n d))) (sTakeWhile (fn [d] (>= n (* d d))) (prs)))))
          (prs [] (sCons 2 (delay (sFilter prime? (stream-integers 3)))))]
    (prs)))

(example '(sToList (sTake 10 stream-ones)))
(example '(sToList (sTake 10 stream-integers)))
(example '(sToList (sTake 10 (sMap (partial * 10) (stream-integers 0)))))
(example '(sToList (sTake 10 primes)))

(section "Lazy sequences")
(defn lazy-integers [i] (cons i (lazy-seq (lazy-integers (+ i 1)))))
(def lazy-primes
  (letfn [(prime? [n] (not-any? (fn [d] (= 0 (mod n d))) (take-while (fn [d] (>= n (* d d))) (prs))))
          (prs [] (cons 2 (filter prime? (lazy-integers 3))))]
    (prs)))
(example '(apply list (take 10 (letfn [(lazy-ones [] (cons 1 (lazy-seq (lazy-ones))))] (lazy-ones)))))
(example '(apply list (take 10 (lazy-integers 0))))
(example '(apply list (take 10 lazy-primes)))
