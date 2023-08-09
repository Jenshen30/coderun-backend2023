import java.io.*;
import java.nio.Buffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Main {
    private static List<Pair> dp;

    static int getPos(long ind, long shift) {
        int q = Collections.binarySearch(dp, new Pair(ind, -1, -1), Comparator.comparing(Pair::getIndexS));
        if (q < 0) {
            q = -q - 1;
            // if q in insertion point
            if (q == dp.size() || dp.get(q).indexS > ind) {// fixme
                q--;
            }
        }
        q += shift;
        if (q >= dp.size() || q < 0) {
            return -1;
        }
        return q;
    }

    private static long getTmp(long ind, int q, boolean isLeft) {
        long ans, counts;
        if (isLeft) {
            counts = dp.get(q).currT - (ind - dp.get(q).indexS); // fixme -1 !!!
        } else {
            counts = (ind - dp.get(q).indexS + 1); // +1
        }

        ans = String.valueOf(counts).length();
        ans += (counts > 1 ? 1 : 0);
        return ans;
    }
    private static void tester() {
        try (BufferedWriter writer = Files.newBufferedWriter(Path.of("test.out"));
             BufferedReader reader = Files.newBufferedReader(Path.of("test.in"))) {
            String s = reader.readLine();
            createDp(s);
            int n = Integer.parseInt(reader.readLine());

            for (int i = 0; i < n; i++) {
                var inp = reader.readLine().split(" ");
                long l = Long.parseLong(inp[0]),
                        r = Long.parseLong(inp[1]);
                writer.write((range(l, r) + added(l, r)) + "\n");
            }
        } catch (IOException e) {
            System.out.println("Problem with io!");
        }
    }
    public static void main(String[] args) throws IOException {
        if (args == null) {
            tester();
        } else {
            stdIO();
        }
    }

    private static void stdIO() throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String s = reader.readLine();
            createDp(s);
            int n = Integer.parseInt(reader.readLine());

            for (int i = 0; i < n; i++) {
                var inp = reader.readLine().split(" ");
                long l = Long.parseLong(inp[0]),
                        r = Long.parseLong(inp[1]);
                System.out.println(
                        range(l, r) +
                                added(l, r));
            }
        }
    }

    private static long added(long l, long r) {
        int lRes = getPos(l, 0);
        int rRes = getPos(r, 0);

        if (lRes == rRes) {
            var val = r - l + 1;
            return String.valueOf(val).length() + (val > 1 ? 1 : 0);
        }

        return getTmp(l, lRes, true) + getTmp(r, rRes, false);
    }
    private static long range(long l, long r) {
        int lRes = getPos(l, 1);
        int rRes = getPos(r, -1);

        if (rRes != -1 && lRes != -1) {
            var currTLen = String.valueOf(dp.get(rRes).currT).length() +
                    (dp.get(rRes).currT > 1 ? 1 : 0);
            if (lRes < rRes) {
                return dp.get(rRes).indexT - dp.get(lRes).indexT +
                        currTLen; // fixme!!
            }
            if (lRes == rRes) {
                return currTLen;
            }
        }
        return 0;
    }
    private static void createDp(String s) {
        int i = 0, counter = 1;
        dp = new ArrayList<>();

        while (i < s.length()) {
            if (Character.isAlphabetic(s.charAt(i))) {
                if (dp.isEmpty()) {
                    dp.add(new Pair(1, 0, counter));
                } else {
                    dp.add(new Pair(dp.get(dp.size() - 1), counter));
                }
                counter = 1;
                i++;
            } else {
                StringBuilder tmp = new StringBuilder();
                while (!Character.isAlphabetic(s.charAt(i))) {
                    tmp.append(s.charAt(i));
                    i++;
                }
                counter = Integer.parseInt(tmp.toString());
            }
        }
    }

    private static class Pair {
        long indexS, indexT, currT;

        public Pair(long indexS, long indexT, long t) {
            this.indexS = indexS;
            this.indexT = indexT;
            this.currT = t;
        }
        public Pair(Pair prev, long counter) {
            this.indexS = prev.indexS + prev.currT;
            this.indexT = prev.indexT + String.valueOf(prev.currT).length() + ((prev.currT > 1) ? 1 : 0);
            this.currT = counter;
        }

        public long getIndexS() {
            return indexS;
        }
    }
}
/*
Tests:

10a10b
1
1 20

10a10b10cd
1
1 31
8

abababa
6
2 5
5 7
7 8
1 8
2 8
2 7


100ab100abc2a
1
200 205



sdf
1
2 2


1000000000a1000000000b1000000000a1000000000b
1
2000000000 4000000000

1000000000a
1
1 9

abcd
2
1 4
2 3

ik2ze
1
1 5
 */
