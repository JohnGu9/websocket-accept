# Intro

Generate a `Sec-WebSocket-Accept` from a `Sec-WebSocket-Key`

# Example

```c
const char websocket_key[] = "dGhlIHNhbXBsZSBub25jZQ=="; // 24 chars
const char result[28]; // 28 chars
websocket_accept(websocket_key, result);
```
