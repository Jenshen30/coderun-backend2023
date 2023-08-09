import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
    public static final int MAX_ENERGY = 4;

    public static void main(String[] args) {
        try (Scanner scn = new Scanner(System.in)) {
            make(scn);
        }
    }

    public static void make(Scanner in) {
        int n = in.nextInt();

        Recipe[] recipes = new Recipe[n + 1];

        for (int i = 0; i < n; i++) {
            recipes[i] = new Recipe();
            recipes[i].name = in.next();
            recipes[i].instrLen = in.nextLong();

            int ingredientsSize = in.nextInt();
            recipes[i].ingredients = new Component[ingredientsSize];

            for (int j = 0; j < recipes[i].ingredients.length; j++) {
                recipes[i].ingredients[j] = new Component();
                recipes[i].ingredients[j].name = in.next();
                recipes[i].ingredients[j].c = readMetric(in);
            }
        }

        int k = in.nextInt();
        Map<String, ComponentCost> componentCost = new HashMap<>();

        for (int i = 0; i < k; i++) {
            var name = in.next();

            ComponentCost curBuyInfo = new ComponentCost();
            curBuyInfo.cost = in.nextLong();
            curBuyInfo.c = readMetric(in);

            componentCost.put(name, curBuyInfo);
        }

        Map<String, ComponentEnergy> componentEnergy = new HashMap<>();
        int m = in.nextInt();

        for (int i = 0; i < m; i++) {
            String name = in.next();

            ComponentEnergy cur = new ComponentEnergy();
            cur.c = readMetric(in);

            for (int j = 0; j < MAX_ENERGY; j++) {
                cur.energies[j] = in.nextDouble();
            }
            componentEnergy.put(name, cur);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < recipes[i].ingredients.length; j++) {
                ComponentCost cur1 = componentCost.get(recipes[i].ingredients[j].name);
                ComponentEnergy cur2 = componentEnergy.get(recipes[i].ingredients[j].name);

                cur1.buyLen += recipes[i].instrLen * recipes[i].ingredients[j].c;

                for (int p = 0; p < MAX_ENERGY; p++) {
                    recipes[i].energies[p] +=
                            ((double) recipes[i].ingredients[j].c / (double) cur2.c) *
                                    cur2.energies[p];
                }
            }
        }

        long totalCost = 0L;
        for (var el : componentCost.entrySet()) {
            totalCost += (el.getValue().buyLen + el.getValue().c - 1) / el.getValue().c *
                    el.getValue().cost;
        }

        System.out.println(totalCost);

        for (var el : componentCost.entrySet()) {
            System.out.println(el.getKey() +
                    " " +
                    (el.getValue().buyLen + el.getValue().c - 1) / el.getValue().c);
        }

        for (int i = 0; i < n; i++) {
            System.out.print(recipes[i].name + " ");

            for (int j = 1; j <= MAX_ENERGY; j++) {
                System.out.print(String.format("%.20f", recipes[i].energies[j - 1]) +
                        (j == MAX_ENERGY ? System.lineSeparator() : " "));
            }
        }
    }

    private static class Recipe {
        String name;
        long instrLen;
        double[] energies = new double[MAX_ENERGY];
        Component[] ingredients;
    }


    private static class ComponentCost {
        long c;
        long buyLen;
        long cost;

    }

    private static class Component {
        long c;
        String name;

    }

    private static class ComponentEnergy {
        double[] energies = new double[MAX_ENERGY];
        long c;
    }

    private static long readMetric(Scanner in) {
        int cnt = in.nextInt();
        String type = in.next();

        switch (type) {
            case "tens" -> {
                return cnt * 10L;
            }
            case "l", "kg" -> {
                return cnt * 1000L;
            }
            default -> {
                return (long) cnt;
            }
        }
    }
}