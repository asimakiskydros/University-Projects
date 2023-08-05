import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;

/**
 * Αυτή η κλάση αναπαριστά ένα ανταλλακτήριο νομισμάτων (κλάση {@link ExchangeMarket}) και κρατάει τα χαρτοφυλάκια των επενδυτών της.
 * <p>
 * This class represents an exchange market company that executes currency-conversion orders ({@link ExchangeMarket} class)
 *
 * @author Konstantinos Prousalis
 */
public class ExchangeMarket {

    private ArrayList<Portfolio> portfolios;

    /**
     * Προκαθορισμένος κατασκευαστής
     * <p>
     * Default constructor
     */
    public ExchangeMarket() {
        portfolios = new ArrayList<Portfolio>();
    }

    /**
     * Μέθοδος για την επιστροφή της λίστας με τa χαρτοφυλάκια (portfolios)
     * <p>
     * Method for returning the list of portfolios
     *
     * @return Η λίστα με τa χαρτοφυλάκια (the list with portfolios)
     */
    public ArrayList<Portfolio> getPortfolios() {
        return this.portfolios;
    }

    /**
     * Μέθοδος για την προσθήκη/καταχώρηση ενός χαρτοφυλακίου (portfolio) στον κατάλογο του ανταλλακτήριου.
     * <p>
     * Method for adding/registering a portfolio
     *
     * @param portfolio Το αντικείμενο του χαρτοφυλακίου που θα προστεθεί στον κατάλογο του ανταλλακτήριου (the portfolio instance that will be added)
     *      
     * @return Ο αριθμός των χαρτοφυλακίων που υπάρχουν στο ανταλλακτήριο, μετά την προσθήκη του νέου χαρτοφυλακίου {@code portfolio}
     * (the number of portfolios that exist in the Exchange Market company , after adding the new one {@code portfolio})
     */
    public int addPortfolio(Portfolio portfolio) {
        this.portfolios.add(portfolio);
        return this.portfolios.size();
    }

    /**
     * Μέθοδος για την επιστροφή του συνολικού αριθμού των τύπων νομισμάτων {@code currencies} που υπάρχουν στο
     * ανταλλακτήριο νομισμάτων
     * <p>
     * Method for returning the total number of currency type {@code currency} that exist in the exchange market
     *
     * @param currency Ο νομισματικός τύπος του οποίου το συνολικό ποσό θα επιστραφεί σε ευρώ (the currency type
     *              whose total amount will be returned in euros)
     * @return Το συνολικό ποσό (the total amount)
     */
    public int getTotalAmountOfCurrency(String currency) {
        int totalValue=0;
        for(Portfolio p : this.portfolios)
            totalValue+=p.getAmountOfCurrency(currency);
        return totalValue;
    }

    /**
     * Μέθοδος για την επιστροφή όλων των νομισματικών τύπων που υπάρχουν στο ανταλλακτήριο
     * <p>
     * Method for returning all the exchange currency types that exist in the Exchange Market
     *
     * @return Σύνολο με τους νομισματικούς τύπους (the set with the currency types)
     */
    public HashSet<String> getAllCurrencyTypes() {
        HashSet<String> currencyTypes = new HashSet<String>();
        for(Portfolio p : this.portfolios){
            for(String currency : p.getPortfolio().keySet())
                currencyTypes.add(currency);
        }
        return currencyTypes;
    }

}
