(ns swingexample
  (:import 
    (javax.swing SwingUtilities JFrame JPanel JLabel JButton)
    (java.awt FlowLayout) 
	(java.awt.event ActionListener)
  )
)

;; wrap GUI construction in a call to invokeLater()
(. SwingUtilities invokeLater 
  (proxy [Runnable] []
    (run []
	  ;; set up the gui
	  (doto (JFrame.) ; generate frame (i.e. window)
		(.setSize  640 480)
		(.setDefaultCloseOperation JFrame/DISPOSE_ON_CLOSE)
		(.add  ; a panel to take care of layout
		  (doto (JPanel. (java.awt.FlowLayout.)) ; add label
				(.add (JLabel. "This GUI was constructed
				from within the event-dispatching
				thread."))
				(.add (doto (JButton. "Press here to
				generate events!") ; add a button
				(.addActionListener
				(proxy
				[java.awt.event.ActionListener] []
					(actionPerformed [e] (println e)))))
				))
		)
		(.setVisible true)
      ) ;; /end event-dispatching thread wrapper
    )
  )
)