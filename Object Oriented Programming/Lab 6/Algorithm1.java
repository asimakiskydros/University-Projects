
import java.util.HashMap;
import java.util.Map;

/**
 * Η κλάση αναπαριστά έναν αλγόριθμο που κρυπτογραφεί / αποκρυπτογραφεί ένα μήνυμα με πεζούς λατινικούς χαρακτήρες,
 * με τη χρήση λεξιλογίου το οποίο αντιστοιχεί κάθε χαρακτήρα σε έναν 2-ψήφιο κωδικό αριθμό.
 * <p>
 * This class represents a cipher / decipher algorithm of a message containing lower-case latin letters, with the use of
 * a dictionary it matches a letter with a 2-digit number.
 */
public class Algorithm1 implements CryptoAlgorithm{

    static final private char[] letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
            'h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p', 'q', 'r', 's', 't', 'u',
            'v', 'w', 'x', 'y', 'z', ' '};
    static final private int[] numbers = {99, 66, 67, 68, 69, 70, 71,
            72, 73, 74, 75, 76, 77, 78,
            79, 80, 81, 82, 83, 84, 85,
            86, 87, 88, 89, 90, 32};
    private Map<Character, Integer> charToInt;
    private Map<Integer, Character> intToChar;

    /**
     * Ο κατασκευαστής της κλάσης / The constructor
     */
    public Algorithm1() {
        // add code
        this.charToInt = new HashMap<>();
        this.intToChar = new HashMap<>();
        for(int i = 0;i<this.letters.length;i++){
            this.charToInt.put(this.letters[i],this.numbers[i]);
            this.intToChar.put(this.numbers[i],this.letters[i]);
        }
    }

    /**
     * Κρυπτογράφηση ενός μηνύματος κειμένου / Ciphering of a text message
     *
     * @param message Το κείμενο / The text message
     * @return Το κρυπτογραφημένο αποτέλεσμα / The ciphered message
     */
    public String encrypt(String message) {
        // add code
        int length = message.length();
        int[] encryptedMessage = new int[length];
        Integer encryptedNumber = 0;
        int mux=1;
        for(int i=0;i<length;i++)
            encryptedMessage[i] = this.charToInt.get(message.charAt(i));
        for(int i=0;i<length;i++){
            encryptedNumber+=encryptedMessage[i]*mux;
            mux*=100;
        }
        return encryptedNumber.toString();
    }

    /**
     * Αποκρυπτογράφηση ενός μηνύματος / Deciphering of a text message
     *
     * @param message Το κρυπτογραφημένο κείμενο / The ciphered message
     * @return Το αποκρυπτογραφημένο κείμενο / The deciphered message
     */
    public String decrypt(String message) {
        // add code
        int length = message.length();
        int copyMessage = Integer.parseInt(message);
        int index = 0;
        char[] decryptedMessage = new char[length/2 + 1];
        int numberPair;
        while(copyMessage>0){
            numberPair = copyMessage%100;
            decryptedMessage[index++] = this.intToChar.get(numberPair);
            copyMessage/=100;
        }
        return decryptedMessage.toString();
    }

}
