#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdbool.h>
#include <inttypes.h>


struct ConfigInfo {    
    bool is_server;          /* if the current node is server */

    int  msg_size;           /* the size of each echo message */
    int  num_concurr_msgs;   /* the number of messages can be sent concurrently */

    char *ip_address;         /* ip of server */
    char *sock_port;         /* socket port number */
}__attribute__((aligned(64)));

extern struct ConfigInfo config_info;

void print_config_info ();

#endif /* CONFIG_H_*/
