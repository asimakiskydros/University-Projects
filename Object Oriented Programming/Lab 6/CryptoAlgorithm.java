
/**
 * Μια εταιρεία που σχεδιάζει συστήματα ασφαλείας, θέλει να υλοποιήσει μια βιβλιοθήκη με σκοπό την κρυπτογράφηση και
 * αποκρυπτογράφηση μηνυμάτων. Αρχικά θα υλοποιήσει δύο συγκεκριμένους αλγορίθμους που περιγράφονται στις κλάσεις
 * Algorithm1 & Algorithm2. Τροποποιήστε κατάλληλα το παρακάτω κομμάτι κώδικα ώστε να υλοποιεί ένα interface που
 * να αναπαριστά έναν αλγόριθμο. Κάθε αλγόριθμος κρυπτογράφησης έχεις μέθοδο κρυπτογράφησης και αποκρυπτογράφησης.
 * <p>
 * A company designs security systems and it wants to implement a library in order to cipher and decipher messages.
 * Firstly, it is going to implement two specific algorithms described in classes Algorithm1 and Algorithm2. Modify this
 * code accordingly in order to implement an interface that will represent a ciphering algorithm. Each ciphering algorithm
 * has a method for ciphering and a method for deciphering.
 */

public interface CryptoAlgorithm{
        String encrypt(String message);
        String decrypt(String message);
}
