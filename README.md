Small ESP32 based device which my parents can use to notify me if I am on my computer and need to come downstairs.

Posts data to an MQTT server. [A java program on my computer](https://github.com/Derkades/mqtt-notifier) listens for messages on the specific topic and if it receives one it plays a sound.

![Physical device made from cardboard](https://i.imgur.com/3Ep5LUs.jpg)

## Led status codes
RED: Standby, waiting for button press<br>
BLUE: Connecting to wifi and MQTT server<br>
GREEN: Successfully connected and sent message.<br>
RED FLASHING: An error occured while trying to connect to the MQTT server<br>
BLUE FLASHING: 2 seconds after success (green). As a reminder that the device should be turned off again.<br>
