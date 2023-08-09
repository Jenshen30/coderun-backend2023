import java.io.*;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Main {

    public static int mod(int a, int b) {
        return (a + b) % b;
    }
    public static String find(String str, Set<String> mp) {
        for (int i = 0; i < 27; i++) {
            StringBuilder s = new StringBuilder();
            for (var ch : str.toCharArray()) {
                s.append((char) (mod((int) ch + i - (int) 'a', 26) + (int)'a'));
            }
            if (mp.contains(s.toString())) {
                return s.toString();
            }
        }
        return "";
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

        String buffer = reader.readLine();
        Set<String> mp = new HashSet<>();
        StringBuilder currword = new StringBuilder();
        int c = 0;
        for (int i = 0; i < buffer.length(); i++) {
            if (buffer.charAt(i) == ' ' || buffer.charAt(i) == '\n') {
                mp.add(currword.toString());
                currword = new StringBuilder();
            } else {
                currword.append(buffer.charAt(i));
            }
        }
        mp.add(currword.toString());

        int n = Integer.parseInt(reader.readLine());
        for (int i = 0; i < n; i++) {
            String str = reader.readLine();
            writer.write(find(str.substring(0, str.length()), mp) + "\n");
        }

        reader.close();
        writer.close();

    }
}
/*
a
3
b
v
c
 */
