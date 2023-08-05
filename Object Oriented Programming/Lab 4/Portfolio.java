import java.util.HashMap;
import java.util.Iterator;

/**
 * Αυτή η κλάση αναπαριστά το χαρτοφυλάκιο (portfolio) ενός επενδυτή που αγοράζει ξένα νομίσματα με ευρώ.
 * Το χαρτοφυλάκιο αποθηκεύει τις εντολές που δίνει ο επενδυτής για κάθε αγορά ξένου νομίσματος.
 * Οι βασικές παράμετροι της κλάσης είναι ο τίτλος του χαρτοφυλακίου {@code portfolioTitle} και το χαρτοφυλάκιο
 * μέσα στο οποίο καταγράφονται οι εντολές αγοράς ως ζεύγοι: &lt;τύπος ξένου νομίσματος, ακέραιο ποσό σε ευρώ&gt;, π.χ.
 * &lt;currencyΧ,3000&gt; που σημαίνει ότι αγοράστηκε (επένδυση) ποσό ξένου νομίσματος currencyΧ αξίας 3000 ευρώ.
 * Για κάθε τύπο ξένου νομίσματος υπάρχει μόνο μια καταχώρηση στο χαρτοφυλάκιο.
 * <p>
 * This class represents the portfolio of an investor who buys foreign currency exchange using euros.
 * The portfolio registers the orders of the investor for each buying of foreign currency.
 * The basic parameters of the class are the portfolio title  {@code portfolioTitle} and the portfolio
 * in which the buying orders are registered as pairs of: &lt;currency type, integer amount of euros&gt;,
 * e.g. &lt;currencyX, 3000&gt;, which means that an amount of currencyX has been bought for 3000 euros.
 * For each currency type currencyX, there is only one entry in the portfolio.
 *
 * @author Konstantinos Prousalis
 */

public class Portfolio {

    private String portfolioTitle;
    private HashMap<String, Integer> portfolio;

    /**
     * Προκαθορισμένος κατασκευαστής.
     * <p>
     * Default constructor.
     */
    public Portfolio() {
        //portfolioTitle="";
        portfolio = new HashMap<String,Integer>();
    }

    /**
     * Κατασκευαστής που παίρνει ως παράμετρο τον τίτλο του νέου χαρτοφυλακίου
     * <p>
     * Constructor that gets as a parameter the portfolio title
     *
     * @param portfolioTitle Ο τίτλος του χαρτοφυλακίου (the portfolio title)
     */
    public Portfolio(String portfolioTitle) {
        this.portfolioTitle = portfolioTitle;
        portfolio = new HashMap<String,Integer>();
    }

    /**
     * Επιστρέφει τον τύπο του νομίσματος
     * <p>
     * Returns the currency type
     *
     * @return Ο τύπος του νομίσματος (the currency type)
     */
    public String getPortfolioTitle() {
        return this.portfolioTitle;
    }

    /**
     * Μέθοδος για την ενημέρωση του τίτλου του χαρτοφυλακίου
     * <p>
     * Method for updating the portfolio title
     *
     * @param portfolioTitle Ο νέος τίτλος του χαρτοφυλακίου (the new title of the portfolio)
     */
    public void setPortfolioTitle(String portfolioTitle) {
        this.portfolioTitle=portfolioTitle;
    }

    /**
     * Μέθοδος για την επιστροφή του καταλόγου με τις εντολές
     * <p>
     * Method for returning the recorded orders
     *
     * @return Ο κατάλογος με τις εγγραφές των εντολών (the recorded orders)
     */
    public HashMap<String, Integer> getPortfolio() {
        return this.portfolio;
    }

    /**
     * Μέθοδος για την καταχώρηση μιας εντολής, δίνοντας ως παράμετρο τον ξένο τύπο νομίσματος
     * {@code currency}. Η κλήση αυτής της μεθόδου σημαίνει ότι έχει καταχωρηθεί μια εντολή,
     * οπότε στην ουσία καλείται η μέθοδος {@link #registerOrder(String, int)} με εξ ορισμού παράμετρο 100.
     * <p>
     * Method for recording an order of type {@code currency}. This method is used to record a single
     * order, therefore it should call the method {@link #registerOrder(String, int)} with default parameter 100.
     *
     * @param currency Ο τύπος του συναλλαγματικού νομίσματος, π.χ.currencyX (the type of the currency, e.g. currencyX)
     */
    public void registerOrder(String currency) {
        registerOrder(currency,100);
    }

    /**
     * Μέθοδος για την καταχώρηση μιας εντολής για την αγορά ξένου νομίσματος {@code currency} με το ποσό {@code amount} σε ευρώ.
     * Αν ο τύπος νομίσματοςβρίσκεται ήδη στον κατάλογο, τότε θα πρέπει να ενημερώνεται το αντίστοιχο ποσό {@code amount}.
     * Διαφορετικά θα πρέπει να προστίθεται μια νέα καταχώρηση στον κατάλογο.
     * <p>
     * Method for recording in the portfolio an amount {@code amount} of euros for conversion into a foreign currency
     * {@code currency}. If the currency type already exists in the portfolio, then the corresponding number/amount
     * should be updated. Otherwise, a new entry should be created in the portfolio.
     *
     * @param currency Ο τύπος του νομίσματος (the currency type)
     * @param amount Το ποσό σε ευρώ που χρησιμοποιούνται για την εντολή (the amount of euros for the order)
     */
    public void registerOrder(String currency, int amount) {
        if(this.portfolio.containsKey(currency))
            this.portfolio.put(currency,this.portfolio.get(currency)+amount);
        else
            this.portfolio.put(currency,amount);
    }

    /**
     * Μέθοδος για την επιστροφή των νομισμάτων τύπου {@code currency} που υπάρχουν στο πορτφολιο
     * <p>
     * Method for returning the currencies of type {@code currency} that exist in the portfolio
     *
     * @param currency Ο τύπος του νομίσματος για τον οποιο θα επιστραφεί το ποσό (the currency type for which the
     *                amount will be returned)
     * @return Ο αριθμός των νομισμάτων τύπου {@code currency} που υπάρχουν (the number of the currency types {@code currency}
     * that exist in the registry
     */
    public int getAmountOfCurrency(String currency) {
        if(this.portfolio.containsKey(currency))
            return this.portfolio.get(currency);
        else return 0;
    }

    /**
     * Μέθοδος για την επιστροφή ενός πίνακα που περιέχει τα νομίσματα (currencies) των εντολών που υπάρχουν στον κατάλογο.
     * Κάθε νόμισμα πρέπει να υπάρχει μόνο μια φορά στον πίνακα που επιστρέφεται.
     * <p>
     * Method for returning an array with the currencies of the sensors that exist in the portfolio. Each currency should
     * exist only once in the array.
     *
     * @return Ο πίνακας με τους τύπους νομισμάτων (the array with the currency types)
     */
    public String[] getAllCurrencies() {
        String[] allCurrencies = new String[this.portfolio.size()];
        int i = 0;
        for(String currency : this.portfolio.keySet())
            allCurrencies[i++] = currency;
        return allCurrencies;
    }

}
