; Wed Dec 11 12:34:59 EET 2019
; 
;+ (version "3.5")
;+ (build "Build 663")


; ΕΡΓΑΣΙΑ ΑΠΟ ΤΟΥΣ:
;---------------------------------------------------------------------------------------------------------------------
;         ΟΝΟΜΑ        || ΑΕΜ  ||        EMAIL
;===================================================
; Ασημάκης Κύδρος      || 3881 ||  asimakis@csd.auth.gr
; Αντώνης Αποστολούδης || 3897 ||  antoapos@csd.auth.gr
; Γιάννης Δροσσας      || 3890 ||  idrossas@csd.auth.gr
;
; ΣΗΜΕΙΩΣΕΙΣ:
; 1. Αλλάξαμε το πως ορίζεται το pH στην κλάση chemical σε κατηγοριματική οντότητα για ευκολία.
;    Από την πλευρά του χρήστη συνεχίζει να είναι συνεχές νούμερο.
; 2. Κάποια μηνύματα προς τον χρήστη μπορεί να εμφανίζονται με διαφορετική ή συμπληρωματική φορά από
;    αυτή που φαίνεται στα παραδείγματα, δηλαδή α) αν ήταν να ερωτηθεί πρώτα τιμή για το radioactivity
;    και μετά για το spectrometry μπορεί οι ερωτήσεις αυτές να γίνουν ανάποδα και β) αν ήταν να ερωτηθεί
;    εξακρίβωση μόλυνσης στο φρεάτιο 5 μπορεί να ερωτηθεί μόλυνση για το φρεάτιο 4. Σε κάθε περίπτωση η
;    αναμενόμενη σημασιολογία παραμένη σεβαστή, δηλαδή στο παράδειγμα για τα φρεάτια, αν μεταξύ του 5 και 4
;    είναι να υπάρχει μόλυνση, δεν θα ερωτηθεί ποτέ για το φρεάτιο 3.
; 3. Το πρόγραμμα υλοποιήθηκε να είναι όσο πιο γενικό γίνεται και να χρειάζεται τις ελάχιστες αλλαγές για την
;    πρόσθεση νέου χημικού. Η μόνη αλλαγή που απαιτείται είναι η συμπερίληψη του νέου χημικού στην switch-case
;	 της main, και πιθανόν quantification κατά το get-filtered-input ανάλογα με τις ανάγκες του προγραμματιστή.
;


(defclass chemical
	(is-a USER)
	(role concrete)
	(multislot colour
		(type SYMBOL)
		(allowed-values clear red white)
		(default clear)
		(create-accessor read-write))
	(multislot specific_gravity
		(type SYMBOL)
		(allowed-values equal_to_1 above_1 below_1)
		(default equal_to_1)
		(create-accessor read-write))
	(multislot radioactivity
		(type SYMBOL)
		(allowed-values no yes)
		(default no)
		(create-accessor read-write))
	(multislot pH
		(type SYMBOL)
		(allowed-values strongly_acidic weakly_acidic neutral weakly_basic strongly_basic)
		(create-accessor read-write))
	(multislot solubility
		(type SYMBOL)
		(allowed-values soluble insoluble)
		(default soluble)
		(create-accessor read-write))
	(multislot smell
		(type SYMBOL)
		(allowed-values none vinegar choking)
		(default none)
		(create-accessor read-write))
	(multislot hazards
		(type SYMBOL)
		(allowed-values asphyxiation burns_skin explosive highly_toxic_PCBs)
		(create-accessor read-write))
	(multislot spectrometry
		(type SYMBOL)
		(allowed-values none sulphur carbon sodium metal)
		(default none)
		(create-accessor read-write)))

(defclass acid
	(is-a chemical)
	(role concrete)
	(multislot pH
		(type SYMBOL)
		(allowed-values strongly_acidic weakly_acidic)
		(default weakly_acidic)
		(create-accessor read-write)))
 
(defclass strong_acid
	(is-a acid)
	(role concrete)
	(multislot pH
		(type SYMBOL)
		(allowed-values strongly_acidic)
		(default strongly_acidic)
		(create-accessor read-write))
	(multislot hazards
		(type SYMBOL)
		(allowed-values asphyxiation burns_skin explosive highly_toxic_PCBs)
		(default burns_skin)
		(create-accessor read-write)))

