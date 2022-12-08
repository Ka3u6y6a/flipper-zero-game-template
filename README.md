# Game project template for Flipper Zero

Template for a [Flipper Zero](https://github.com/flipperdevices/flipperzero-firmware) game with the minimum required structure, resources and methods.

# How To

### Getting started

1. Clone the Flipper Zero firmware repository from the following link: [flipperzero-firmware](https://github.com/flipperdevices/flipperzero-firmware)
another firmware that you use (firmware list can be found here [awesome-flipperzero](https://github.com/djsime1/awesome-flipperzero#firmwares--tweaks)).
2. In the `applications_user` directory, create a symbolic link named **game_app** (or any other desired name) that points to this repository.
3. Compile firmware by running the command `./fbt` in a terminal.

### Customization

To customize the game, open the project folder in [Visual Studio Code](https://code.visualstudio.com/download) and edit the `application.fam` file.
In this file, you can change the `appid` filed (which should be unique and not contain any whitespace characters) and the  `name` field, which is the name that will be displayed in the Flipper menu.

Once the game is ready to be compiled, you have two options:

#### Compiling option 1

1. Compile by running `./fbt __your_app_id__`, e.g. `./fbt game_app`
2. Copy `build/f7-firmware-D/.extapps/__your_app_id__.fap` to **apps/Games** on the SD card or by [qFlipper](https://flipperzero.one/update) app.

#### Compiling option 2

1. Connect the Flipper device to your computer via USB
2. Run the command `./fbt launch_app APPSRC=__your_app_id__` (e.g. `./fbt launch_app APPSRC=game_app`). This will compile and launch the game on the device automatically.
