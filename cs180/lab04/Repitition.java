import java.util.Scanner;
/**
 * CS 180 - Lab 04 - Repetition
 * 
 * (Brief description of the class file)
 * 
 * @author Kush Rustagi <(krustagi@purdue.edu)>
 * 
 * @lab 806
 *
 * @date 9/24/2014
 */

public class Repitition {
    
    public static void main(String[] args) {
        Repitition r = new Repitition();
        // call the even() method
        r.even();
        System.out.println();
        // call the powers() method
        r.powers();
        System.out.println();
        // call the alphabet() method
        r.alphabet();
        System.out.println();   
        //change as you need
        r.vertical("hello");
        System.out.println();
        r.testResults();
        System.out.println();
    }

    public static void even() {
        for( int i = 0; i<100; i+=2)
            System.out.print(i+" ");
    }   
 
    public static void powers() {
        int exp=0;
        while(Math.pow(2,exp)<1000)
        {
            System.out.print(Math.pow(2,exp)+" ");
            exp++;
        }
    }

    public static void alphabet() {
        for(int i=97;i<=122;i++)
            System.out.print((char)i);
    }

    public static void vertical ( String s) {
        for(int i=0;i<s.length();i++)
            System.out.println(s.charAt(i));
    }

    public static void testResults() {
        int ls=0,hs=0,avg,s=0,i=0;
        int a;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter scores now:");
        while(sc.hasNextInt())
        {
            a=sc.nextInt();
            if(i==0)
                ls=a;
            s+=a;
            if(a<ls)
                ls=a;
            if(a>hs)
                hs=a;
            i++;
        }
        avg=s/i;
        System.out.printf("=====-----=====-----=====-----=====\n");
        System.out.printf("=          Test Results           =\n");
        System.out.printf("= Average: %22d =\n",avg);
        System.out.printf("= Lowest:  %22d =\n",ls);
        System.out.printf("= Highest: %22d =\n",hs);
        System.out.printf("=====-----=====-----=====-----=====\n");
    }
    
}