(defclass weak_acid
	(is-a acid)
	(role concrete)
	(multislot pH
		(type SYMBOL)
		(allowed-values weakly_acidic)
		(default weakly_acidic)
		(create-accessor read-write)))

(defclass base
	(is-a chemical)
	(role concrete)
	(multislot pH
		(type SYMBOL)
		(allowed-values weakly_basic strongly_basic)
		(default weakly_basic)
		(create-accessor read-write)))

(defclass strong_base
	(is-a base)
	(role concrete)
	(multislot pH
		(type SYMBOL)
		(allowed-values strongly_basic)
		(default strongly_basic)
		(create-accessor read-write))
	(multislot hazards
		(type SYMBOL)
		(allowed-values asphyxiation burns_skin explosive highly_toxic_PCBs)
		(default burns_skin)
		(create-accessor read-write)))

(defclass weak_base
	(is-a base)
	(role concrete)
	(multislot pH
		(type SYMBOL)
		(allowed-values weakly_basic)
		(default weakly_basic)
		(create-accessor read-write)))

(defclass oil
	(is-a chemical)
	(role concrete)
	(multislot pH
		(type SYMBOL)
		(allowed-values neutral)
		(default neutral)
		(create-accessor read-write))
	(multislot solubility
		(type SYMBOL)
		(allowed-values soluble insoluble)
		(default insoluble)
		(create-accessor read-write))
	(multislot spectrometry
		(type SYMBOL)
		(allowed-values none sulphur carbon sodium metal)
		(default carbon)
		(create-accessor read-write)))

(defclass node
	(is-a USER)
	(role concrete)
	(multislot downstream
		(type INSTANCE)
		(create-accessor read-write)))

(defclass store
	(is-a node)
	(role concrete)
	(multislot contents
		(type INSTANCE)
		(cardinality 1 ?VARIABLE)
		(create-accessor read-write)))

(defclass manhole
	(is-a node)
	(role concrete))
	
(definstances facts
	([acetic_acid] of  weak_acid

		(smell vinegar))

	([aluminium_hydroxide] of  weak_base

		(colour white)
		(specific_gravity above_1)
		(spectrometry metal))

	([carbonic_acid] of  weak_acid

		(spectrometry carbon))

	([chromogen_23] of  weak_base

		(colour red)
		(specific_gravity below_1))

	([hydrochloric_acid] of  strong_acid

		(hazards asphyxiation burns_skin)
		(smell choking))

	([manhole_1] of  manhole

		(downstream [manhole_9]))

	([manhole_10] of  manhole

		(downstream [manhole_12]))

	([manhole_11] of  manhole

		(downstream [manhole_13]))

	([manhole_12] of  manhole

		(downstream [monitoring_station]))

	([manhole_13] of  manhole

		(downstream [monitoring_station]))

	([manhole_2] of  manhole

		(downstream [manhole_9]))

	([manhole_3] of  manhole

		(downstream [manhole_9]))

	([manhole_4] of  manhole

		(downstream [manhole_10]))

	([manhole_5] of  manhole

		(downstream [manhole_10]))

	([manhole_6] of  manhole

		(downstream [manhole_11]))

	([manhole_7] of  manhole

		(downstream [manhole_11]))

	([manhole_8] of  manhole

		(downstream [manhole_13]))

	([manhole_9] of  manhole

		(downstream [manhole_12]))

	([monitoring_station] of  node
	)

	([petrol] of  oil

		(hazards explosive)
		(specific_gravity below_1))

	([rubidium_hydroxide] of  weak_base

		(radioactivity yes)
		(specific_gravity above_1)
		(spectrometry metal))

	([sodium_hydroxide] of  strong_base

		(spectrometry sodium))

	([store_1] of  store

		(contents
			[sulphuric_acid]
			[petrol])
		(downstream [manhole_1]))

	([store_2] of  store

		(contents
			[hydrochloric_acid]
			[acetic_acid])
		(downstream [manhole_2]))

	([store_3] of  store

		(contents
			[rubidium_hydroxide]
			[transformer_oil])
		(downstream [manhole_3]))

	([store_4] of  store

		(contents
			[carbonic_acid]
			[acetic_acid]
			[petrol])
		(downstream [manhole_4]))

	([store_5] of  store

		(contents
			[chromogen_23]
			[sulphuric_acid]
			[petrol])
		(downstream [manhole_5]))

	([store_6] of  store

		(contents
			[aluminium_hydroxide]
			[transformer_oil]
			[carbonic_acid])
		(downstream [manhole_6]))

	([store_7] of  store

		(contents
			[hydrochloric_acid]
			[sulphuric_acid])
		(downstream [manhole_7]))

	([store_8] of  store

		(contents
			[acetic_acid]
			[carbonic_acid]
			[sodium_hydroxide])
		(downstream [manhole_8]))

	([sulphuric_acid] of  strong_acid

		(spectrometry sulphur))

	([transformer_oil] of  oil

		(hazards highly_toxic_PCBs))
)

