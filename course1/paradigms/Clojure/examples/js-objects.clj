(chapter "JavaScript-like objects")

(section "Maps as objects")
(def point {"x" 10 "y" 20})
(example 'point)
(example "Map as function" '(point "x"))

(section "Keywords")
(def point {:x 10 :y 20})
(example "Keyword" :x)
(example '(= :x (keyword "x")))
(example "Keywords map" 'point)
(example "Keywords as functions" '(:x point))

(section "Prototypes")
(def shifted-point {:dx 1 :dy 2 :y 100 :prototype point})
(example '(defn proto-get [obj key]
  (cond
    (contains? obj key) (obj key)
    :else (proto-get (:prototype obj) key))))
(example '(proto-get shifted-point :dx))
(example '(proto-get shifted-point :x))
(example '(proto-get shifted-point :y))

(section "Methods")
(def point
  {:x 10
   :y 20
   :getX (fn [this] (proto-get this :x))
   :getY (fn [this] (proto-get this :y))
   })
(def shifted-point
  {:dx 1
   :dy 2
   :getX (fn [this] (+ (proto-get this :x) (proto-get this :dx)))
   :getY (fn [this] (+ (proto-get this :y) (proto-get this :dy)))
   :add (fn [this a b] (+ a b))
   :prototype point
   })
(example '(defn proto-call [obj key & args]
  (apply (proto-get obj key) (cons obj args))))
(example '(proto-call point :getX))
(example '(proto-call shifted-point :getX))
(example '(proto-call shifted-point :add 2 3))

(section "Shugaring")
(example '(defn method [key]
  (fn [obj & args] (apply (partial proto-call obj key) args))))
(example '(defn field [key]
  (fn [obj] (proto-get obj key))))

(def _getX (method :getX))
(def _add (method :add))
(def _x (field :x))
(def _y (field :y))
(def _dx (field :dx))
(def _dy (field :dy))

(def point
  {:x 10
   :y 20
   :getX (partial _x)
   :getY (partial _y)
   })
(def shifted-point
  {:dx 1
   :dy 2
   :getX (fn [this] (+ (_x this) (_dx this)))
   :getY (fn [this] (+ (_y this) (_dy this)))
   :add (fn [this a b] (+ a b))
   :prototype point
   })
(example '(_getX point))
(example '(_getX shifted-point))
(example '(_add shifted-point 2 3))
(example '(_x point))
(example '(_x shifted-point))

(section "Constructors")
(example '(def PointPrototype
  {:getX (partial _x)
   :getY (partial _y)
   }))
(example '(defn constructor [ctor prototype]
  (fn [& args] (apply (partial ctor {:prototype prototype}) args))))
(example '(defn Point [this x y]
  (assoc this
    :x x
    :y y)))
(example '(def newPoint (constructor Point PointPrototype)))

(def ShiftedPointPrototype
  (assoc PointPrototype
    :getX (fn [this] (+ (_x this) (_dx this)))
    :getY (fn [this] (+ (_y this) (_dy this)))
    :add (fn [this a b] (+ a b))))
(defn ShiftedPoint [this x y dx dy]
  (assoc (Point this x y)
    :dx dx
    :dy dy
    ))
(def newShiftedPoint (constructor ShiftedPoint ShiftedPointPrototype))

(def point (newPoint 10 20))
(def shifted-point (newShiftedPoint 10 20 1 2))
(example '(_getX point))
(example '(_getX shifted-point))
(example '(_add shifted-point 2 3))
(example '(_x point))
(example '(_x shifted-point))

