import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Κλάση που υλοποιεί μια απλή αριθμομηχανή για προσθέσεις και αφαιρέσεις. Δημιουργήστε ένα παράθυρο 300x80 που περιέχει
 * δύο text fields για τους αριθμούς που θα προστεθούν ή θα αφαιρεθούν, ένα κουμπί πρόσθεσης και ένα αφαίρεσης, καθώς
 * και ένα text field για το αποτέλεσμα της πράξης. Προτείνεται η χρήση του FlowLayout. Παράδειγμα:
 * https://drive.google.com/file/d/1MDA9VYuVau2k5SVQbtQrnTgVIvSSMO1f/view?usp=sharing
 *
 * <p>
 * Class that implements a simple calculator for additions and subtractions. Create a frame 300x80 that contains two
 * text fields for the two numbers of the arithmetic operations, one button for the addition and one for the
 * subtractions, as well as one text field for the results. It is recommended to use the FlowLayout. Example:
 * https://drive.google.com/file/d/1MDA9VYuVau2k5SVQbtQrnTgVIvSSMO1f/view?usp=sharing
 */
public class CalculatorFrame extends JFrame/* extend and/or implement accordingly */ {
    JButton buttonAdd;
    JButton buttonSub;
    JTextField field1;
    JTextField field2;
    JTextField fieldRes;
    // insert fields

    public void startGUI() {
        // insert code
        this.setTitle("Calculator");
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(new FlowLayout());
        this.setSize(new Dimension(300,80));
        buttonAdd = new JButton("+");
        buttonSub = new JButton("-");


        field1 = new JTextField();
        field2 = new JTextField();
        fieldRes = new JTextField();
        field1.setPreferredSize(new Dimension(60,30));
        field2.setPreferredSize(new Dimension(60,30));
        fieldRes.setPreferredSize(new Dimension(60,30));
        this.add(buttonAdd);
        this.add(buttonSub);
        this.add(field1);
        this.add(field2);
        this.add(fieldRes);
        ActionListener buttonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println(e.getActionCommand());
                String text1 = field1.getText();
                String text2 = field2.getText();
                if(e.getActionCommand().equals("+")){
                    int int1 = Integer.parseInt(text1);
                    int int2 = Integer.parseInt(text2);
                    fieldRes.setText(int1 + int2 + "");
                }
                else if(e.getActionCommand().equals("-")){
                    int int1 = Integer.parseInt(text1);
                    int int2 = Integer.parseInt(text2);
                    fieldRes.setText(int1 - int2 + "");
                }
            }
        };
        buttonAdd.addActionListener(buttonListener);
        buttonSub.addActionListener(buttonListener);
        this.setVisible(true);
    }

    public static void main(String[] args) {
        // insert code
        new CalculatorFrame().startGUI();
    }
}
