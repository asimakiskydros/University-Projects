import java.util.HashSet;
import java.util.Random;

/**
 * Η κλάση αυτή υλοποιεί την λογική ενός παιχνιδιού "βρες έναν από τους τρεις
 * τυχερούς αριθμούς από το 1 μέχρι το 25". Στο παιχνίδι αυτό, ο υπολογιστής επιλέγει
 * τρεις τυχαίους διαφορετικούς αριθμούς μεταξύ του 1 και του 25. Ο χρήστης έχει έναν
 * αριθμό από προσπάθειες για να μαντέψει έναν από τους τρεις. Σε κάθε προσπάθεια, ο
 * υπολογιστής του απαντάει αν το βρήκε. Αν βρει έναν από τους τρεις ή αν τελειώσουν οι
 * προσπάθειες, το παιχνίδι τελειώνει.
 *
 * This class represents the logic of the game "find one out of three lucky numbers". In this
 * game the computer selects three different random numbers between 1 and 25. The user has a number of
 * tries to guess the number. In every try, the computer responds if the given number exists in the set
 * of the three lucky numbers. If the user founds the number or the number of tries is reached the
 * game is over.
 *
 *  @author Konstantinos Prousalis
 */

public class CheckTheNumbers {

    private int efforts;
    private Random randomizer;
    public HashSet<Integer> hiddenSet;
    private Boolean bingo;
    /**
     * Αρχικοποιεί τη λογική του παιχνιδιού με έναν
     * αριθμό προσπαθειών.
     * <p>
     * Initializes the logic of the game given a number of tries.
     *
     * @param efforts
     */
    public CheckTheNumbers(int efforts) {
        // Συμπληρώστε τον κώδικα
        this.efforts = efforts;
        this.randomizer = new Random();
        this.hiddenSet = new HashSet<>();
        for(int i=0;i<3;i++)
            this.hiddenSet.add(this.randomizer.nextInt(25)+1);
        this.bingo = false; //?
    }

    /**
     * Επιστρέφει τον αριθμό των προσπαθειών που απομένουν.
     * <p>
     * Returns the number of tries that remain.
     *
     * @return προπσπάθειες που απομένουν, the remaining number of tries.
     */
    public int getEfforts() {
        // Συμπληρώστε τον κώδικα
        return this.efforts;
    }

    /**
     * Επιστρέφει τους κρυμμένους αριθμούς.
     * <p>
     * It returns the hidden numbers.
     *
     * @return τους κρυμμένους αριθμούς, the hidden numbers
     */
    public HashSet getHiddenNums() {
        // Συμπληρώστε τον κώδικα
        return this.hiddenSet;
    }

    /**
     * Επιστρέφει αληθές αν ο χρήστης έχει βρει
     * έναν από τους κρυμμένους αριθμούς.
     * <p>
     * It return true if the user guesses one of the the hidden numbers.
     *
     * @return
     */
    public boolean getBingo() {
        // Συμπληρώστε τον κώδικα
        return this.bingo;
    }

    /**
     * Ο χρήστης δίνει μια μαντεψιά.
     * <p>
     * The user guesses.
     *
     * @param x η μαντεψιά του χρήστη, the user's guess.
     * @return 0 αν το βρήκε, 1 αν ο κρυμμένος είναι μεγαλύτερος από αυτόν που
     * έδωσε ο χρήστης, -1 αν ο κρυμμένος είνα μικρότερος από αυτόν που έδωσε
     * ο χρήστης.
     * 0 If the user found the number, 1 if the hidden number is greater than the one given,
     * -1  if the hidden number is smaller than the one given.
     */
    public int userGuessEffort(int x) {
        // Συμπληρώστε τον κώδικα
        this.efforts--;
        if(this.hiddenSet.contains(x)) {
            this.bingo = true;
        }
        return getBingo() ? 1 : 0;
    }
}
