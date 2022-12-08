# Game project template for Flipper Zero

Template for a [Flipper Zero](https://github.com/flipperdevices/flipperzero-firmware) game with the minimum required structure, resources and methods.

# How To

### Getting started

1. Clone the [flipperzero-firmware](https://github.com/flipperdevices/flipperzero-firmware) repository or another firmware that you use (firmware list can be found here [awesome-flipperzero](https://github.com/djsime1/awesome-flipperzero#firmwares--tweaks)).
2. Create a symbolic link in `applications_user` named **game_app** (or any another name), pointing to this repository.
3. Compile by command `./fbt`

### Variables to change

1. Open project folder with [Visual Studio Code](https://code.visualstudio.com/download)
2. Open `application.fam` file and edit next values:
appid - your unique application id without whitespaces (used in fbt compiling commands)
name - application name that ypu see in Flipper menu

### Compiling variant 1

1. Compile by command `./fbt game_app` (*change to your app id*)
2. Copy `build/f7-firmware-D/.extapps/game_app.fap` (*or your_app_id.fap*) to **apps/Games** on the SD card or by [qFlipper](https://flipperzero.one/update) app.

### Compiling variant 2

1. Connect your Flipper via USB
2. Execute command `./fbt launch_app APPSRC=game_app` (*change to your app id*), and the game will run automatically on your Flipper device after compilation.
