
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./client SERVER_IP STUDENT_NAME\n";
        return 1;
    }

    const char* serverIP = argv[1];
    const char* studentName = argv[2];

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);

    if (inet_pton(AF_INET, serverIP,
                  &serverAddress.sin_addr) <= 0) {
        cerr << "Invalid server IP\n";
        close(clientSocket);
        return 1;
    }

    cout << "Connecting to server " << serverIP << "...\n";

    if (connect(clientSocket, (sockaddr*)&serverAddress,
                sizeof(serverAddress)) < 0) {
        cerr << "Connection failed!\n";
        close(clientSocket);
        return 1;
    }

    send(clientSocket, studentName, strlen(studentName), 0);

    cout << "Request sent by " << studentName << "\n";

    close(clientSocket);
    return 0;
}
