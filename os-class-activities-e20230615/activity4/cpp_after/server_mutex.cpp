
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

mutex scoreMutex;

void handleClient(int clientSocket) {
    char buffer[1024] = {0};

    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead > 0) {
        string studentName(buffer, bytesRead);

        // Protect the complete read-modify-write operation
        lock_guard<mutex> lock(scoreMutex);

        int score = 0;

        ifstream inputFile("shared_score.txt");
        if (inputFile.is_open()) {
            inputFile >> score;
            inputFile.close();
        }

        // Simulate processing time
        this_thread::sleep_for(chrono::milliseconds(100));

        score++;

        ofstream outputFile("shared_score.txt");
        outputFile << score;
        outputFile.close();

        cout << studentName << " updated score to "
             << score << endl;
    }

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(9002);

    if (bind(serverSocket, (sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0) {
        cerr << "Bind failed\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 20) < 0) {
        cerr << "Listen failed\n";
        close(serverSocket);
        return 1;
    }

    cout << "C++ mutex server running on port 9002\n";

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket >= 0) {
            thread(handleClient, clientSocket).detach();
        }
    }

    close(serverSocket);
    return 0;
}
