#include <stdio.h>

#include "debug.h"
#include "config.h"
#include "ib.h"
#include "setup_ib.h"
#include "client.h"
#include "server.h"

FILE	*log_fp	     = NULL;

int	init_env    ();
void	destroy_env ();

int main (int argc, char *argv[])
{
    int	ret = 0;

    if (argc != 4) {
        // printf ("Usage: %s config_file sock_port server_name\n", argv[0]);
        printf ("Usage: %s Type:[server/client] ip_addre sock_port\n", argv[0]);
        return 0;
    }    

    config_info.is_server = !strcmp(argv[1],"server");
    config_info.ip_address = argv[2];
    config_info.sock_port = argv[3];
    config_info.num_concurr_msgs = 1;
    config_info.msg_size = 8;

    init_env();

    ret = setup_ib ();
    check (ret == 0, "Failed to setup IB");

    if (config_info.is_server) {
        ret = run_server ();
    } else {
        ret = run_client ();
    }
    check (ret == 0, "Failed to run workload");

 error:
    close_ib_connection ();
    destroy_env         ();
    return ret;
}    

int init_env ()
{
    char fname[64] = {'\0'};

    if (config_info.is_server) {
        sprintf (fname, "server.log");
    } else {
        sprintf (fname, "client.log");
    }
    log_fp = fopen (fname, "w");
    check (log_fp != NULL, "Failed to open log file");

    log (LOG_HEADER, "IB Echo Server");
    print_config_info ();

    return 0;
 error:
    return -1;
}

void destroy_env ()
{
    log (LOG_HEADER, "Run Finished");
    if (log_fp != NULL) {
        fclose (log_fp);
    }
}
