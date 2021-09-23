#pragma once

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>


const int SOCKET_BUFFER_1K = 1024;
const int SOCKET_BUFFER_2K = 2 * 1024;
const int SOCKET_BUFFER_1M = 1024 * 1024;

const int MAX_LISTEN_BACK_POOL = 5;
const unsigned short server_port = 9898;