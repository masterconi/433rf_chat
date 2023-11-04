#include <VirtualWire.h>
#include "xorencrypt.h"

const int transmitterPin = 12; // Define the digital pin for the RF transmitter
const int receiverPin = 11;    // Define the digital pin for the RF receiver

char encryptionKey = 'K'; // XOR encryption key



void setup() {
  Serial.begin(115200);
  vw_set_tx_pin(transmitterPin);
  vw_set_rx_pin(receiverPin);
  vw_setup(2000); // Bits per second
  vw_rx_start();
}

void loop() {
  // Sender
  if (Serial.available() > 0) {
    Serial.println("Enter your message:");
    while (Serial.available() == 0); // Wait for user input
    String message = Serial.readString();

    // Encrypt the message using XOR
    String encryptedMessage = xorEncrypt(message);

    // Send the encrypted message via RF transmitter
    vw_send((uint8_t*)encryptedMessage.c_str(), encryptedMessage.length() + 1);
    vw_wait_tx(); // Wait until the whole message is sent

    Serial.println("Message sent: " + message);
  }

  // Receiver
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    if (buflen > 0) {
      String received = (char*)buf;

      // Decrypt the received message using XOR
      String decryptedMessage = xorEncrypt(received);

      Serial.print("Received message: ");
      Serial.println(decryptedMessage);
    }
  }
}



