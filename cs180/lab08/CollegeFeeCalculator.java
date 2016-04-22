/**
 * CS 180 - Lab 08 - CollegeFeeCalculator
 * 
 * Calculates College Fees
 * 
 * @author Kush Rustagi <krustagi@purdue.edu>
 * 
 * @lab 806
 *
 * @date 5th Nov, 2014
 */
import javax.swing.JOptionPane;
public class CollegeFeeCalculator {
    public static void main(String[] args) {
        int c = 1;
        try {
            JOptionPane.showMessageDialog (null, "Welcome to CollegeFeeCalculator!",
                                           "CollegeFeeCalculator", JOptionPane.INFORMATION_MESSAGE);
            do {
                int totalfee = 0;
                int tuitionFee = 0;
                int expenses = 0;
                String name = JOptionPane.showInputDialog(null,"Please enter your name, then press OK",
                                                          "Name", JOptionPane.QUESTION_MESSAGE);
                if(name == null||name.equals("")){
                    break;
                }
                String[] a = {"Part-time", "Full-time"};
                int choice;
                String numcredits;
                int credits;
                while(true) {
                    choice = JOptionPane.showOptionDialog(null, "Please select your enrollment", 
                                                              "Enrollment",JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, a, a[0]);
                    numcredits = JOptionPane.showInputDialog(null,"Please enter the no. of credit hours, then press OK",
                                                                    "Credit Hours", JOptionPane.QUESTION_MESSAGE);
                    credits = Integer.parseInt(numcredits);
                    
                    if ((a[choice].equals("Part-time") && credits >= 8)||(a[choice].equals("Full-time") && credits < 8)){
                        
                        JOptionPane.showMessageDialog (null, "Please enter valid credit hours for the current enrollment",
                                                       "Invalid no. of credits", JOptionPane.ERROR_MESSAGE);
                        credits = Integer.parseInt(numcredits);
                        continue;
                    }
                    else break;
                }
                String[] residency = {"In-state", "Out-of-state", "International"};
                
                String resichoice = (String)JOptionPane.showInputDialog(null, "Please select the appropriate residency", "Residency", 
                                                                        JOptionPane.QUESTION_MESSAGE, null, residency, residency[0]);
                if(resichoice == null){
                    break;
                }
                
                String[] state = {"ON-Campus", "OFF-Campus"};
                
                String statechoice = (String)JOptionPane.showInputDialog(null, "Please select your housing", "Housing", 
                                                                         JOptionPane.QUESTION_MESSAGE, null, state, state[0]);
                String rhc = "";
                if(statechoice.equals("ON-Campus")) {
                    
                    String[] resihall = {"Earhart", "Hillenbrand", "Owen", "Windsor"};
                    
                    rhc = (String)JOptionPane.showInputDialog(null, "Please select the residence hall", "Residence-Hall", 
                                                                         JOptionPane.QUESTION_MESSAGE, null, resihall, resihall[0]);
                }
                if(a[choice].equals("Full-time")) {
                    if(resichoice.equals("In-state"))
                        tuitionFee = 4996;
                    if(resichoice.equals("Out-of-state"))
                        tuitionFee = 4996 + 9401;
                    if(resichoice.equals("International"))
                        tuitionFee = 4996 + 9401 + 1000;
                }
                
                else if(a[choice].equals("Part-time")) {
                    if(resichoice.equals("In-state"))
                        tuitionFee = 350 * credits;
                    if(resichoice.equals("Out-of-state"))
                        tuitionFee = (350 + 600) * credits;
                    if(resichoice.equals("International"))
                        tuitionFee = (350 + 600 + 70) * credits;
                }
                if(statechoice.equals("OFF-Campus")) 
                    expenses = 0;
                else {
                    if(rhc.equals("Earhart"))
                        expenses = 4745;
                    if(rhc.equals("Hillenbrand"))
                        expenses = 5307;
                    if(rhc.equals("Owen"))
                        expenses = 4130;
                    if(rhc.equals("Windsor"))
                        expenses = 4150;
                }
                totalfee = tuitionFee + expenses;
                
                JOptionPane.showMessageDialog (null, "Name: " + name + "\nCredit Hours: " + credits +"\nEnrollment: "
                                                   + a[choice] + "\nResidency: " + resichoice + "\nTuition fee: $"
                                                   + tuitionFee + "\nHousing Expense: $" + expenses + "\nTotal Sem. Fee: $"
                                                   + totalfee,
                                               "CollegeFeeCalculator", JOptionPane.INFORMATION_MESSAGE);
                
                
                c = JOptionPane.showConfirmDialog(null, "Would you like to perform another fee calculation?",
                                                  "Are you done?", JOptionPane.YES_NO_OPTION);
            }while(c==0);
        }
        catch(Exception e){
            c = 1;
        }
    }
}