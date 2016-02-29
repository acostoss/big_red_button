# Big Red Button driver

Barebones driver for the [Dream Cheeky 'Big Red Button'](http://dreamcheeky.com/big-red-button), for triggering an intro video.

Assumes UDEV rule has been set up. 

**Example:**
    `ACTION=="add", ENV{ID_MODEL}=="DL100B_Dream_Cheeky_Generic_Controller", SYMLINK+="big_red_button", MODE="0666", RUN+="/usr/bin/mosquitto_pub -h mqtt.opensensors.io -t /my/big/red/button -m Add"`
    `ACTION=="remove", ENV{ID_MODEL}=="DL100B_Dream_Cheeky_Generic_Controller", RUN+="/usr/bin/mosquitto_pub -h mqtt.opensensors.io -t /my/big/red/button -m Add"`

Your `ENV{ID_MODEL}` may differ. Use `udevadm` to verify yours.

### Todo
* Fork off video process to allow for things such as cancellation (process kill) on button window closure.
* Show an idle image/video before button press.