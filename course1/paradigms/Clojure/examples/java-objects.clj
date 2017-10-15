(chapter "Java-like objects")

(section "Interfaces and Classes")

(definterface PtI
  (getX [])
  (getY []))

(deftype Pt [x y]
  PtI
  (getX [this] x)
  (getY [this] y))

(deftype ShiftedPt [x y dx dy]
  PtI
  (getX [this] (+ (.x this) (.dx this)))
  (getY [this] (+ (.y this) (.dy this))))

(def point (Pt. 10 20))
(def shifted-point (ShiftedPt. 10 20 1 2))
(example 'point)
(example '(.x point))
(example '(.y point))
(example '(.getX point))
(example '(.getY point))
(example 'shifted-point)
(example '(.getX shifted-point))
(example '(.getY shifted-point))

(section "Java method implementation")
(deftype Pair [f s]
  Object
  (equals [this that]
    (and (= f (.f that)) (= s (.s that))))
  Comparable
  (compareTo [this that]
    (cond
      (< f (.f that)) -1
      (> f (.f that)) 1
      (< s (.s that)) -1
      (> s (.s that)) 1
      :else 0)))

(example '(= (Pair. 1 2) (Pair. 1 2)))
(example '(= (Pt. 1 2) (Pt. 1 2)))
(example '(.compareTo (Pair. 1 2) (Pair. 1 1)))

(section "Mutable fields")
(definterface MPair
  (getFirst [])
  (getSecond [])
  (setFirst [value])
  (setSecond [value]))
(deftype MutablePair [^{:unsynchronized-mutable true} f
                      ^{:unsynchronized-mutable true} s]
  MPair
  (getFirst [this] f)
  (getSecond [this] s)
  (setFirst [this value] (set! f value))
  (setSecond [this value] (set! s value)))

(def mutable-pair (MutablePair. 1 2))
(defn setPair [pair f s]
  (.setFirst pair f)
  (.setSecond pair s))
(example '(.getFirst mutable-pair))
(example '(.getSecond mutable-pair))
(example '(.setFirst mutable-pair 10))
(example '(.setSecond mutable-pair 20))
(example '(.getFirst mutable-pair))
(example '(.getSecond mutable-pair))
(example '(setPair mutable-pair 100 200))
(example '(.getFirst mutable-pair))
(example '(.getSecond mutable-pair))
