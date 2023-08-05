
import java.util.ArrayList;
import java.util.List;

/**
 * Η κλάση Crypt, περιλαμβάνει δύο **συλλογές** συμβολοσειρών, μία προς κρυπτογράφηση και μία προς αποκρυπτογράφηση.
 * Στον κατασκευαστή της κλάσης αυτής θα δίνουμε ένα αντικείμενο αλγορίθμου απο/κρυπτογράφησης.
 * <p>
 * This class contains to **lists** of strings, one list for ciphering and the other for deciphering. The class uses the
 * ciphering algorithm given to the constructor.
 */
public class Crypt {
    private List<String> forEncryption;
    private List<String> forDecryption;
    private CryptoAlgorithm crypto;

    /**
     * Ο κατασκευαστής της κλάσης / The constructor of the class
     *
     * @param crypto Ένας αλγόριθμος κρυπτογράφησης / A ciphering algorithm
     */
    public Crypt(CryptoAlgorithm crypto) {
        // add code
        this.crypto = crypto;
        this.forEncryption = new ArrayList<>();
        this.forDecryption = new ArrayList<>();
    }

    /**
     * Προσθήκη συμβολοσειράς προς κρυπτογράφηση / Add of a string for ciphering
     *
     * @param message Η συμβολοσειρά / The string
     */
    public void addForEncryption(String message) {
        // add code
        this.forDecryption.add(message);

    }

    /**
     * Προσθήκη συμβολοσειράς προς αποκρυπτογράφηση / Add of string for deciphering
     *
     * @param message Η συμβολοσειρά / The string
     */
    public void addForDecryption(String message) {
        // add code
        this.forDecryption.add(message);
    }

    /**
     * Επιστρέφει κρυπτογραφημένες τις συμβολοσειρές προς κρυπτογράφηση.
     * It returns the ciphered string that was given for ciphering.
     *
     * @return
     */
    public ArrayList<String> getEncrypted() {
        // add code
        ArrayList<String> encrypted = new ArrayList<>();
        for(String message : this.forEncryption)
            encrypted.add(crypto.encrypt(message));
        return encrypted;
    }

    /**
     * Επιστρέφει αποκρυπτογραφημένες τις συμβολοσειρές προς αποκρυπτογράφηση.
     * It returns the deciphered strings given for deciphering.
     */
    public ArrayList<String> getDecrypted() {
        // add code
        ArrayList<String> decrypted = new ArrayList<>();
        for(String message : this.forDecryption)
            decrypted.add(crypto.decrypt(message));
        return decrypted;
    }


}
