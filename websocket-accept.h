#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

// https://en.wikipedia.org/wiki/WebSocket
#ifndef WEBSOCKET_KEY_SIZE
#define WEBSOCKET_KEY_SIZE 24
#endif

#ifndef WEBSOCKET_ACCEPT_KEY_SIZE
#define WEBSOCKET_ACCEPT_KEY_SIZE 28
#endif

  /**
   * @brief
   *
   * @param websocket_key size should be WEBSOCKET_KEY_SIZE
   * @param buffer size should be WEBSOCKET_ACCEPT_KEY_SIZE
   * @return size_t
   */
  size_t websocket_accept(const char websocket_key[WEBSOCKET_KEY_SIZE], char buffer[WEBSOCKET_ACCEPT_KEY_SIZE]);

#ifdef __cplusplus
}
#endif
