#include "websocket-accept.h"

#include <assert.h>
#include <stdio.h>

int main()
{
    const char websocket_key[] = "dGhlIHNhbXBsZSBub25jZQ==";
    char websocket_accept_result[WEBSOCKET_ACCEPT_KEY_SIZE];
    const size_t websocket_accept_size = websocket_accept(websocket_key, websocket_accept_result);
    printf("size(%zu) str(%.*s)\n", websocket_accept_size, (int)websocket_accept_size, websocket_accept_result);

    const char target[] = "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=";
    assert(websocket_accept_size == (sizeof(target) - 1));
    assert(memcmp(websocket_accept_result, target, websocket_accept_size) == 0);
    return 0;
}