; ===== LOGIC ===== ;

; Print the correct message based on specified metric
(deffunction print-message (?metric)
	; fetch metric's domain
	(bind $?domain (slot-allowed-values chemical ?metric))
	; if special case (pH or specific_gravity) show corresponding range instead
	(if (eq ?metric pH) then (bind $?domain "(0 - 14)"))
	(if (eq ?metric specific_gravity) then (bind $?domain "(0.9 - 1.1)"))
	; print correct message
	(printout t "Specify " ?metric " " $?domain ": ")
)

; Get user input and quantize it into symbol if float/integer.
(deffunction get-filtered-input (?metric)
	; get raw input
	(bind ?user-input (read))
	; normalize to lowercase
	(if (lexemep ?user-input) then (bind ?user-input (lowcase ?user-input)))
	; check input for correctness
	(if (or 
			; case 0: input is neither a number nor a symbol
			(not (or (symbolp ?user-input) (numberp ?user-input)))
			; case 1: input is number when not measuring pH or specific_gravity (and the inverse)
			(and (numberp ?user-input) (not (or (eq ?metric pH) (eq ?metric specific_gravity))))
			; case 2: number input for pH not in range [0, 14]
			(and (numberp ?user-input) (eq ?metric pH) (or (< ?user-input 0) (> ?user-input 14)))
			; case 3: number input for specific_gravity not in range [0.9, 1.1]
			(and (numberp ?user-input) (eq ?metric specific_gravity) (or (< ?user-input 0.9) (> ?user-input 1.1)))
			; case 4: symbol input not an allowed value for specified metric
			(and (symbolp ?user-input) (not (member$ ?user-input (slot-allowed-values chemical ?metric))))
		)
		then 
			; wrong given input, inform user and recursively call self
			(printout t "Wrong input, try again: ") 
			(return (get-filtered-input ?metric))
	)
	; quantize input for the cases of pH and specific gravity
	(if (eq ?metric pH) then
		(if (< ?user-input 3)  then (bind ?user-input strongly_acidic)
		else (if (< ?user-input 6)  then (bind ?user-input weakly_acidic)
		else (if (< ?user-input 8)  then (bind ?user-input neutral)
		else (if (< ?user-input 11) then (bind ?user-input weakly_basic)
		else                             (bind ?user-input strongly_basic)))))
	)
	(if (eq ?metric specific_gravity) then
		(     if (< ?user-input 1) then (bind ?user-input below_1)
		else (if (> ?user-input 1) then (bind ?user-input above_1)
		else                            (bind ?user-input equal_to_1)))
	)
	(return ?user-input)
)

; Get metrics from user and check if all symbols
; are valid metrics.
(deffunction get-metrics ()
	; get raw user input
	(bind $?metrics (explode$ (readline)))
	(foreach ?metric $?metrics
		(if (not (member$ ?metric (delete-member$ (class-slots chemical) hazards))) then
			; unexpected symbol encountered, inform user and recursively call self
			(printout t "Wrong input, try again: ")
			(return (get-metrics))
		)
	)
	(return $?metrics)
)

; Get status for current node by repeatedly asking
; until a correct input is given.
(deffunction get-contamination-status ()
	(bind ?status (read))
	; correct input for status: 'yes' or 'no', case-insensitive
	(if (and (lexemep ?status) (eq (lowcase ?status) yes)) then (return TRUE))
	(if (and (lexemep ?status) (eq (lowcase ?status) no)) then (return FALSE))
	; recursively call self for invalid input
	(printout t "Wrong input, try again: ")
	(return (get-contamination-status))
)

