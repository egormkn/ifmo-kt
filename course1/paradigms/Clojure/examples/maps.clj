(section "Maps")

(example "Map" '{"x" 1 "y" 2})
(def m {"x" 1 "y" 2})
(example 'm)

(println "Tests")
(example '(map? m))
(example '(empty? {}))
(example '(contains? m "x"))

(println "Queries")
(example '(get m "x"))
(example '(get m "z"))
(example '(count m))
(example '(keys m))
(example '(vals m))
(example '(contains? m "x"))

(println "Modifications")
(example '(assoc m "z" 3))
(example '(assoc m "x" 3))
