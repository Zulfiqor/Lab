#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

#define SERVER_PORT 12345
#define QUEUE_SIZE 5




void main (int argc, char *argv[])
{
	int error, on;
	int listen_sd;

	int accept_sd;
	char buffer[80];
	struct sockaddr_in addr;
	pid_t child_pid;

	// create listening socket
	listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sd < 0) {
		perror("socket() failed");
		exit(-1);
	}

	error = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
						(char *)&on, sizeof(on));

	// setoption error
	if (error < 0) {
		perror("setsockopt() failed");
		close(listen_sd);
		exit(-1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port  = htons(SERVER_PORT);
	error = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));

	if (error < 0) {
		perror("bind() failed");
		close(listen_sd);
		exit(-1);
   }

	error = listen(listen_sd, QUEUE_SIZE);
	if (error < 0) {
		perror("listen() failed");
		close(listen_sd);
		exit(-1);
	}

	printf("The server is ready\n");

	while (1) {
		accept_sd = accept(listen_sd, NULL, NULL);
		if (accept_sd < 0) {
			perror("accept() failed");
			close(listen_sd);
			exit(-1);
		}
		// here start new thread
		pthread_t pthread;
		if (thread_def) {
			pthread_create(&pthread, NULL, &thread_func, (void*)&accept_sd);
		} else {	
	   		child_pid = fork();
	   		if(child_pid == 0) {
				thread_func((void*)&accept_sd);
			}
		}
	}
	close(listen_sd);
}
