import javax.xml.bind.DatatypeConverter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;

//import java.nio.file.Path;
//import java.security.DigestInputStream;

public class CalcSHA256 {

    public static void main(String[] args) throws Exception {
//        byte[] buffer = new byte[1024];
        for (String p : Files.readAllLines(Paths.get(args[0]))) {
//            for (Path f : Files.walk(Paths.get(p)).filter(s -> s.toFile().isFile()).toArray(Path[]::new)) {
//                DigestInputStream dis = new DigestInputStream(Files.newInputStream(f), MessageDigest.getInstance("SHA-256"));
//                while (dis.read(buffer) > -1) {}
            System.out.println(DatatypeConverter.printHexBinary(
//                        dis.getMessageDigest().digest()
                    MessageDigest.getInstance("SHA-256").digest(Files.readAllBytes(Paths.get(p)))
            ).toUpperCase());

//                dis.close();
//            }
        }
    }
}
