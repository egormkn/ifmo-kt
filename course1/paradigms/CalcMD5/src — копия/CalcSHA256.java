import javax.xml.bind.DatatypeConverter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;

public class CalcSHA256 {

    public static void main(String[] args) throws Exception {
        for (String p : Files.readAllLines(Paths.get(args[0]))) {
            System.out.println(DatatypeConverter.printHexBinary(MessageDigest.getInstance("SHA-256").digest(Files.readAllBytes(Paths.get(p)))).toUpperCase())
        }
    }
}