#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

int str_find(char *arr, char c) {
  for (int i = 0; i < strlen(arr); i++) {
    if (arr[i] == c) return i;
  }
  return -1;
}

int main()
{
  int one = 1, client_fd, max_req_size = 8192;
  char req_line[512] = "";
  struct sockaddr_in svr_addr, cli_addr;
  socklen_t sin_len = sizeof(cli_addr);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    err(1, "can't open socket");

  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

  int port = 8080;
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(port);

  if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
    close(sock);
    err(1, "Can't bind");
  }

  listen(sock, 5);
  printf("server running on port %d\n", port);

  while (1) {
    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);

    if (client_fd == -1) {
      perror("Can't accept");
      continue;
    }

    char *request;
    request = (char *)malloc(max_req_size * sizeof(char));
    if(request == NULL) {
      printf("Error! memory not allocated.");
      exit(0);
    }

    read(client_fd, request, max_req_size);
    // printf("REQUEST:\n");
    // printf("%s\n", request);

    int newline_idx = str_find(request, '\n');
    if (newline_idx != -1) {
      strncpy(req_line, request, newline_idx);
      req_line[newline_idx] = '\0';
      printf("%s\n", req_line);
    }

    if (strncmp(request, "GET / HTTP/1.1", 14) == 0) {
      char res200[] = "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/html; charset=UTF-8\r\n\r\n"
      "<!DOCTYPE html><html><head><title>Hello World</title></head>"
      "<body><h1>Hello World!</h1></body></html>\r\n";

      // printf("RESPONSE:\n");
      // printf("%s\n", res200);
      printf("    ==>  200 OK\n");
      write(client_fd, res200, sizeof(res200) - 1);
    } else {
      char res404[] = "HTTP/1.1 404 Not Found\r\n";
      printf("    ==>  404 Not Found\n");
      write(client_fd, res404, sizeof(res404) - 1);
    }

    free(request);
    close(client_fd);
  }
}
