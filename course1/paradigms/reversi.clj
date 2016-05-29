(def copyright [
    
    "Reversi (Othello) 1.0"
    "by Egor Makarenko"
    "http://github.com/egormkn"
    ""
    "Game still not works but"
    "you can just place your game pieces"
    "on the board to fill it :)"
    ""
    "Moves should be in format `A1` or `A 1`"

])

; =================== Sugaring ===================

; Gets a field from object or its prototype
(defn proto-get [obj, key]
    (cond
        (contains? obj key) (obj key)
        (contains? obj :extends) (recur (:extends obj) key)
        (true) nil
    )
)

; Calls a method of object or its prototype,
; passing the object itself as the first argument
(defn proto-call [obj, key & args]
    (apply (proto-get obj key) (cons obj args))
)

; Creates an alias for method
; Usage: (def getX (method :getX))
(defn method [key]
    (fn method-fn [obj & args] 
        (apply (partial proto-call obj key) args)
    )
)

; Creates an alias for field
; Usage: (def x (method :x))
(defn field [key]
    (fn field-fn [obj] 
        (proto-get obj key)
    )
)

; ================ Game helpers =================

; Increments `x` by a module of `y`
(defn incmod [x y] (mod (inc x) y))

; Gets the square of `x`
(defn square [x] (* x x))

; Checks, whether coordinates are out of bounds
(defn outofbounds [board row col]
    (let [dim (proto-get board :dim)]
        (or (< row 0) (< col 0) (>= row dim) (>= col dim))
    )
)

; Parses the string to integer
(defn parse-int [s] (Integer/parseInt s))

; Reads a point from System.in
; and converts from chess board coordinates
(defn read-point [dim]
    (print "Enter a point (for example, E2): ")
    (let [point (re-matches #"([a-zA-Z])\s{0,1}(\d+)" (read-line))]
        (if (nil? point)
            nil
            [(- dim (parse-int (point 2)))    (- (int (get (point 1) 0)) 65)]
        )
    )
)

; =============== Game structures ===============

; Board prototype, that determines board size,
; fill char and prints the board to console
(def board-prototype {
    :dim 8
    :fill '.
    :total (fn gettotal [this] 
        (reduce + (proto-get this :score))
    )
    :print (fn printboard [this] 
        (let [dim (proto-get this :dim) board (proto-get this :board)]
            (println "\n\n\t Current board state:\n")
            (dotimes [n dim] (println 
                "\t" (- dim n) "" (board n)
            ))
            (print "\n\t     ")
            (dotimes [n dim] (print 
                (char (+ 65 n)) ""
            ))
            (newline)
        )
    )
})

; Board class, that represents its current state
(def board {
    :extends board-prototype
    :board [ ; TODO auto-generation based on dimensions
        ['. '. '. '. '. '. '. '.]
        ['. '. '. '. '. '. '. '.]
        ['. '. '. '. '. '. '. '.]
        ['. '. '. 'X 'O '. '. '.]
        ['. '. '. 'O 'X '. '. '.]
        ['. '. '. '. '. '. '. '.]
        ['. '. '. '. '. '. '. '.]
        ['. '. '. '. '. '. '. '.]
    ]
    :next 0 
    :score [2 2]
})

;======================================================================================================================================

; Player prototype with make-move implementation
(def player-prototype {
    :make-move (fn make-move-fn [this board] ;TODO ====================================================
        (let [point (proto-call this :move board) get (partial proto-get board) sym (proto-get this :sym)]
            (assoc board 
                :board (assoc-in (get :board) point sym)
                :score (assoc (get :score) (get :next) (inc 
                    ((get :score) (get :next))
                ))
                :next (incmod (get :next) 2)
            )
        )
    )
})

(def make-move (method :make-move))

; Human player, that takes moves from System.in
(def human {
    :extends player-prototype
    :name "Neo (you)" ; Wake up, Neo!
    :sym 'X
    :move (fn move-fn [this board]
        (loop [point (read-point (proto-get board :dim))]
            (if (or (nil? point) (outofbounds board (point 0) (point 1)))
                (recur (read-point (proto-get board :dim)))
                point
            )
        )
    )
})

; Computer player, that generates moves 
; by a strategy (not a good one though)
(def robot {
    :extends player-prototype
    :name "Agent Smith" ; Kill all humans!!!1
    :sym 'O
    :move (fn move-fn [this board]
        (loop [point (read-point (proto-get board :dim))]
            (if (or (nil? point) (outofbounds board (point 0) (point 1)))
                (recur (read-point (proto-get board :dim)))
                point
            )
        )
    )
})

(def playerlist [human robot])

(defn toreverse [board sym row col] ;TODO =============================================================
    (if (or (outofbounds board row col) (not= sym (proto-get board :board)))
        [] ; Empty vector
        []
    )
)


(defn init []
    (newline)
    (doseq [s copyright]
        (println "\t" s)
    )
    (newline)
    (doseq [p playerlist] 
        (println "\t"(proto-get p :name) "plays for" (proto-get p :sym))
    )
    
    (proto-call board :print)
    
    (loop [board board] ;CHECK ===================================================================
        (let [playerid (proto-get board :next)]
            (if false ; No moves available ;TODO
                (do 
                    (printf "%s has no moves available!\n" ((playerlist playerid) :name))
                    (recur (assoc board 
                        :next (incmod playerid 2)
                    ))
                )
                (let [player (playerlist playerid) newboard (make-move (playerlist playerid) board)]
                    (proto-call newboard :print)
                    (if (= 
                            (square (proto-get newboard :dim)) 
                            (proto-call newboard :total)
                        )
                        (printf 
                            "%s wins with a score %d:%d" 
                            (player :name) 
                            (first (proto-get newboard :score)) 
                            (second (proto-get newboard :score))
                        )
                        (recur newboard)
                    )
                )
            )
        )
    )
)

(def gameserver {
    :player1 human
    :player2 robot
    :start init
})

(init)