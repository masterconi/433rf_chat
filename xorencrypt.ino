#include "xorencrypt.h"

String xorEncrypt(const String& message) {
  String encryptedMessage = message;
  for (int i = 0; i < message.length(); i++) {
    encryptedMessage[i] = message[i] ^ encryptionKey;
  }
  return encryptedMessage;
}