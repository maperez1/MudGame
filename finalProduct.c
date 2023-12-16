#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <mosquitto.h>

#define UDP_PORT 8080
#define UDP_MAX_LEN 1024
#define ADDRESS "dakotarowland.duckdns.org"
#define CLIENTID "ESP32"
#define QOS 1

char currentPath[1024] = "/home/dakotarowland03/MudGame/orange/start"; // Global currentPath variable

int change_directory(const char *direction) {
    char str[] = "Orange Connect";
    char *cwd;
    char buffer[1024];
    cwd = getcwd(buffer, sizeof(buffer));
    FILE *file = fopen("desc.txt", "r");
    if (file == NULL) {
        perror("Failed to open desc.txt");
    }
    char descBuffer[UDP_MAX_LEN];
    while (fgets(descBuffer, sizeof(descBuffer), file) != NULL) {
        printf("Line: %s", descBuffer); // Output each line of the file
    }
    fclose(file);

    // Check for special room descriptions and change directory accordingly
    if (strcmp(descBuffer, "Orange Connect\n") == 0 && strcmp(direction, "north") == 0) {
        if (chdir("/home/dakotarowland03/MudGame/blue/start") != 0) {
            perror("Failed to change directory");
            printf("%s\n", cwd);
            return -1;
        }
        return 0;
    }
    if (strcmp(descBuffer, "Blue Connect\n") == 0 && strcmp(direction, "north") == 0) {
        if (chdir("/home/dakotarowland03/MudGame/red/start") != 0) {
            perror("Failed to change directory");
            printf("%s", cwd);
            return -1;
        }
        return 0;
    }
    if (strcmp(descBuffer, "Blue Start\n") == 0 && strcmp(direction, "south") == 0) {
        if (chdir("/home/dakotarowland03/MudGame/orange/start/east/south/east/east/east/north/north") != 0) {
            perror("Failed to change directory");
            printf("%s", cwd);
            return -1;
        }
        return 0;
    }
// If none of the special conditions are met, try to change the directory normally
    char newPath[1024];
    snprintf(newPath, sizeof(newPath), "%s/%s", currentPath, direction); // Assuming currentPath is a global variable

    if (chdir(direction) == -1) {
        perror("Failed to change directory to normal room");
        printf("%s", cwd);
        return -1;
    }

    return 0;
}

void output_description() { //debug
    FILE *file = fopen("desc.txt", "r");
    if (file == NULL) {
        perror("Failed to open desc.txt");
        return;
    }

    char descBuffer[UDP_MAX_LEN];
    while (fgets(descBuffer, sizeof(descBuffer), file) != NULL) {
        printf("%s", descBuffer); // Output each line of the file
    }
    fclose(file);
}

int main() {
	pid_t pid, sid;

    pid = fork(); // Creating a child process
    if (pid < 0) {
        exit(EXIT_FAILURE); // Exit if fork fails
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS); // Exit if parent process, to let the child continue as a new process
    }

    umask(0); // Change the file mode mask

    sid = setsid(); // Create a new session
    if (sid < 0) {
        exit(EXIT_FAILURE); // Exit on failure to create a new session
    }

    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE); // Change the working directory to root
    }

    close(STDIN_FILENO); // Close standard input
    close(STDOUT_FILENO); // Close standard output
    close(STDERR_FILENO); // Close standard error

    struct mosquitto *mosq = NULL;
    mosquitto_lib_init();
//attempts to connnect to mqtt broker
    mosq = mosquitto_new(CLIENTID, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    if (mosquitto_connect(mosq, ADDRESS, 1883, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to connect to MQTT broker.\n");
        return 1;
    }

    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    char buffer[UDP_MAX_LEN];
//creates socket connection
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(UDP_PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Binding failed");
        return 1;
    }

//this is what actually runs
    mosquitto_loop_start(mosq);
    chdir("/home/dakotarowland03/MudGame/orange/start");    //FILE *file;

    while (1) {
        FILE *file = fopen("desc.txt", "r");
        if (file == NULL) {
            perror("Failed to open desc.txt");
        }

        char descBuffer[UDP_MAX_LEN];
        while (fgets(descBuffer, sizeof(descBuffer), file) != NULL) {
            printf("%s", descBuffer); // Output each line of the file
        }
        fclose(file);

        struct mosquitto_message pubmsg;
        pubmsg.payload = descBuffer;
        pubmsg.payloadlen = strlen(descBuffer);
        pubmsg.qos = QOS;
        pubmsg.retain = 0;

        int n = recvfrom(sockfd, buffer, UDP_MAX_LEN, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0'; // Ensure the buffer is null-terminated
        printf("Received UDP message: %s\n", buffer);

        // Check if the message is a valid direction and change directory
        if (strcmp(buffer, "north") == 0 || strcmp(buffer, "south") == 0 ||
            strcmp(buffer, "east") == 0 || strcmp(buffer, "west") == 0) {

            if (change_directory(buffer) == 0) {
                // Successfully changed directory, output description
                output_description();
                FILE *file = fopen("desc.txt", "r");
        if (file == NULL) {
            perror("Failed to open desc.txt");
        }

        char descBuffer[UDP_MAX_LEN];
        while (fgets(descBuffer, sizeof(descBuffer), file) != NULL) {
            printf("%s", descBuffer); // Output each line of the file
        }
        fclose(file);

        struct mosquitto_message pubmsg;
        pubmsg.payload = descBuffer;
        pubmsg.payloadlen = strlen(descBuffer);
        pubmsg.qos = QOS;
        pubmsg.retain = 0;
                // Send contents of desc.txt over MQTT
                if (mosquitto_publish(mosq, NULL, "description", strlen(descBuffer), descBuffer, QOS, false) != MOSQ_ERR_SUCCESS) {
                    fprintf(stderr, "Failed to publish MQTT message.\n");
                }
            } else {
                if (mosquitto_publish(mosq, NULL, "description", strlen("Invalid Move"), "Invalid Move", QOS, false) !=
                    MOSQ_ERR_SUCCESS) {
                    fprintf(stderr, "Failed to publish MQTT message.\n");
                }
            }
        }
    }

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    close(sockfd);
    return 0;
}