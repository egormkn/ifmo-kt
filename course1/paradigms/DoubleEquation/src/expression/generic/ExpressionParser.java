package expression.generic;

import expression.exceptions.*;

public class ExpressionParser<T extends Numeric> implements Parser<T> {

    private String expr;
    private int pos;
    private int length;
    private T p;

    @Override
    public TripleExpression<T> parse(String s) throws ParserException {
        expr = s;
        length = s.length();
        pos = 0;
        TripleExpression<T> result = parseAddSub();
        if (pos < length) {
            parseError();
        }
        return result;
    }

    private void trim() {
        for (; pos < length && Character.isWhitespace(expr.charAt(pos)); pos++);
    }

    private TripleExpression parseAddSub() throws ParserException {
        TripleExpression leftExpr = parseMulDiv();
        while (pos < length) {
            char sign = expr.charAt(pos);
            if (sign != '+' && sign != '-') {
                break;
            }
            pos++;
            trim();
            TripleExpression rightExpr = parseMulDiv();
            if (sign == '+') {
                leftExpr = new CheckedAdd(leftExpr, rightExpr);
            } else {
                leftExpr = new CheckedSubtract(leftExpr, rightExpr);
            }
        }
        return leftExpr;
    }

    private TripleExpression parseMulDiv() throws ParserException {
        TripleExpression leftExpr = parsePowLog();
        while (pos < length) {
            char sign = expr.charAt(pos);
            if ((sign != '*' && sign != '/')) {
                return leftExpr;
            }
            pos++;
            trim();
            TripleExpression rightExpr = parsePowLog();
            if (sign == '*') {
                leftExpr = new CheckedMultiply(leftExpr, rightExpr);
            } else {
                leftExpr = new CheckedDivide(leftExpr, rightExpr);
            }
        }
        return leftExpr;
    }

    private TripleExpression parsePowLog() throws ParserException {
        TripleExpression leftExpr = parseParenthesis();
        while (pos < length - 1) {
            char sign = expr.charAt(pos);
            if ((sign != '*' && sign != '/') || sign != expr.charAt(pos + 1)) {
                return leftExpr;
            }
            pos += 2;
            trim();
            TripleExpression rightExpr = parseParenthesis();
            if (sign == '*') {
                leftExpr = new CheckedPower(leftExpr, rightExpr);
            } else {
                leftExpr = new CheckedLog(leftExpr, rightExpr);
            }
        }
        return leftExpr;
    }

    private TripleExpression parseParenthesis() throws ParserException {
        trim();
        if (pos != length && expr.charAt(pos) == '(') {
            pos++;
            trim();
            TripleExpression r = parseAddSub();
            if (pos != length && expr.charAt(pos) == ')') {
                pos++;
                trim();
            } else {
                throw new ParserException("parenthesis not closed in '" + expr + "' on position " + pos);
            }
            return r;
        }
        return parseFunctionVariable();
    }

    private TripleExpression parseFunctionVariable() throws ParserException {
        if (pos < length - 1 && expr.charAt(pos) == '-' && !Character.isDigit(expr.charAt(pos + 1))) {
            pos++;
            trim();
            return new CheckedNegate(parseParenthesis());
        }

        String temp = "";
        while (pos < length && Character.isLetter(expr.charAt(pos))) {
            temp += expr.charAt(pos++);
        }
        trim();
        if (!temp.isEmpty()) {
            if (temp.length() > 1) {
                TripleExpression r = parseParenthesis();
                switch (temp) {
                    case "abs":
                        return new CheckedAbs(r);
                    case "sqrt":
                        return new CheckedSqrt(r);
                    default:
                        throw new ParserException("unknown operator '" + temp + "' on position " + pos);
                }
            } else {
                if (!temp.equals("x") && !temp.equals("y") && !temp.equals("z")) {
                    throw new ParserException("unknown variable '" + temp + "' on position " + pos);
                }
                return new CheckedVariable(temp);
            }
        }
        trim();
        return parseNumber();
    }

    private TripleExpression parseNumber() throws ParserException {
        String temp = "";
        while (pos < length && (Character.isDigit(expr.charAt(pos)) || (temp.isEmpty() && expr.charAt(pos) == '-'))) {
            temp += expr.charAt(pos++);
        }
        if (temp.isEmpty()) {
            parseError();
        }
        trim();
        return new CheckedConst(p.parse(temp));
    }

    void parseError() throws ParserException {
        if(pos == length){
            throw new ParserException("no last argument ('" + expr.substring(pos) + "' found) in '" + expr + "' on position " + pos);
        }
        char c = expr.charAt(pos);
        if(!Character.isDigit(c) && !Character.isLetter(c) && "()+-*/".indexOf(c) == -1){
            throw new ParserException("unexpected symbol '" + c + "' in '" + expr + "' on position " + pos);
        } else if(c == ')') {
            throw new ParserException("parenthesis not opened ('" + expr.substring(pos) + "' found) in '" + expr + "' on position " + pos);
        } else if("+-*/".indexOf(c) != -1) {
            throw new ParserException("argument missed ('" + expr.substring(pos) + "' found) in '" + expr + "' on position " + pos);
        } else {
            throw new ParserException("unexpected expression ('" + expr.substring(pos) + "' found) '" + expr + "' on position " + pos);
        }
    }
}