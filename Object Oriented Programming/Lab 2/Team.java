/**
 * Αυτή η κλάση αναπαριστά μια ομάδα εργασίας φοιτητών που αποτελείται από δύο φοιτητές (Student κλάση).
 * This class represents a team consisting of two students (Student class)
 */
public class Team {

    private Student student1;
    private Student student2;
    // Δημιουργήστε έναν κατασκευαστή που να δέχεται ως όρισματα τους 2 φοιτητές.
    // Create a constructor that has as parameters the 2 students.
    public Team(Student student1,Student student2){
        this.student1=student1;
        this.student2=student2;
    }

    /**
     * Μέθοδος που επιστρέφει τον 1ο φοιτητή της ομάδας.
     * This method should return the 1st student of the team.
     */
    public Student getStudent1() {
        return this.student1;
    }

    /**
     * Μέθοδος που επιστρέφει τον 2ο φοιτητή της ομάδας.
     * This method should return the 2nd student of the team.
     */
    public Student getStudent2() {
        return this.student2;
    }

    /**
     * Μέθοδος που αλλάζει τον 1ο φοιτητή της ομάδας.
     * This method should change the 1st student of the team.
     */
    public void setStudent1(Student student1) {
        this.student1=student1;
    }

    /**
     * Μέθοδος που αλλάζει τον 2o φοιτητή της ομάδας.
     * This method should change the 2nd student of the team.
     */
    public void setStudent2(Student student2) {
        this.student2=student2;
    }

    /**
     * Δοθέντος έναν αριθμό από projects αυτή η μέθοδος επιστρέφει το project (αριθμό) που πρέπει
     * υλοποιήσει η ομάδα -> ("Άθροισμα των ΑΕΜ" modulo #projects) + 1
     * Given a number of projects, this method returns the project number the team should take.
     * The formula is -> ("sum of IDs" modulo #projects) + 1
     */
    public int getProject(int projects) {
        return (student1.getId()+student2.getId())%projects +1;
    }

    /**
     * Αυτή η μέθοδος ελέγχει αν οι φοιτητές της ομάδας παρακολουθούν το ίδιο εργαστηριακό τμήμα δοθέντος
     * το αριθμό των τμημάτων.
     * This method checks if the team's students are in the same lab given the total number of labs.
     */
    public boolean sameLab(int labs) {
        return student1.getLab(labs)==student2.getLab(labs);
    }


}