; Get the stream of a store in a list, i.e. the series of manholes
; a possible leak would have to go through to reach the control station
; in order.
(deffunction get-stream (?store)
	(bind $?stream (create$))
	(bind ?next-node ?store)
	(while (neq ?next-node nil) do
		(bind $?stream (create$ $?stream ?next-node))
		(bind ?next-node (send ?next-node get-downstream))
		(if (neq ?next-node nil) then (bind ?next-node (nth$ 1 ?next-node)))
	)
	(return $?stream)
)

(defrule main "First rule to fire. Contains main logic."
	=>
	(bind $?domain (delete-member$ (class-slots chemical) hazards))
	(printout t "Give metrics for evaluation " $?domain ": ")
	; start with all instances of chemical and continuously prune
	; those that dont match the description created by the user's inputs
	(bind $?chemicals (find-all-instances ((?chemical chemical))
						(member$ weakly_basic (slot-allowed-values chemical pH))))
	(foreach ?metric (get-metrics)
		(print-message ?metric)
		(bind ?input-value (get-filtered-input ?metric))
		; find all chemicals that agree with the examined metric's user-specified value
		(switch ?metric
			(case colour           then (bind $?valid-chemicals (find-all-instances ((?chemical chemical)) (member$ ?input-value ?chemical:colour))))
			(case specific_gravity then (bind $?valid-chemicals (find-all-instances ((?chemical chemical)) (member$ ?input-value ?chemical:specific_gravity))))
			(case radioactivity    then (bind $?valid-chemicals (find-all-instances ((?chemical chemical)) (member$ ?input-value ?chemical:radioactivity))))
			(case pH               then (bind $?valid-chemicals (find-all-instances ((?chemical chemical)) (member$ ?input-value ?chemical:pH))))
			(case solubility       then (bind $?valid-chemicals (find-all-instances ((?chemical chemical)) (member$ ?input-value ?chemical:solubility))))
			(case smell            then (bind $?valid-chemicals (find-all-instances ((?chemical chemical)) (member$ ?input-value ?chemical:smell))))
			(case spectrometry     then (bind $?valid-chemicals (find-all-instances ((?chemical chemical)) (member$ ?input-value ?chemical:spectrometry))))
		)
		; each time keep only those that agree on all metrics	
		(bind $?chemicals (intersection$ $?chemicals $?valid-chemicals))
	)
	; fetch all stores containing at least one of the compiled chemicals
	(bind $?stores 
		(find-all-instances ((?store store)) 
							(< 0 (length$ (intersection$ $?chemicals (send ?store get-contents))))
	))
	(while (> (length$ $?stores) 1) do
		; find closest common ancestor of all candidate stores
		(bind $?common-stream (get-stream (nth$ 1 $?stores)))
		(foreach ?store $?stores
			(bind $?common-stream (intersection$ $?common-stream (get-stream ?store)))
		)
		(bind ?cca (nth$ 1 $?common-stream))
		; ask its children (i.e. immediate previous ancestor) for contamination 
		(bind $?children (find-all-instances ((?node node)) (member$ ?cca ?node:downstream)))
		(bind ?flag TRUE)
		(bind ?i 1)
		(bind ?len (length$ $?children))
		(while (and ?flag (<= ?i ?len)) do 
			; if there's only one child remaining, that means all the previous are not contaminated
			; so this must be the contaminated one. no need to ask.
			(bind ?i-child (nth$ ?i $?children))
			(if (= ?i ?len) then 
				(bind ?contaminated-child ?i-child)
				(bind ?flag FALSE)
			else
				; ask for contamination context. if the current manhole turns out to be
				; contaminated, skip all the rest (only one child can be contaminated).
				(printout t "Is there a contamination on " ?i-child " (yes no)?: ")
				(if (get-contamination-status) then 
					(bind ?contaminated-child ?i-child)
					(bind ?flag FALSE))
				(bind ?i (+ ?i 1))
			)
		)
		; remove all stores that had their ancestor disqualified from the above setting.
		(foreach ?other $?stores
			(if (not (member$ ?contaminated-child (get-stream ?other))) then
				(bind $?stores (delete-member$ $?stores ?other))
	)))
	; print results
	(foreach ?chem $?chemicals
		(printout t "Possible contamination culprit: " ?chem crlf)
		(bind $?hazards (send ?chem get-hazards))
		(if (> (length$ $?hazards) 0) then
			(printout t "Possible hazards: " (implode$ ?hazards) crlf)
		))
	(printout t "Source of contamination: " (nth$ 1 $?stores) crlf)
	(halt)
)
