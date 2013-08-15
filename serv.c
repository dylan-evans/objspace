#include  <microhttpd.h>
#include <stdio.h>

#define HELLO "Hello, World!"

static int req(void *cls, 
               struct MHD_Connection *connection, 
               const char *url, 
               const char *method,
               const char *version, 
               const char *upload_data, 
               size_t *upload_data_size,
               void **ptr)
{
    int ret;
    struct MHD_Response *response;
    static int dummy;
    char *doc;

    if(&dummy != *ptr)
    {
        *ptr = &dummy;
        return MHD_YES;
    }
    doc = malloc(strlen(url) + strlen(HELLO) + 1024);
    sprintf(doc, "%s (%s)", HELLO, url);
            
    response = MHD_create_response_from_data(strlen(doc), 
                                             (void*)doc,
                                             MHD_NO,
                                             MHD_NO);
    ret = MHD_queue_response(connection, 
                             MHD_HTTP_OK, 
                             response);
    MHD_destroy_response(response);
    return ret;
}


int main()
{
    struct MHD_Daemon *d;

    d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                         8080, NULL, NULL, &req, "Hello?", MHD_OPTION_END);
    sleep(10000);
    return 0;
}
