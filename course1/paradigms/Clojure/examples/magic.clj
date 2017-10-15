(defn lecture [name]
  (println)
  (println "========================================")
  (println name)
  (println "========================================"))

(defn chapter [name]
  (println)
  (println "==========" name "=========="))

(defn section [name]
  (println)
  (println "----------" name "----------"))


(defn example' [prefix expression]
  (let [result (try
                 (eval expression)
                 (catch Throwable e (str (.getSimpleName (type e)) ": " (.getMessage e))))]
    (println (str "    " prefix expression " -> " result))))
(defn example
  ([description expression] (example' (str description ": ") expression))
  ([expression] (example' "" expression)))
