
import java.io.*;
import java.net.*;

public class ScoreClient {

    public static void main(String[] args) {

        if (args.length != 3) {
            System.out.println(
                "Usage: java ScoreClient SERVER_IP STUDENT_NAME PORT"
            );
            return;
        }

        String serverIP = args[0];
        String studentName = args[1];
        int port = Integer.parseInt(args[2]);

        try (Socket socket = new Socket(serverIP, port)) {

            PrintWriter output = new PrintWriter(
                socket.getOutputStream(), true
            );

            output.println(studentName);

            System.out.println(
                "Request sent by " + studentName
            );

        } catch (IOException e) {
            System.err.println(
                "Connection failed: " + e.getMessage()
            );
        }
    }
}
