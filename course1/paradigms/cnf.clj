(require '[clojure.string :as string])

; It's impossible to write such complex task on Clojure in 2 hours :(

(defn negate [x] 
    (map (fn [x]
        (cond 
            (= '& x) '|
            (= '| x) '&
            (list? x) (negate x)
            (true) (list '! x)
        )
    ) x)
)

(defn shiftNegate [x]
    (loop [result () e1 (first x) e2 (first (rest x)) other (rest (rest x))]
        (cond
            (nil? e1) (list)
            (nil? e2) (list e1)
            (empty? other) (if 
                (and (= '! e1) (list? e2))
                (do (negate e2) (println e2))
                (conj result e1 e2)
            )
            (= '! e1) (recur (conj result (negate e1)) (first other) (first (rest other)) (rest (rest other)))
            :else (recur (conj result e1) e2 (first other) (rest other))
        )
    )
)

(defn removeDoubleNegate [x] x)

(defn cnf [str] 
    (println (map (fn [x] (if (= x "!") "~" x)) (flatten (removeDoubleNegate (shiftNegate 
        (read-string 
            (string/join " " (map 
                (fn [x] (if (= x "~") "!" x)) 
                (string/split (format "(%s)" str) #"")
            ))
        )
    )))))
)