(def operators {})

; Sugaring
(defn proto-get [obj key] (cond (contains? obj key) (obj key) :else (proto-get (:proto obj) key)))
(defn proto-call [obj key & args] (apply (proto-get obj key) (cons obj args)))
(defn method [key] (fn [obj & args] (apply (partial proto-call obj key) args)))
(defn field [key] (fn [obj] (proto-get obj key))) 
(defn constructor [ctor proto] (fn [& args] (apply (partial ctor {:proto proto}) args)))

(def evaluate (method :evaluate))
(def toString (method :toString))
(def diff (method :diff))

(defn Constant [value] 
    {
        :value value
        :proto {
            :evaluate (fn [this, variables] (proto-get this :value))
            :toString (fn [this] (str (proto-get this :value)))
            :diff     (fn [this, variable] (Constant 0))
        }
    }
)

(defn Variable [name] 
    {
        :name name
        :proto {
            :evaluate (fn [this, variables] (get variables (proto-get this :name)))
            :toString (fn [this] (str (proto-get this :name)))
            :diff     (fn [this, variable] (if (= (proto-get this :name) variable) (Constant 1) (Constant 0)))
        }
    }
)

(defn objectFactory [sym, f, d] 
    (defn Operator [& operands] 
        (def object {
            :operands operands
            :f f
            :proto {
                :evaluate (fn [this, variables]
                    (apply (proto-get this :f) (map (fn [o] (evaluate o variables)) operands))
                )
                :toString (fn [this] (str (proto-get this :name)))
                :diff (fn [this, variable] 
                    ;(if (nil? d) 
                        (Constant 0)
                        ;(apply (proto-get this :f) (map (fn [o] (diff o variable)) operands))
                        ;(d this variable)
                    ;)
                )
            }
        })
    )
    (def operators (assoc operators sym Operator))
    (identity Operator)
)

(def Add (objectFactory '+ +' nil))
(def Subtract (objectFactory '- -' nil))
(def Multiply (objectFactory '* *' nil))
(def Divide (objectFactory '/ (fn [a b] (/ (double a) b)) nil))
(def Negate (objectFactory 'negate -' nil))
(def Sin (objectFactory 'sin (fn [x] (Math/sin x)) nil))
(def Cos (objectFactory 'cos (fn [x] (Math/cos x)) nil))


(defn parseObjectType [objectParser, x] (cond 
    (number? x) (Constant x)
    (list? x) (apply objectParser x)
    (nil? (get operators x)) (Variable (str x))
    :else (println "Error")
))

(defn objectParser [operator, & operands] 
    (apply (get operators operator) (map (fn [x] 
        (parseObjectType objectParser x)
    ) operands))
)

(defn parseObject [s]
    (parseObjectType objectParser (read-string s))
)

(println (evaluate (diff (Add (Constant 1) (Constant 2)) "x") {"x" 2 "y" 3}))