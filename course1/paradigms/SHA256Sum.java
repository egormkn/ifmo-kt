import javax.xml.bind.DatatypeConverter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.DigestInputStream;
import java.security.MessageDigest;

public class SHA256Sum {

    public static void main(String[] args) throws Exception {
        if(args.length == 0){
            byte[] buffer = new byte[1024];
            DigestInputStream dis = new DigestInputStream(System.in, MessageDigest.getInstance("SHA-256"));
            while (dis.read(buffer) > -1) {}
            System.out.println(DatatypeConverter.printHexBinary(dis.getMessageDigest().digest()).toUpperCase() + " *-");
            dis.close();
            return;
        }

        for (String p : args) {
            System.out.println(DatatypeConverter.printHexBinary(MessageDigest.getInstance("SHA-256").digest(Files.readAllBytes(Paths.get(p)))).toUpperCase() + " *" + Paths.get(p).getFileName().toString());
        }
    }
}
