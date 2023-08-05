/**
 * Αυτή η κλάση αντιπροσωπεύει έναν επιβάτη. Κάθε επιβάτης έχει ένα passport id, όνομα και επίθετο.
 * <p>
 * This class represents a passenger. Each passenger has a passport id, first name and last name.
 */
public class Passenger {
    private String passportId;
    private String firstName;
    private String lastName;

    /**
     * Επιστρέφει το passport id του επιβάτη
     * <p>
     * Gets the passport id of the passenger
     *
     * @return το passport id / the passport id
     */
    public String getPassportId() {
        return passportId;
    }

    /**
     * Επιστρέφει το όνομα.
     * <p>
     * Gets first name.
     *
     * @return το όνομα / the first name
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Επιστρέφει το επίθετο
     * <p>
     * Gets the last name.
     *
     * @return το επίθετο / the last name
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Μέθοδος για την ενημέρωση του passport id. Η μέθοδος ελέγχει για το αν είναι null η τιμή  της παραμέτρου. Αν
     * είναι, τότε δε γίνεται καμιά αλλαγή και επιστρέφει η μέθοδος false. Διαφορετικά, ενημερώνεται το passport id και
     * επιστρέφεται true.
     * <p>
     * The methods updates the passport id. The method checks if the parameter is null. If it is, then the passport id
     * is not updated and the method returns false. Otherwise, the methods updates the passport id and returns  true.
     *
     * @param passportId το passport id / the passport id
     * @return True ή false, ανάλογα με το αν ενημερώθηκε ή όχι το passport id / True or false, according to whether the
     * passport id has been successfully updated or not.
     */
    public boolean setPassportId(String passportId) {
        if (passportId == null) {
            System.out.println("No value for passport id.");
            return false;
        }
        this.passportId = passportId;
        return true;
    }

    /**
     * Μέθοδος για την ενημέρωση του ονόματος. Η μέθοδος ελέγχει για το αν είναι null η τιμή  της παραμέτρου. Αν είναι,
     * τότε δε γίνεται καμιά αλλαγή και επιστρέφει η μέθοδος false. Διαφορετικά, ενημερώνεται το όνομα και επιστρέφεται
     * true.
     * <p>
     * The methods updates the first name. The method checks if the parameter is null. If it is, then the name is not
     * updated and the method returns false. Otherwise, the methods updates the name  and returns true.
     *
     * @param firstName το όνομα / the first name
     * @return True ή false, ανάλογα με το αν ενημερώθηκε ή όχι το όνομα / True or false, according to whether the name
     * has been successfully updated or not.
     */
    public boolean setFirstName(String firstName) {
        if (firstName == null) {
            System.out.println("No value for first name.");
            return false;
        }
        this.firstName = firstName;
        return true;
    }

    /**
     * Μέθοδος για την ενημέρωση του επιθέτου. Η μέθοδος ελέγχει για το αν είναι null η τιμή της παραμέτρου. Αν είναι,
     * τότε δε γίνεται καμιά αλλαγή και επιστρέφει η μέθοδος false. Διαφορετικά, ενημερώνεται το επίθετο και
     * επιστρέφεται true.
     * <p>
     * The methods updates the surname. The method checks if the parameter is null. If it is, then the surname is not
     * updated and the method returns false. Otherwise, the methods updates the surname and returns true.
     *
     * @param lastName το επίθετο / the surname
     * @return True ή false, ανάλογα με το αν ενημερώθηκε ή όχι το επίθετο / True or false, according to whether the
     * surname has been successfully updated or not.
     */
    public boolean setLastName(String lastName) {
        if (lastName == null) {
            System.out.println("No value for last name.");
            return false;
        }
        this.lastName = lastName;
        return true;
    }
}
