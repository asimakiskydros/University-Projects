import java.util.ArrayList;
import java.util.List;

/**
 * Αυτή η κλάση αντιπροσωπεύει μιά αεροπορική πτήση. Κάθε πτήση έχει έναν αριθμό, διάρκεια σε ώρες, χωρητικότητα και μια
 * λίστα με τους επιβάτες.
 * <p>
 * This class represents a flight. Each flight has an number, duration in hours, number of seats and a list with the
 * passengers.
 */

public class Flight {
    private String flightNo;
    private int duration; // in hours
    private int seats;
    private List<Passenger> passengers = null;

    /**
     * Κατασκευαστής
     * <p>
     * Instantiates a new Flight
     */
    public Flight() {
        this.passengers = new ArrayList<>();
    }

    /**
     * Επιστρέφει τον αριθμό της πτήσης
     * <p>
     * Gets the flight number.
     *
     * @return ο αριθμός της πτήσης / the flight no
     */
    public String getFlightNo() {
        return flightNo;
    }

    /**
     * Επιστρέφει την λίστα με τους επιβάτες.
     * <p>
     * Gets the list of passengers.
     *
     * @return η λίστα με τους επιβάτες / the list with the passengers
     */
    public List<Passenger> getPassengers() {
        return passengers;
    }

    /**
     * Ενημερώνει τη διάρκεια της πτήσης
     * <p>
     * Updates the flight duration
     *
     * @param duration η διάρκεια της πτήσης (ώρες) / flight duration (hours)
     */
    public void setDuration(int duration) {
        this.duration = duration;
    }

    /**
     * Ενημερώνει την χωρητικότητα της πτήσης
     * <p>
     * Updates the flight seats
     *
     * @param seats οι συνολικές θέσεις της πτήσης / the total seats of the flight duration
     */
    public void setSeats(int seats) {
        this.seats = seats;
    }

    /**
     * Ενημερώνει τον αριθμό της πτήσης. Η μέθοδος ελέγχει για το αν είναι null η τιμή της παραμέτρου. Αν είναι, τότε
     * δεν γίνεται καμιά αλλαγή και επιστρέφει η μέθοδος false. Διαφορετικά, ενημερώνεται ο αριθμός της πτήσης και
     * επιστρέφεται true.
     * <p>
     * Sets flight number. The methods checks if the value provided as input is null. If it is, then the flight number
     * is not updated and the method returns false. Otherwise, the methods updates the flight number and returns true.
     *
     * @param flightNo ένα έγκυρος  αριθμός πτήσης / a valid flight number
     * @return true ή false ανάλογα με το αν ο αριθμός πτήσης είναι έγκυρος / true or false, according to whether the
     * flight number is valid or not
     */
    public boolean setFlightNo(String flightNo) {
        if(flightNo == null)
            return false;
        else
            this.flightNo = flightNo;
            return true;
    }

    /**
     * Μέθοδος που βρίσκει και επιστρέφει τον επιβάτη από τη λίστα με τους επιβάτες που έχει ίδιο το passport id. Αν δεν
     * υπάρχει τέτοιος επιβάτης, επιστρέφει null.
     * <p>
     * It finds and returns the passenger from the list with the passengers that has the same passport id, as the one
     * provided as parameter. If there is no such passenger, it returns null.
     *
     * @param passportId Το passport id του επιβάτη που ψάχνουμε / the passport id of the passenger
     * @return Ο επιβάτης ή null αν δεν βρεθεί κάποιος / the passenger or null if there is no passenger with the same
     * passport
     */
    public Passenger findPassenger(String passportId) {
        if(this.passengers!=null)
            for (Passenger passenger : passengers) {
                if (passenger.getPassportId().equals(passportId))
                    return passenger;
            }
        return null;
    }

