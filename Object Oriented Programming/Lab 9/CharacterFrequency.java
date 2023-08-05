import java.io.*;
import java.util.HashMap;

/**
 * Προσθέστε στην κλάση πεδίο/πεδία και συμπληρώστε τις μεθόδους, έτσι ώστε να υπολογίζεται η συχνότητα των χαρακτήρων
 * που υπάρχουν σε ένα αρχείο κειμένου καθώς και να υποστηρίζεται η αποθήκευση και φόρτωση των στατιστικών σε/από
 * δυαδικά αρχεία.
 * <p>
 * Update the class with field(s) and fill in the methods, so as to calculate the frequency of the characters of a text
 * file, as well as to save and retrieve the frequencies to/from binary files.
 */

public class CharacterFrequency {

    HashMap<Character,Integer> data;
    /**
     * Μέθοδος που υπολογίζει τις συχνότητες των χαρακτήρων (γράμμα, αριθμός, σύμβολο, κτλ.) που υπάρχουν σε ένα αρχείο
     * κειμένου, του οποίου το όνομα δίνεται ως παράμετρος. Τα κενά θα πρέπει να αγνοούνται. Όλες οι συχνότητες θα
     * πρέπει να υπολογίζονται αφού γίνει μετατροπή σε πεζούς χαρακτήρες. Τα αποτελέσματα πρέπει να αποθηκεύονται σε
     * κατάλληλη δομή στην κλάση, ώστε να είναι προσβάσιμη και στη μέθοδο saveToBinaryFile(String filename). Για
     * παράδειγμα, για το test_file2.txt τα αποτελέσματα πρέπει να είναι: '1'=1, 'a'=10, '2'=1, 'b'=6, '3'=1, '4'=1,
     * '5'=1, '6'=2, 'h'=2, 'j'=2, '.'=7
     * <p>
     * This method calculates the frequencies of the characters (letters, numbers, symbols, etc.) that exist in a text
     * file, whose name is given as a parameter. Spaces should be skipped. All frequencies should be calculated on
     * lowercase characters (i.e. you need first to convert upper case to lower case). The frequencies should be stored
     * in an appropriate structure in the class, so as to be accessible by the method saveToBinaryFile(String filename).
     * For example, for the test_file2.txt, the results should be: '1'=1, 'a'=10, '2'=1, 'b'=6, '3'=1, '4'=1, '5'=1,
     * '6'=2, 'h'=2, 'j'=2, '.'=7
     *
     * @param filename Το όνομα του αρχείου / The name of the file
     */
    public void countCharacters(String filename) {
        this.data = new HashMap<>();
        try(BufferedReader buffer = new BufferedReader(new FileReader(filename))){
            String line;
            while((line = buffer.readLine()) != null) {
                char[] lineArray = line.toCharArray();
                for (char c : lineArray) {
                    if (c >= 'A' && c <= 'Z')
                        c += 'a' - 'A';
                    if (c != ' ')
                        this.data.put(c, getFrequency(c) + 1);
                }
            }
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    /**
     * Σώζει τη δομή με τις συχνότητες σε ένα δυαδικό αρχείο.
     * <p>
     * It saves the structure with the frequencies in an binary file.
     *
     * @param outputFilename Το όνομα του δυαδικού αρχείου / The name of the binary file
     */
    public void saveToBinaryFile(String outputFilename) {
        try(ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(outputFilename))){
            oos.writeObject(data);
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    /**
     * Φορτώνει τη δομή με τις συχνότητες από το δυαδικό αρχείο.
     * <p>
     * It loads the structure with the frequencies from the binary file.
     *
     * @param file Το όνομα του δυαδικού αρχείου / The name of the binary file.
     */
    public void loadFromBinaryFile(String file) {
        try(ObjectInputStream reader = new ObjectInputStream(new FileInputStream(file))){
            this.data = (HashMap<Character, Integer>) reader.readObject();
        }catch(IOException | ClassNotFoundException e){
            e.printStackTrace();
        }
    }

    /**
     * Επιστρέφει τη συχνότητα ενός χαρακτήρα.
     * <p>
     * It returns the frequency of the character.
     *
     * @param character Ο χαρακτήρας του οποίου θέλουμε τη συχνότητα / The character whose frequency is requested
     * @return Η συχνότητα του χαρακτήρα, 0 αν δεν υπάρχει / The frequency of the character, 0 if it does not exist
     */
    public int getFrequency(char character) {
        return this.data.getOrDefault(character,0);
    }


}
