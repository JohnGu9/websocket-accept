#include "websocket-accept.h"
#include "sha1/sha1.h"

#include <assert.h>

// reference: https://stackoverflow.com/a/41094722
size_t _base64_encode(const unsigned char *const src, size_t len,
                      unsigned char *const out_str, size_t out_size)
{
  static const unsigned char _base64_table[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  unsigned char *out, *pos;
  const unsigned char *end, *in;

  size_t olen = 4 * ((len + 2) / 3); /* 3-byte blocks to 4-byte */
  assert(olen >= out_size);

  if (olen < len)
    return 0; /* integer overflow */

  out = (unsigned char *)out_str;

  end = src + len;
  in = src;
  pos = out;
  while (end - in >= 3)
  {
    *pos++ = _base64_table[in[0] >> 2];
    *pos++ = _base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
    *pos++ = _base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
    *pos++ = _base64_table[in[2] & 0x3f];
    in += 3;
  }

  if (end - in)
  {
    *pos++ = _base64_table[in[0] >> 2];
    if (end - in == 1)
    {
      *pos++ = _base64_table[(in[0] & 0x03) << 4];
      *pos++ = '=';
    }
    else
    {
      *pos++ = _base64_table[((in[0] & 0x03) << 4) |
                             (in[1] >> 4)];
      *pos++ = _base64_table[(in[1] & 0x0f) << 2];
    }
    *pos++ = '=';
  }

  return olen;
}

size_t websocket_accept(const char websocket_key[WEBSOCKET_KEY_SIZE], char buffer[WEBSOCKET_ACCEPT_KEY_SIZE])
{
#define WEBSOCKET_MAGIC_CODE "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
#define WEBSOCKET_MAGIC_CODE_SIZE (sizeof(WEBSOCKET_MAGIC_CODE) - 1)

  unsigned char obuf[20];
  SHA1_CTX ctx;
  SHA1Init(&ctx);
  SHA1Update(&ctx, (const unsigned char *)websocket_key, WEBSOCKET_KEY_SIZE);
  SHA1Update(&ctx, (const unsigned char *)WEBSOCKET_MAGIC_CODE, WEBSOCKET_MAGIC_CODE_SIZE);
  SHA1Final(obuf, &ctx);

  return _base64_encode(obuf, sizeof(obuf), (unsigned char *)buffer, WEBSOCKET_ACCEPT_KEY_SIZE);
}
