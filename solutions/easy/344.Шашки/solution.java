import java.util.*;

public class Main {
    static char[][] board;
    static int n, m;

    private static ArrayList<Pair> readBoardForOneStage(Scanner scn, int iter, char color) {
        ArrayList<Pair> pairs = new ArrayList<>();
        for (int i = 0; i < iter; i++) {
            var tmp = new Pair(scn.nextInt(), scn.nextInt());
            pairs.add(tmp);
            board[tmp.x][tmp.y] = color;
        }
        return pairs;
    }

    private static boolean isOccupyOne(Pair p, char color) {
        for (var delta_x : Set.of(-1, 1)) {
            for (var delta_y : Set.of(-1, 1)) {
                if (p.x + delta_x >= 1 && p.x + delta_x <= n &&
                        p.y + delta_y >= 1 && p.y + delta_y <= m &&
                        board[p.x + delta_x][p.y + delta_y] == color) {

                    if (p.x + 2 * delta_x >= 1 && p.x + 2 * delta_x <= n &&
                            p.y + 2 * delta_y >= 1 && p.y + 2 * delta_y <= m &&
                            board[p.x + 2 * delta_x][p.y + 2 * delta_y] == 0) {
                        return true;
                    }

                }
            }
        }
        return false;
    }

    private static String check(ArrayList<Pair> queue, char opposite) {
        for (Pair el : queue) {
            if (isOccupyOne(el, opposite)) {
                return "Yes";
            }
        }
        return "No";
    }

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        n = scn.nextInt();
        m = scn.nextInt();
        board = new char[n + 1][m + 1];

        int countWhite = scn.nextInt();
        var whites = readBoardForOneStage(scn, countWhite, 'w');

        int countBlack = scn.nextInt();
        var blacks = readBoardForOneStage(scn, countBlack, 'b');

        scn.nextLine();

        if (scn.nextLine().equals("white")) {
            System.out.println(check(whites,  'b'));
        } else {
            System.out.println(check(blacks, 'w'));
        }
        scn.close();
    }
    private static class Pair {
        int x,y;

        public Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}
