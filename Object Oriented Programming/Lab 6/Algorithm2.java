/**
 * Η κλάση αναπαριστά έναν αλγόριθμο που κρυπτογραφεί/αποκρυπτογραφεί ένα μήνυμα με πεζούς λατινικούς χαρακτήρες,
 * αντιστρέφοντας τη σειρά των χαρακτήρων, διαχωρίζοντας τους με έναν ειδικό χαρακτήρα (delimiter).
 * Για παράδειγμα, το αποτέλεσμα της κρυπτογράφησης του μηνύματος "this is a java world" θα ήταν ως εξής:
 * "d-l-r-o-w- -a-v-a-j- -a- -s-i- -s-i-h-t".
 * <p>
 * This class represents a ciphering / deciphering algorithm of a text message containing lower-case latin letters. It
 * reverses the sequence of the letters and separates them with a special delimiter. For example, the result of the
 * message "this is a java world" is "d-l-r-o-w- -a-v-a-j- -a- -s-i- -s-i-h-t"
 */
public class Algorithm2 implements CryptoAlgorithm{

    private char delimiter;

    /**
     * Κατασκευαστής της κλάσης / The constructor
     *
     * @param delimiter Το διαχωριστικό του αλγορίθμου / The delimiter used by  the algorithm
     */
    public Algorithm2(char delimiter) {
        // add code
        this.delimiter = delimiter;
    }

    /**
     * Κρυπτογράφηση ενός μηνύματος κειμένου / Ciphering of a text message
     *
     * @param message Το κείμενο / The text message
     * @return Το κρυπτογραφημένο αποτέλεσμα / The ciphered message
     */
    public String encrypt(String message) {
        //add code
        int length1 = 2*message.length() -1;
        int length2 = message.length();
        char[] encryptedMessage = new char[length1];
        char[] copyMessage = message.toCharArray();
        for(int i = length2 -1,j=0; i>=0;i--){
            encryptedMessage[j++] = copyMessage[i];
            if(j<length1)
                encryptedMessage[j++] = this.delimiter;
        }
        return encryptedMessage.toString();
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
        char[] decryptedMessage = message.toCharArray();
        for(int i = 0;i<length;i++)
            if(decryptedMessage[i] == this.delimiter){
                for(int j=i;j<length;j++)
                    decryptedMessage[j]=decryptedMessage[j+1];
            }
        length = decryptedMessage.length;
        for(int i=0,j=length - 1;j>i;i++,j--)
            decryptedMessage[i] = decryptedMessage[j];
        return decryptedMessage.toString();
    }

}
