#include <microhttpd.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

#define PORT 8080

using namespace std;

// HTTP 请求处理函数
static enum MHD_Result handle_request(void *cls,
                                       struct MHD_Connection *connection,
                                       const char *url,
                                       const char *method,
                                       const char *version,
                                       const char *upload_data,
                                       size_t *upload_data_size,
                                       void **con_cls) {
    // 只处理 GET 请求
    if (strcmp(method, "GET") != 0) {
        const char *response_str = "Method Not Allowed";
        struct MHD_Response *response = MHD_create_response_from_buffer(
            strlen(response_str), (void*)response_str, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, response);
        MHD_destroy_response(response);
        return (MHD_Result)ret;
    }

    // 返回 Hello World
    const char *response_str = "Hello World";
    struct MHD_Response *response = MHD_create_response_from_buffer(
        strlen(response_str), (void*)response_str, MHD_RESPMEM_PERSISTENT);

    MHD_add_response_header(response, "Content-Type", "text/plain");

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return (MHD_Result)ret;
}

int main() {
    struct MHD_Daemon *daemon;

    // 127.0.0.1
    struct sockaddr_in addr4;
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr4.sin_addr);

    // 启动服务器，通过 MHD_OPTION_SOCK_ADDR 绑定到指定地址
    daemon = MHD_start_daemon(
        MHD_USE_SELECT_INTERNALLY,
        PORT,
        NULL, NULL,
        &handle_request, NULL,
        MHD_OPTION_SOCK_ADDR, &addr4,
        MHD_OPTION_END
    );

    if (NULL == daemon) {
        cerr << "Failed to start server on port " << PORT << endl;
        return 1;
    }

    cout << "========================================" << endl;
    cout << "Server started successfully!" << endl;
    cout << "Listening on: http://127.0.0.1:" << PORT << endl;
    cout << "Press Enter to stop the server..." << endl;
    cout << "========================================" << endl;

    cin.get();

    MHD_stop_daemon(daemon);
    cout << "Server stopped." << endl;

    return 0;
}