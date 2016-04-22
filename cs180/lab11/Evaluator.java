import java.util.Scanner;
import java.util.Stack;
public class Evaluator {
    public static int evaluate(String s) {
        Stack<Integer> st= new Stack<Integer>();
        int a1;
        int b1;
        int ans;
        int answer;
        Scanner sc = new Scanner(s);         
        while (sc.hasNext()) {  
            String a = sc.next();
            if (a.equals("+") ) {
                a1 = st.pop();
                b1 = st.pop();
                ans = b1 + a1;
                st.push(ans);
            }
            else if (a.equals("-")) {
                a1 = st.pop();
                b1 = st.pop();
                ans = b1 - a1;
                st.push(ans);
            }
            else if (a.equals("x")) {
                a1 = st.pop();
                b1 = st.pop();
                ans = b1 * a1;
                st.push(ans);
            }
            else if (a.equals("/")) {
                a1 = st.pop();
                b1 = st.pop();
                ans = b1 / a1;
                st.push(ans);
            }
            else if (a.equals(" ")) 
                continue; 
            else {
                int b = Integer.parseInt(a);
                if (b >= 0 && b <= 9 ) {                
                    st.push(b);
                }
            }
            
        }
        answer = st.pop();
        System.out.println(answer);
        return answer;
    }
    public static void main(String[] args) {
        Evaluator obj = new Evaluator(); 
        obj.evaluate("5 1 2 + 4 x + 3 -");
    }
}
