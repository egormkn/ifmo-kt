(def about [
    
    ""
    "Reversi (Othello) 1.0"
    "by Egor Makarenko"
    "http://github.com/egormkn"
    ""
    "Game still not works but you can"
    "just place your game pieces"
    "on the board to fill it :)"
    ""
    "Moves should be"
    "in format `A1` or `A 1`"
    ""
    
])

; =================== Sugaring ===================

; Gets a field from object or its prototype
(defn proto-get [obj key]
    (cond
        (contains? obj key) (obj key)
        (contains? obj :extends) (recur (:extends obj) key)
        (true) nil
    )
)

; Calls a method of object or its prototype,
; passing the object itself as the first argument
(defn proto-call [obj key & args]
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
(defn outofbounds [dim row col]
    (or (< row 0) (< col 0) (>= row dim) (>= col dim))
)

; Aliases
(def start (method :start))
(def printinfo (method :print))
(def make-move (method :make-move))
(def score (field :score))
(def getdim (field :dim))
(def getname (field :name))
(def getboard (field :board))
(def nextid (field :nextid))
(def getsym (field :sym))

; ================= Move functions =================

; Returns a vector of points that will be reversed
; when player put a piece at (row; col)
(defn toreverse [board player row col] ; ----------------------------------------------------------------> TODO
    [row col]
) 

; Checks whether a move is forbidden
; (if no piece will be reversed)
(defn forbidden [board player row col] 
    (zero? (count (toreverse board player row col)))
)

; Reads a point from System.in, performs checks
; and converts from chess board coordinates
(defn read-point [board player]
    (printf "\t%s, enter a point (for example, E2): " (getname player))
    (loop []
        (flush)
        (if-let [point (re-matches #"([a-zA-Z])\s{0,1}(\d+)" (read-line))]
            (let [row (- (getdim board) (Integer/parseInt (point 2))) 
                  col (- (int (get (point 1) 0)) 65)]
                (cond 
                    (outofbounds (getdim board) row col) (do 
                        (print "\tPoint is out of bounds. Try another: ")
                        (recur)
                    )
                    (forbidden board player row col) (do 
                        (print "\tMove is forbidden. Try another: ")
                        (recur)
                    )
                    :else [row col]
                )
            )
            (do 
                (print "\tWrong input format. Try again: ")
                (recur)
            )
        )
    )
)

; =============== Game structures ===============

; Board prototype, that determines board size,
; fill char and prints the board to console
(def board-prototype {
    :dim 8
    :fill '.
    :total (fn total-fn [this] (reduce + (score this)))
    :print (fn print-fn [this] 
        (let [d (getdim this) board (getboard this)]
            (println "\n\n\tCurrent board state:\n")
            (dotimes [n d] (printf "\t%d  %s\n" (- d n) (board n)))
            (print "\n\t    ")
            (dotimes [n d] (printf "%c " (char (+ 65 n))))
            (newline)
            (newline)
            (flush)
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
    :nextid 0 
    :score [2 2]
})

; Player prototype with make-move implementation
(def player-prototype {
    :print (fn print-fn [this]
        (printf "\t%s plays for %s\n" (proto-get this :name) (getsym this))
    )
    :make-move (fn make-move-fn [this board] 
        (assoc board 
            :board (assoc-in ; ---------------------------------------------------------------> TODO
                (getboard board) 
                (proto-call this :move board)
                (getsym this)
            )
            :score (assoc (score board) (nextid board) (inc 
                ((score board) (nextid board))
            ))
            :nextid (incmod (nextid board) 2)
        )
    )
})

; Human player, that takes moves from System.in
(def human {
    :extends player-prototype
    :name "Neo" ; Wake up, Neo!
    :sym 'X
    :move (fn move-fn [this board]
        (read-point board this)
    )
})

; Computer player, that generates moves 
; by a strategy (not a good one though)
(def robot {
    :extends player-prototype
    :name "Agent Smith" ; Kill all humans!!!1
    :sym 'O
    :move (fn move-fn [this board]
        (read-point board this) ; ---------------------------------------------------------------> TODO
    )
})

(def gameserver {
    :print (fn print-fn [this] (doseq [s about] (printf "\t%s\n" s)))
    :start (fn start-fn [this board player1 player2]
        (printinfo this)
        (printinfo player1)
        (printinfo player2)
        (printinfo board)
        (flush)
        
        (loop [board board] ;CHECK ===================================================================
            (let [playerid (proto-get board :nextid) player ([player1 player2] playerid)]
                (if false ; No moves available ;TODO
                    (do 
                        (printf "\n\t%s has no moves available!\n" (player :name))
                        (recur (assoc board 
                            :nextid (incmod playerid 2)
                        ))
                    )
                    (let [newboard (make-move player board)]
                        (printinfo newboard)
                        (when-not (proto-call this :finish board [player1 player2])
                            (recur newboard)
                        )
                    )
                )
            )
        )
    )
    :finish (fn [this board players] ; --------------------------------------------------------------------------> TODO
        (when 
            (or (= 
                    (square (getdim board)) 
                    (proto-call board :total)
                )
                (zero? (reduce * (score board)))
            )
            (let [p1 (first (score board)) p2 (second (score board))]
                (printf
                    "%s wins with a score %d:%d" 
                    (getname (players (if (> p1 p2) 0 1)))
                    p1 
                    p2
                )
            )
        )
    )
})

(start gameserver board human robot)

