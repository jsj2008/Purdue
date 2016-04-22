import java.util.Random;
import java.util.Scanner;

public class Minesweeper {
    
    private boolean[][] minefield; 
    private int[][] clueGrid; 
    private boolean[][] checked; 
    private int rows;
    private int columns;
    
    public Minesweeper(int rows, int columns, int mines) {
        minefield = new boolean[rows][columns]; 
        clueGrid = new int[rows][columns];
        checked = new boolean[rows][columns];
        this.rows = rows;
        this.columns = columns;
        
        generateMinefield(mines);   
        generateClueGrid(); 
        
        for (int i = 0; i < checked.length; i++) 
            for (int j = 0; j < checked[i].length; j++)
            checked[i][j] = false; 
    }
    
    private void generateMinefield(int mines) {
        
        for (int i = 0; i < minefield.length; i++)
            for (int j = 0; j < minefield[i].length; j++)
            minefield[i][j] = false;
        
        Random random = new Random(System.currentTimeMillis());
        
        while (mines > 0) { 
            
            int r = random.nextInt(minefield.length);
            int c = random.nextInt(minefield[r].length);
            
            
            if (!minefield[r][c]) {
               
                minefield[r][c] = true;
                
                mines--;
            }
        }
    }
    
    
    private void generateClueGrid() {
        // for each cell, count the mines around it
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
            clueGrid[i][j] = minefield[i][j] ? -1 : countMines(i,j);
    }
    private int countMines(int row, int column) {
        int n = 0;
        for (int i = Math.max(row-1,0); i <= Math.min(row+1,rows-1); i++)
            for (int j = Math.max(column-1,0); j <= Math.min(column+1,columns-1); j++)
            if (!(i == row && j == column))
            n += minefield[i][j] ? 1 : 0;
        return n;
    }
    
    private void printBoard() {
        
        System.out.print("   "); 
        for (int j = 0; j < columns; j++) 
            System.out.print(" " + (j+1)); 
        System.out.println(); 
        // print dividing line
        System.out.print("  +-"); 
        for (int j = 0; j < columns; j++) 
            System.out.print("--"); 
        System.out.println(); 
        // print row letters and board cells
        char row_letter = 'A';
        for (int i = 0; i < rows; i++) {
            // print a row of cells
            System.out.print(row_letter + " |"); 
            for (int j = 0; j < columns; j++) { 
                char cell_symbol;
                if (!checked[i][j]) 
                    cell_symbol = '?';
                else if (minefield[i][j])
                    cell_symbol = '*';
                else if (clueGrid[i][j] > 0) 
                    cell_symbol = (char)('0' + clueGrid[i][j]);
                else  
                    cell_symbol = ' ';
                System.out.print(" " + cell_symbol);  
            }
            System.out.println(); 
            row_letter++;
        }
    }
    
    public void start() {
        Scanner scanner = new Scanner(System.in);
        boolean win = false; 
        while (!win) {
         
            printBoard();
            
            System.out.print("Check cell? ");
        
            String line = scanner.nextLine().toUpperCase();
            int row = line.charAt(0)-'A';
            int column = line.charAt(1)-'1';

            if (minefield[row][column]) 
                break;// break out of the loop
            else 
                checked[row][column] = true; // if the player identifies the mine as a mine 
            win = true;
            for (int i = 0 ; i < rows && win; i++)
                for (int j = 0; j < columns && win; j++)
                if (!checked[i][j] && !minefield[i][j])
                win = false; // unchecked cell is not a mine
        }
        // game is over
        scanner.close(); 
        for (int i = 0 ; i < rows; i++)
            for (int j = 0; j < columns; j++)
            checked[i][j] = true;
        printBoard();
        if (win) 
            System.out.println("\nYou win!");
        else 
            System.out.println("\nYou're not very good at this are you?");
    }
    
    public static void main(String[] args) {
        
        Minesweeper m = new Minesweeper(5,5,1);
        m.start();
    }
    
}