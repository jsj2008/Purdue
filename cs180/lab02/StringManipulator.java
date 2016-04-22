/**
 * CS 180 - Lab 02 - StringManipulator
 * 
 * Manipulates strings using functions
 * 
 * @author Kush Rustagi <krustagi@purdue.edu>
 * 
 * @lab (806)
 *
 * @date 09/10/2014
 */
import java.util.Scanner;
public class StringManipulator {
  
public String makeUserName(String fullName) {
  /**
 * @param fullName contains the person's 
 * first and last name separated by a space
 * @return user name
 */
  fullName = fullName.toLowerCase();
  int a = fullName.indexOf(' ');
  String User = fullName.charAt(0) + fullName.substring(a+1);
  return User;
}

public String makeEmail(String name, String domain) {
    /** 
 * @param name user name returned by the makeUserName method
 * @param domain Internet domain name (e.g. purdue.edu)
 * @return e-mail
 */
  domain= domain.toLowerCase();
  return name+"@"+domain;
  }
public static void main(String[] args) {
  Scanner s=new Scanner(System.in);
  StringManipulator m= new StringManipulator();
  System.out.println("ENter the Full name of the Person. First Name followed by the last name.");                     
  String Name= s.nextLine();
  System.out.println("Enter the Domain");
  String Domain= s.nextLine();
  System.out.println("The user name for the person is: " + m.makeUserName(Name));
  System.out.println("The email id for the person is: " + m.makeEmail(m.makeUserName(Name),Domain));
}
}