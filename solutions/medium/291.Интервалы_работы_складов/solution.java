import java.io.*;
import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

public class Main {
    private static List<Note> notes = new ArrayList<>();

    public static void main(String[] args) throws IOException {
        try(BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out))) {
            String line;

            while ((line = reader.readLine()) != null) {
                //            while ((line = reader.readLine()) != null) {
                var splitted = Arrays.stream(line.split(","))
                        .map(String::trim)
                        .map(i -> i.split(" "))
                        .flatMap(Arrays::stream)
                        .toArray(String[]::new);

                if (splitted[3].equals("NULL")) {
                    for (var el : Type.values()) {
                        notes.add(new Note(splitted[0],
                                splitted[1],
                                splitted[2],
                                el.toString()));
                    }
                } else {
                    notes.add(new Note(splitted[0],
                            splitted[1],
                            splitted[2],
                            splitted[3]));
                }
            }
            notes = sort(notes);
            List<Note> afterFiltering = new ArrayList<>(List.of(notes.get(0)));

            for (int i = 1; i < notes.size(); i++) {
                var t = afterFiltering.remove(afterFiltering.size() - 1);

                if (isNoteInNote(notes.get(i), t) &&
                        t.type.equals(notes.get(i).type) &&
                        t.id == notes.get(i).id) {

                    afterFiltering.add(
                            new Note(t.id, minDate(t.start, notes.get(i).start),
                                    maxDate(t.end, notes.get(i).end), t.type));
                } else {
                    afterFiltering.add(t);
                    afterFiltering.add(notes.get(i));
                }
            }
            afterFiltering = sort(afterFiltering);
            for (var el : afterFiltering) {
                writer.write(el.toString() + "\n");
            }
        }
    }

    private static LocalDate minDate(LocalDate d1, LocalDate d2) {
        return (d1.isAfter(d2)) ? d2 : d1;
    }

    private static LocalDate maxDate(LocalDate d1, LocalDate d2) {
        return (d1.isAfter(d2)) ? d1 : d2;
    }

    private static List<Note> sort(List<Note> in) {
        return in.stream()
                .sorted(Comparator.comparingInt(Note::getId)
                        .thenComparing(Note::getType)
                        .thenComparing(Note::getStart))
                .collect(Collectors.toList());
    }

    private static boolean isNoteInNote(Note n1, Note n2) {
        return  n1.start.isBefore(n2.end) || n1.start.isEqual(n2.start) || n1.start.isEqual(n2.end);
    }

    private static class Note {
        int id;
        LocalDate start, end;
        Type type;

        public Note(int id, LocalDate start, LocalDate end, Type type) {
            this.id = id;
            this.start = start;
            this.end = end;
            this.type = type;
        }

        private LocalDate parseDate(String YMD) {
            var tmp = Arrays.stream(YMD.split("-"))
                    .map(Integer::parseInt).toList();
            return LocalDate.of(tmp.get(0), tmp.get(1), tmp.get(2));
        }

        public Note(String id, String start, String end, String type) {
            this.id = Integer.parseInt(id);
            this.start = parseDate(start);
            this.end = parseDate(end);
            this.type = Type.valueOf(type);
        }

        public int getId() {
            return id;
        }

        public LocalDate getStart() {
            return start;
        }

        public Type getType() {
            return type;
        }

        @Override
        public String toString() {
            return id +
                    "," + start +
                    " " + end +
                    "," + type;
        }
        public  LocalDate getEnd() {
            return end;
        }
    }

    public enum Type {
        KGT, COLD, OTHER
    }
}

/*

4,2020-02-23 2020-11-01,COLD
4,2020-03-15 2020-07-12,COLD
4,2020-03-15 2020-07-12,COLD
4,2020-03-15 2020-07-12,NULL
4,2020-02-23 2020-03-15,COLD
4,2020-03-15 2020-07-12,COLD

  16  11
15      12
4,2020-03-16 2020-07-11,COLD
4,2020-03-15 2020-07-12,NULL


0,2020-02-23 2020-03-15,COLD
4,2020-03-13 2020-07-13,COLD
4,2020-07-11 2020-07-13,COLD

4,2020-02-23 2020-03-15,COLD
4,2020-03-15 2020-03-15,COLD

4,2020-03-15 2020-07-12,KGT
4,2020-03-15 2020-07-12,KGT

*/
