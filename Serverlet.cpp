// Server side C/C++ program to demonstrate Socket
// programming
#ifndef SERVERLET_C
#define SERVERLET_C
#ifndef SERVERLET_H
	#include "Serverlet.h"
#endif 
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <utility>      // std::move
#include <future>       // std::packaged_task, std::future
#define PORT 8080

void Serverlet::createListener(){

int server_fd, new_socket;
	ssize_t valread;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);
	char buffer[1024] = { 0 };

// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt\n");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen\n");
		exit(EXIT_FAILURE);
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				&addrlen))
		< 0) {
		perror("accept\n");
		exit(EXIT_FAILURE);
	}

	valread = read(new_socket, buffer,
				1024 - 1); // subtract 1 for the null
							// terminator at the end
	printf("%s\n", buffer);

// 	std::packaged_task<Response(std::string)> tsk (this->appRouter->getCallBack()); // package task

//   std::thread(this->appRouter->getCallBack(),"abc").detach();   // spawn thread and call task
}





int Serverlet::socketFlow(){
	int server_fd, new_socket;
	ssize_t valread;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	char* hello = "HTTP/1.1 200 OK\n"
"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
"Content-Type: html\n"
"Accept-Ranges: bytes\n"
"Connection: close\n"
"\n"
"<!DOCTYPE html>\n"
"<html>\n"
// "<head>\n"
// "<title>Page Title</title>\n"
// "</head>\n"
// "<body>\n"
// "\n"
// "<h1>This is a Heading</h1>\n"
// "<p>This is a paragraph.</p>\n"
// "\n"
// "</body>\n"
// "</html>\n";
"<div id=\"game-board\">\n"
	"<div class=\"column\" id=\"column-0\" data-x=\"0\">\n"
		"<svg height=\"100\" width=\"100\" class=\"row-5\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" fill=\"red\" class=\"free\" />\n"
		"</svg>\n"
		"<svg height=\"100\" width=\"100\" class=\"row-4\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-3\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-2\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-1\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-0\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
	"</div>\n"
	"<div class=\"column\"  id=\"column-1\" data-x=\"1\">\n"
		"<svg height=\"100\" width=\"100\" class=\"row-5\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-4\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-3\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-2\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-1\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-0\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
	"</div>\n"
	"<div class=\"column\" id=\"column-2\" data-x=\"2\">\n"
		"<svg height=\"100\" width=\"100\" class=\"row-5\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-4\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-3\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-2\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-1\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-0\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
	"</div>\n"
	"<div class=\"column\" id=\"column-3\" data-x=\"3\">\n"
		"<svg height=\"100\" width=\"100\" class=\"row-5\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-4\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-3\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-2\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-1\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-0\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
	"</div>\n"
	"<div class=\"column\" id=\"column-4\" data-x=\"4\">\n"
		"<svg height=\"100\" width=\"100\" class=\"row-5\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-4\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-3\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-2\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-1\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-0\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
	"</div>\n"
	"<div class=\"column\" id=\"column-5\" data-x=\"5\">\n"
		"<svg height=\"100\" width=\"100\" class=\"row-5\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-4\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-3\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-2\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-1\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-0\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
	"</div>\n"
	"<div class=\"column\" id=\"column-6\" data-x=\"6\">\n"
		"<svg height=\"100\" width=\"100\" class=\"row-5\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-4\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-3\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-2\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-1\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
		"<svg height=\"100\" width=\"100\" class=\"row-0\">\n"
		  "<circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"#0B4E72\" stroke-width=\"3\" class=\"free\" />\n"
		"</svg>\n" 
	"</div>\n"
"</div>\n";





	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt\n");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen\n");
		exit(EXIT_FAILURE);
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				&addrlen))
		< 0) {
		perror("accept\n");
		exit(EXIT_FAILURE);
	}
        printf("in 4\n");

	valread = read(new_socket, buffer,
				1024 - 1); // subtract 1 for the null
							// terminator at the end
	printf("%s\n", buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	close(server_fd);
	return 0;
}
#endif