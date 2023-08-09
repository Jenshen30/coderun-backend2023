import java.io.*;
import java.util.*;
import java.util.function.BiFunction;
import java.util.function.Consumer;

public class Main {
    private static final List<DataCenter> centers = new ArrayList<>();
    private final static SortedSet<Pair> resMin = new TreeSet<>(), resMax = new TreeSet<>();

    private static final BiFunction<Pair, Pair, Integer> compMax = (t1, t2) -> {
        if (t1.value != t2.value)
            // t1.value > t2.value => 1
            return Long.compare(t1.value, t2.value);
        // t1.index < t2.index => 1
        return Integer.compare(t2.index, t1.index);
    };

    private static final BiFunction<Pair, Pair, Integer> compMin = (t1, t2) -> {
        if (t1.value != t2.value)
            // t1.value < t2.value => 1
            return -Long.compare(t1.value, t2.value);
        // t1 < t2 => 1
        return Integer.compare(t2.index, t1.index);
    };

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

        String nmq = reader.readLine();

        int n = Integer.parseInt(nmq.split(" ")[0]),
                m = Integer.parseInt(nmq.split(" ")[1]),
                q = Integer.parseInt(nmq.split(" ")[2]);


        for (int i = 0; i < n; i++) {
            centers.add(new DataCenter(m));
            resMax.add(new Pair(centers.get(i).getRA(), i, compMax));
            resMin.add(new Pair(centers.get(i).getRA(), i, compMin));
        }

        for (int i = 0; i < q; i++) {
            var request = reader.readLine();
            if (request.startsWith("DISABLE")) {
                changeElement(request, (el) ->
                        el.disableServer(Integer.parseInt(request.split(" ")[2]) - 1));
            } else if (request.startsWith("RESET")) {
                changeElement(request, DataCenter::reset);
            } else if (request.startsWith("GETMAX")) {
                // max for comp
                writer.write((resMax.last().index + 1) + "\n");
            } else if (request.startsWith("GETMIN")) {
                // max for comp eq min
                writer.write((resMin.last().index + 1) + "\n");
            }
        }

        reader.close();
        writer.close();
    }

    private static void changeElement(String request, Consumer<DataCenter> action) {
        int index = Integer.parseInt(request.split(" ")[1]) - 1;
        var el = centers.get(index);
        resMax.remove(new Pair(el.getRA(), index, compMax));
        resMin.remove(new Pair(el.getRA(), index, compMin));

        action.accept(el);

        resMax.add(new Pair(el.getRA(), index, compMax));
        resMin.add(new Pair(el.getRA(), index, compMin));
    }

    private static class DataCenter {
        long max;
        Set<Integer> closed = new HashSet<>();
        long resets = 0;

        public DataCenter(int active) {
            this.max = active;
        }

        public long getRA() {
            return resets * (max - closed.size());
        }

        public void disableServer(int num) {
            closed.add(num);
        }

        public void reset() {
            closed.clear();
            resets++;
        }
    }

    private static class Pair implements Comparable<Pair> {
        long value;
        int index;
        BiFunction<Pair, Pair, Integer> comp;

        public Pair(long value, int index, BiFunction<Pair, Pair, Integer> comp) {
            this.value = value;
            this.index = index;
            this.comp = comp;
        }

        @Override
        public int compareTo(Pair o) {
            return comp.apply(this, o);
        }
    }
}

/*
100 2 6
RESET 100
DISABLE 100 1
RESET 100
DISABLE 100 2
GETMIN
GETMAX

RESET 3
DISABLE 3 1
DISABLE 2 1
DISABLE 3 1
1
1
*/
