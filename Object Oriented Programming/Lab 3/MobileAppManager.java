/**
 * Αυτή η κλάση αναπαριστά ένα σύστημα που διαχειρίζεται ένα σύνολο από μικροεφαρμογές φορητών συσκευών που
 * διατίθενται προς χρήση του κοινού, όπως π.χ. το PlayStore. Τα βασικά χαρακτηριστικά του συστήματος είναι:
 * ο τίτλος του συστήματος διαχείρισης και η λίστα όπου θα καταχωρούνται τα αντικείμενα των μικροεφαρμογών.
 *
 * <p>
 * This class represents a mobile app manager system. The most basic characteristics are:  the title of the
 * manager system and the list that registers the apps.
 */

import java.util.ArrayList;


public class MobileAppManager {

    String managerTitle;
    ArrayList<MobileApp> apps;

    public MobileAppManager(String managerTitle) {
        this.managerTitle=managerTitle;
        apps=new ArrayList<>();
    }


    /**
     * Μέθοδος που επιστρέφει τον τίτλο
     * Method for returning the title
     */
    public String getManagerTitle() {
        return this.managerTitle;
    }

    /**
     * Μέθοδος που ενημερώνει τον τίτλο του συστήματος διαχείρισης μικροεφαρμογών (app manager)
     * <p>
     * Method for updating the title of the manager system
     */
    public void setManagerTitle(String managerTitle) {
        this.managerTitle=managerTitle;
    }

    /**
     * Μέθοδος που επιστρέφει τη λίστα με τις μικροεφαρμογές
     * <p>
     * Method for returning the list with the apps
     */
    public ArrayList<MobileApp> getAppList() {
        return this.apps;
    }


    /**
     * Μέθοδος που προσθέτει μια μικροεφαρμογή στη λίστα του manager
     * <p>
     * Method for adding a app to the manager list
     */
    public void addApp(String titleName, int capacity, int starRate, int downloads, boolean hasAdv) {
        apps.add(new MobileApp(titleName,capacity,starRate,downloads,hasAdv));
    }

    /**
     * Μέθοδος που επιστρέφει τον συνολικό αριθμό των downloads των μιρκοεφαρμογών του manager. Η μέθοδος δέχεται
     * ως παράμετρο τo αν θέλουμε τα downloads να υπολογιστούν μόνο για τις μικροεφαρμογές που έχουν διαφήμιση ή όχι
     * <p>
     * Method for returning the total number of downloads of the app manager. The method accepts as parameter a
     * boolean value according to whether or not we want the number of downloads to be computed only for blog
     * posts that have advertisement.
     */
    public int getDownloads(boolean withoutAdv) {
        int sumDownloads=0;
        int sumAdds=0;
        for(MobileApp app:apps){
            if(app.hasAdv())
                sumAdds+=app.getDownloads();
            sumDownloads+=app.getDownloads();
        }
        return withoutAdv ? sumDownloads-sumAdds : sumDownloads;
    }

    /**
     * Μέθοδος που επιστρέφει τον μέσο αριθμό λήψεων (downloads) που έχουν οι μικροεφαρμογές του manager
     * <p>
     * Method for returning the average number of downloads of the manager
     */
    public double getAverageStarRate() {
        int sumStars=0;
        if(apps.size()==0)
            return 0;
        for(MobileApp app:apps)
            sumStars+=app.getStars();
        return sumStars/(double)apps.size();
    }

}