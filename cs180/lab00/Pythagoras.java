/**
* CS180 - Lab00
* Explain briefly the functionality of the program.
*@author Kush Rustagi, krustagi@purdue.edu
*/
import java.util.Scanner;
public class Pythagoras 
{
	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in); //create a console scanner object
        System.out.print("Enter side 'a': "); // prompt the user for input
        int a = scanner.nextInt(); // read 'a' from the console
		System.out.print("Enter side 'b': "); // prompt the user for input
        int b = scanner.nextInt(); // read 'b' from the console
		Pythagoras p = new Pythagoras();
		double h = p.getHypotenuse(a, b);
		System.out.println("Hypotenuse: " + h);
	}

	public static double getHypotenuse(int a, int b)
	{
		double result;
        result = Math.sqrt(a * a + b * b);
        return result;
	}
}
