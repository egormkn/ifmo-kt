(def operators {})

(defn constant [value] (fn [variables] (num value)))
(defn variable [name] (fn [variables] (get variables name)))

(defn operator-factory [sym, f] 
  (defn operator [& operands] (
    fn [variables] (
      apply f (map (fn [f] (f variables)) operands)
    )
  ))
  (def operators (assoc operators sym operator))
  (identity operator)
)

(def add (operator-factory '+ +))
(def subtract (operator-factory '- -'))
(def multiply (operator-factory '* *'))
(def divide (operator-factory '/ /))
(def negate (operator-factory 'negate -'))

; TESTS
(def expr 
  (subtract
    (multiply 
      (variable "y")
      (variable "x"))
    (constant 3)))
(println (expr {"y" 5 "x" 2}))

(defn evaluate [operator, & operands] 
  (println operator)
  (apply (get operators operator) (map (fn [x] 
    (cond 
      (number? x) (constant x)
      (list? x) (apply evaluate x)
      (nil? (get operators x)) (variable (str x))
      :else (println "Error")
    )
  ) operands))
)

(defn parseFunction [s] 
  (def parsestr (read-string s))
  (cond 
    (number? parsestr) (constant parsestr)
    (list? parsestr) (apply evaluate parsestr)
    (nil? (get operators parsestr)) (variable (str parsestr))
    :else (println "Error")
  )
)

(println ((parseFunction "10.0") {"x" 2}))