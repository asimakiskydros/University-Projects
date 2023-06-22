# Databases Project

Project header:

Create a database that can fully simulate the following system:

Car Dealership

The dealership has mechanics, sellers*, it may sell new or used cars and it may also accept foreign cars for service.
For each seller the database should hold a unique code and their full name. A seller may sell multiple cars, but a car
can only be sold by a single seller.

For each car the database should hold a unique code, its manufacturer, the model, the color, the year it was manufactured,
its serial number, and also a flag to signify if it is for sale (Y) or for service (N).

For each customer, the database should hold a unique code, their full name, their phone number and their full address
(city, postcode, street name and street number). A customer may buy multiple cars, but every car can be purchased by a 
single customer.

When a sale happens, a seller must issue an invoice/receipt to the customer. A customer must receive one for every car they buy.
when an invoice is issued, the database should hold its code number, the date it was issued and the total price in euros.

A customer may bring as many cars as he likes to the dealership, for service. They may even do so without previously buying any car.
For each car they bring for service to the dealership, they must receive a service ticket. For each such ticket, the database
should hold a unique code, the date the car arrived at the dealership for service, the date it departed, possible comments from 
the mechanics that worked on it and the total price of the work done.

A car that requires service may need multiple mechanics working on it, and each mechanic may work on multiple cars.
For each mechanic, the database should hold a unique code and their full name. For each service and for each mechanic that participated
on it, the database should hold the total work hours spent and possible comments from the aforementioned mechanics.

(* in this project, "vendors" was used instead of "sellers". In hindsight, this translation may or may not be wrong.)

Original header in greek, courtesy of Aristotle University of Thessalonica, CSD:

Η Αντιπροσωπεία Αυτοκινήτων

Η αντιπροσωπεία έχει μηχανικούς, πωλητές, μπορεί να πουλάει καινούργια αλλά και μεταχειρισμένα 
αυτοκίνητα, καθώς επίσης μπορεί να κάνει service σε αυτοκίνητα.
Για κάθε πωλητή καταχωρούμε έναν μοναδικό κωδικό, το επώνυμο και το όνομα του. Ένας πωλητής μπορεί να 
πουλήσει πολλά αυτοκίνητα, αλλά κάθε αυτοκίνητο πωλείται από έναν μόνο πωλητή.
Για κάθε αυτοκίνητο καταχωρούμε έναν μοναδικό κωδικό, την εταιρεία που το κατασκεύασε, το μοντέλο του, το 
χρώμα του, το έτος κατασκευής του, τον σειριακό αριθμό του, καθώς και το αν είναι για πώληση (Υ) ή μόνο για 
επισκευή (Ν).

Για κάθε πελάτη καταχωρούμε έναν μοναδικό κωδικό, το επώνυμο και το όνομα του, το τηλέφωνο επικοινωνίας 
του και την διεύθυνσή του (πόλη, ΤΚ, οδός, αριθμός). Ένας πελάτης μπορεί να αγοράσει πολλά αυτοκίνητα, αλλά 
κάθε αυτοκίνητο αγοράζεται από έναν μόνο πελάτη.

Ένας πωλητής κόβει ένα μόνο τιμολόγιο για κάθε αυτοκίνητο που πουλάει. Ένας πελάτης λαμβάνει τιμολόγιο για 
κάθε αυτοκίνητο που αγοράζει. Όταν κόβεται ένα τιμολόγιο, καταγράφεται ο κωδικός αριθμός του, η ημερομηνία 
έκδοσης του, καθώς και η συνολική αξία σε ευρώ.

Ένας πελάτης μπορεί να έρθει για να επισκευάσει το αυτοκίνητό του στο τμήμα service (χωρίς απαραίτητα να 
έχει αγοράσει το αυτοκίνητο του από την συγκεκριμένη αντιπροσωπεία). Όταν ένας πελάτης φέρνει ένα ή 
περισσότερα αυτοκίνητα για επισκευή, κόβεται ένα εισιτήριο σέρβις για κάθε αυτοκίνητο. Όταν κόβεται ένα 
εισιτήριο σέρβις (και κατά τη διάρκεια της επισκευής), καταγράφεται ένας μοναδικός κωδικός για το εισιτήριο, 
η ημερομηνία εισαγωγής του αυτοκινήτου στο τμήμα σέρβις, η ημερομηνία παραλαβής του αυτοκινήτου από το 
τμήμα σέρβις, σχόλια/παρατηρήσεις για την επισκευή, καθώς επίσης και το κόστος της επισκευής.

Ένα αυτοκίνητο που περνάει στο σέρβις μπορεί να επισκευαστεί από πολλούς μηχανικούς και κάθε μηχανικός 
μπορεί να δουλέψει σε πολλά αυτοκίνητα. Για κάθε μηχανικό καταχωρούμε έναν κωδικό, το επώνυμο του και το 
όνομα του. Για κάθε σέρβις που γίνεται και για κάθε μηχανικό που εργάζεται σε αυτό καταχωρούμε τις ώρες 
εργασίας που απαιτήθηκαν, καθώς επίσης και τα σχόλια του μηχανικού για την επισκευή.
