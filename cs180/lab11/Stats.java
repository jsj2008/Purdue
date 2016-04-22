import java.util.Set;
import java.util.HashMap;
import java.util.Map;
import java.io.*;

public class Stats {  
    public static Map<String,Integer> wins() throws FileNotFoundException,IOException {
        BufferedReader br = new BufferedReader(new FileReader("/Users/krustagi/Desktop/lab11.txt"));
        Map<String,Integer> map = new HashMap<String,Integer>();
        
        String names = br.readLine();
        while(names != null) {
            
            String[] word = names.split(" ");
            if (word[0].equals("1")) {
                int i = 1;
                while (!word[i].equals( "vs.")) {
                    Integer count = map.get(word[i]);
                    // map.contains(word[i])
                    if (count == null) {
                        map.put(word[i], 1);
                    }
                    else {
                        count++;
                        map.put(word[i],count);
                    }
                    
                    i++;
                }
            }
            else {
                int i = word.length - 1;
                while (!word[i].equals( "vs."))  {
                    Integer count = map.get(word[i]);
                    if (count == null) {
                        map.put(word[i], 1);
                    }
                    else {
                        count++;
                        map.put(word[i],count);
                    }
                    i --;
                }
            }
            
            names = br.readLine();
        }
        System.out.println(map);
        return map;
    }
    public static String winner()throws FileNotFoundException,IOException {
        Map<String,Integer> map = wins();
        int max = 0;
        String str = "";
        for ( Map.Entry<String, Integer> entry : map.entrySet()) {
            String key = entry.getKey();
            int value = entry.getValue();
            if (value > max) {
                max = value;
                str = key;
            }
        }
        System.out.println(str);
        return str;
    }
    public static void main(String[]  args) throws FileNotFoundException,IOException{
        Stats obj = new Stats();
        obj.wins();
        obj.winner();
    }
}

