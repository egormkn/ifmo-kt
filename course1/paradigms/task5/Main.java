import expression.*;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите х: ");
        double x = sc.nextDouble();
        double result = new Add( // x^2-2x+1
                new Subtract( // x^2-2x
                        new Multiply( // x^2
                                new Variable("x"),
                                new Variable("x")
                        ),
                        new Multiply( // 2x
                                new Const(2),
                                new Variable("x")
                        )
                ),
                new Const(1)
        ).evaluate(x);

        System.out.println("Результат: " + result);
    }
}
