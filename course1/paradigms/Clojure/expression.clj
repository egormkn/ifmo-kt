(def operators {})

(defn constant [value] (fn [variables] value))
(defn variable [name] (fn [variables] (get variables name)))

(defn operatorFactory [sym, f] 
    (defn operator [& operands] 
        (fn [variables] 
            (apply f 
                (map (fn [f] (f variables)) operands)
            )
        )
    )
    (def operators (assoc operators sym operator))
    (identity operator)
)

(def add (operatorFactory '+ +'))
(def subtract (operatorFactory '- -'))
(def multiply (operatorFactory '* *'))
(def divide (operatorFactory '/ (fn [a b] (/ (double a) b))))
(def negate (operatorFactory 'negate -'))
(def sin (operatorFactory 'sin (fn [x] (Math/sin x))))
(def cos (operatorFactory 'cos (fn [x] (Math/cos x))))

(defn parse [x] (cond 
    (number? x) (constant x)
    (list? x) (apply (fn [operator, & operands] 
        (apply (get operators operator) (map (fn [x] 
            (parse x)
        ) operands))
    ) x)
    (nil? (get operators x)) (variable (str x))
    :else (println "Error")
))

(defn parseFunction [s]
    (parse (read-string s))
)