    /**
     * Μέθοδος για την προσθήκη ενός επιβάτη στη λίστα με τους επιβάτες της πτήσης. Η μέθοδος ελέγχει αρχικά για το αν
     * υπάρχουν διαθέσιμες (κενές) θέσεις. Αν δεν υπάρχουν, επιστρέφει false. Στην συνέχεια ελέγχει για το αν υπάρχει
     * ήδη κάποιος επιβάτης στην πτήση με το ίδιο passport id. Αν υπάρχει, τότε επιστρέφει false. Διαφορετικά, ο
     * επιβάτης προστίθεται στη λίστα με τους επιβάτες και επιστρέφεται true.
     * <p>
     * Method that adds a passenger to the list of the passengers of the flight. The method first checks if there are
     * empty seats. If there are not, then it returns false. Then, it checks if there is already a passenger in the
     * flight with the same passport id. If there is, then it returns false. Otherwise, the passenger is added to the
     * list with the passengers and it returns true.
     *
     * @param passenger Ο επιβάτης που είναι να προστεθεί / The passenger to be added
     * @return True ή false, ανάλογα με το αν ο επιβάτης έχει προστεθεί στην πτήση ή όχι / True or false, according to
     * whether the passenger has been successfully added to the flight or not.
     */
    public boolean addPassenger(Passenger passenger) {
        if(getEmptySeats() <= 0)
            return false;
        if(passenger == null)
            return false;
        Passenger existingPassenger = findPassenger(passenger.getPassportId());
        if (existingPassenger != null) {
            System.out.printf("There is already a passenger with passport id: %s \n", passenger.getPassportId());
            return false;
        }
        this.passengers.add(passenger);
        return true;
    }

    /**
     * Μέθοδος που επιστρέφει το ποσοστό πληρότητας της πτήσης, δηλαδή τον λόγο του αριθμού των επιβατών προς τις
     * συνολικές θέσεις (χωρητικότητα) της πτήσης.
     * <p>
     * Method that returns the occupancy percentage, that is, the ratio of the number of passengers to the total seats.
     *
     * @return το ποσοστό πληρότητας / the occupancy percentage
     */
    public double getOccupancy() {
        if(this.passengers != null)
            return passengers.size() / (double) seats;

        return 0;
    }

    /**
     * Επιστρέφει τον αριθμό των διαθέσιμων (κενών) θέσεων της πτήσης, δηλαδή χωρητικότητα - καταχωρημένοι επιβάτες.
     * <p>
     * It returns the number of the available (empty) seats, i.e. total seats - registered passengers.
     *
     * @return οι διαθέσιμες (κενές) θέσεις / the available (empty) seats
     */
    public int getEmptySeats() {
        if(this.passengers != null)
            return seats - passengers.size();

        return this.seats;
    }

    /**
     * Επιστρέφει τα ελάχιστα λίτρα καυσίμου που πρέπει να υπάρχουν στην πτήση. Τα λίτρα καυσίμου για μία πτήση
     * υπολογίζονται χρησιμοποιώντας τη μέση κατανάλωση καυσίμου για ένα αεροπλάνο ανά ώρα (μεταβλητή
     * AVERAGE_FUEL_CONSUMPTION_PER_HOUR = 1000) επί τη διάρκεια της πτήσης (σε ώρες). Για ασφάλεια, πρέπει να υπάρχει
     * και 10% περισσότερο καύσιμο στην πτήση. Έτσι αν μια πτήση διαρκεί 1 ώρα, τα ελάχιστα καύσιμα που πρέπει να
     * υπάρχουν στην πτήση είναι 1100 λίτρα.
     * <p>
     * It returns the minimum amount of fuels (in litres) that the flight should have. The amount of fuels for a flight
     * is calculated taking into account the average fuel consumption for a flight (variable
     * AVERAGE_FUEL_CONSUMPTION_PER_HOUR = 1000) times the duration of the flight (in hours). For safety, the flight
     * should have 10% more fuels. For example, if the duration of the flight is 1 hour, then the minimum amount of fuel
     * for the flight is 1100 litres.
     *
     * @return τα ελάχιστα λίτρα καυσίμου για την πτήση / the minimum fuels for the trip
     */
    public double getMinimumFuelsForTheTrip() {
        return CONSTANTS.AVERAGE_FUEL_CONSUMPTION_PER_HOUR * duration * (1 + 0.1);
    }
}
