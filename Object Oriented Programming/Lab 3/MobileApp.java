/**
 * Αυτή η κλάση αναπαριστά μια εφαρμογή που θα μπορούσε να εγκατασταθεί σε μια φορητή υπολογιστική συσκευή.
 * Τα βασικά χαρακτηριστικά της είναι: ο εμπορικός τίτλος (ονομασία), η χωρητικότητα (σε MB), η αξιολόγηση
 * (star-rating 1-5), οι λήψεις (downloads) και το αν έχει διαφημίσεις.
 * <p>
 * This class represents a mobile app. The most basic characteristics are: the trade name, capacity (MB), downloads and
 * whether includes advertisement or not.
 */

public class MobileApp {
    private String title;
    private double capacity;
    private int rating;
    private int downloads;
    boolean hasAds;


    /**
     * Ο προκαθορισμένος κατασκευαστής
     * <p>
     * This is the default constructor
     */
    public MobileApp() {
    }

    /**
     * Κατασκευαστής που αρχικοποιεί τις παραμέτρους της κλάσης
     * <p>
     * The constructor that initialises all the class fields
     */
    public MobileApp(String titleName, double capacity, int starRate, int downloads, boolean hasAdv) {
        this.title=titleName;
        this.capacity=capacity;
        this.rating=starRate;
        this.downloads=downloads;
        this.hasAds=hasAdv;
    }
    /**
     * Μέθοδος που επιστρέφει τον τίτλο
     * <p>
     * Method for returning the title
     */
    public String getTitleName() {
        return this.title;
    }


    /**
     * Μέθοδος που αλλάζει τον τίτλο της μικροεφαρμογής
     * <p>
     * Method for updating the title of the app
     */
    public void setTitleName(String titleName) {
        this.title=titleName;
    }

    /**
     * Μέθοδος που επιστρέφει τη χωρητικότητα της μικροεφαρμογής
     * <p>
     * Method for returning the capacity of the app
     */
    public double getCapacity() {
        return this.capacity;
    }

    /**
     * Μέθοδος που ενημερώνει τη χωρητικοτητα σε MB
     * <p>
     * Method for updating the capacity into MB
     */
    public void setCapacity(double capacity) {
        this.capacity=capacity;
    }

    /**
     * Μέθοδος που επιστρέφει τα likes
     * <p>
     * Method for returning the likes
     */
    public int getStars() {
        return this.rating;
    }
    /**
     * Μέθοδος που ενημερώνει το βαθμό ικανοποιήσης του πελάτη (1-5 αστέρια)
     * <p>
     * Method for updating the customer's satisfactions level (1-5 stars)
     */
    public void setStars(int starRate) {
        this.rating=starRate;
    }

    /**
     * Μέθοδος που επιστρέφει τις φορές που έλαβαν την μικροεφαρμογή
     * <p>
     * Method for returning the download times of the app
     */
    public int getDownloads() {
        return this.downloads;
    }

    /**
     * Μέθοδος που ενημερώνει τις λήψεις
     * <p>
     * Method for updating the downloads times
     */
    public void setDownloads(int downloads) {
        this.downloads=downloads;
    }

    /**
     * Μέθοδος που επιστρέφει true ή false ανάλογα με το αν έχει η εφαρμογή διαφημίσεις
     * <p>
     * Method for returning true or false according to whether the post has advertisement or not
     */
    public boolean hasAdv() {
        return this.hasAds;
    }

    /**
     * Μέθοδος που ενημερώνει αν υπάρχει εικόνα
     * <p>
     * Method for updating the hasImage field
     */
    public void setHasAdv(boolean hasAdv) {
        this.hasAds=hasAdv;
    }

    /**
     * Μέθοδος που επιστρέφει το conversion rate της μικροεφαρμογής. Το conversion rate υπολογίζεται ως ο λόγος
     * των λήψεων (download rating) προς τον αριθμό των ψήφων (star rating)
     * <p>
     * Method for returning the conversion rate of the post. It is calculated as the number of downloads divided
     * by the star rate of the app
     */
    double getConversionRate() {
        if(getDownloads()>0 && getStars()>0)
            return getStars()/(double)getDownloads();
        else return 0;
    }

}