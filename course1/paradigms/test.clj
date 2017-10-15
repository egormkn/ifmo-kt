(defn read-point [dim]
    (print "\tEnter a point (for example, E2): ")
    (flush)
    (let [point (re-matches #"([a-zA-Z])\s{0,1}(\d+)" (read-line))]
        (if (nil? point)
            (println "\tWrong input format. Try again.")
            [(- dim (Integer/parseInt (point 2))) (- (int (get (point 1) 0)) 65)]
        )
    )
)
(def s (re-matches #"([a-zA-Z])\s{0,1}(\d+)" (read-line)))
(read-point 8)