
import java.io.*;
import java.net.*;
import java.nio.file.*;

public class ScoreServerSync {

    private static final int PORT = 9012;
    private static final String SCORE_FILE = "shared_score.txt";

    public static void main(String[] args) {
        try (ServerSocket server = new ServerSocket(PORT)) {

            System.out.println(
                "Java synchronized server running on port " + PORT
            );

            while (true) {
                Socket client = server.accept();

                Thread thread = new Thread(() -> handleClient(client));
                thread.start();
            }

        } catch (IOException e) {
            System.err.println("Server error: " + e.getMessage());
        }
    }

    private static void handleClient(Socket client) {
        try (
            Socket socket = client;
            BufferedReader input = new BufferedReader(
                new InputStreamReader(socket.getInputStream())
            )
        ) {
            String studentName = input.readLine();

            if (studentName != null) {
                int score = updateScore(studentName);

                System.out.println(
                    studentName + " updated score to " + score
                );
            }

        } catch (Exception e) {
            System.err.println("Client error: " + e.getMessage());
        }
    }

    // Synchronization protects the entire read-modify-write operation
    private static synchronized int updateScore(String studentName)
            throws IOException, InterruptedException {

        int score = Integer.parseInt(
            Files.readString(Path.of(SCORE_FILE)).trim()
        );

        Thread.sleep(100);

        score++;

        Files.writeString(
            Path.of(SCORE_FILE),
            String.valueOf(score)
        );

        return score;
    }
}
