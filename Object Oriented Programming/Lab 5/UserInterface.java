import java.util.Scanner;
/**
 * Η κλάση αυτή υλοποιεί μια διεπαφή γραμμής εντολών για το παιχνίδι "βρες
 * έναν τυχερό αριθμό"
 *
 * This class represents a console UI for the game "guess a lucky number"
 *
 * @author Konstantinos Prousalis
 */

public class UserInterface {
    private CheckTheNumbers game;
    Scanner scanner;
    /**
     * Constructor of the class.
     *
     * Αρχικοποίηση της κλάσης.
     */
    public UserInterface() {
        // συμπληρώστε τον κώδικα
        this.game = new CheckTheNumbers(10);
        this.scanner = new Scanner(System.in);
    }

    /**
     * Εδώ υλοποιείται όλη η αλληλεπίδραση με τον χρήστη στην γραμμή εντολών
     *
     * This method implements the interaction between the user the console.
     */
    public void start() {
        // Συμπληρώστε τον κώδικα
        int guess;
        while(game.getEfforts()>0 && !game.getBingo()){
            guess = this.scanner.nextInt();
            if(game.userGuessEffort(guess) == 1)
                System.out.println("You won! You found" + guess + ".");
        }
        if(!game.getBingo())
            System.out.print("You lost! ");
        System.out.println("The hidden numbers were: " + game.getHiddenNums());
    }

    /**
     * Εκκίνηση της διεπαφής γραμμής εντολών
     *
     * Starting the console UI.
     *
     * @param args παράμετροι γραμμής εντολών, the parameters of the console.
     */
    public static void main(String[] args) {
        // Συμπληρώστε τον κώδικα
        UserInterface gameCheckTheNumbers = new UserInterface();
        gameCheckTheNumbers.start();
    }
}
