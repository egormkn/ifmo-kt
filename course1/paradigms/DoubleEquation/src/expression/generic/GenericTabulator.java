package expression.generic;

public class GenericTabulator implements Tabulator {

    @Override
    public Object[][][] tabulate(String mode, String expression, int x1, int x2, int y1, int y2, int z1, int z2) throws Exception {
        ExpressionParser p;
        switch (mode) {
            case "i": // вычисления в int с проверкой на переполнение
                p = new ExpressionParser<NumericCheckedInteger>();
                break;
            case "d": // вычисления в double без проверки на переполнение
                p = new ExpressionParser<NumericDouble>();
                break;
            case "bi": // вычисления в BigInteger
                p = new ExpressionParser<NumericBigInteger>();
                break;
            case "u": // вычисления в int без проверки на переполнение
                p = new ExpressionParser<NumericInteger>();
                break;
            case "b": // вычисления в byte без проверки на переполнение
                p = new ExpressionParser<NumericByte>();
                break;
            case "f": // вычисления в float без проверки на переполнение
                p = new ExpressionParser<NumericFloat>();
                break;
            default:
                throw new Exception("Unknown type '" + mode + "'");
        }

        TripleExpression expr = p.parse(expression);

        Object[][][] result = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
        for(int i = 0; i <= x2 - x1; i++){
            for(int j = 0; j <= y2 - y1; j++){
                for(int k = 0; k <= z2 - z1; k++){
                    try {
                        result[i][j][k] = expr.evaluate(x1 + i, y1 + j, z1 + k);
                    } catch (Exception e){
                        result[i][j][k] = null;
                    }
                }
            }
        }
        return result;
    }
}
