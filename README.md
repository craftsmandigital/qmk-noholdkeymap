# noholdkeymap

All my keyboard collected in one userspace. 
This compile is based on qmk release tag: 0.23.6
## The noholdkeymap layout

The layout is inspired by [Miryoku](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku) keyboard layout, but there are quite differences. I admit that I have stolen much of his setup, because it is so vel suited to support a bunce of keyboards.

## Your keyboard

If you want to use this keymap yourself, here are the instructions to use it. It is easier with an example. Example with the "Lets'split" keyboard.
Check out what keymap layout your keyboard is using. Let's say that you want to use the "Lets'split" keyboard. Check in the `keymap.c` file, in the `default` layout  for your keyboard --%3E `.../qmk_firmware/keyboards/lets_split/keymaps/default/keymap.c` when looking in this file, we can see that the name of the layout is `LAYOUT_ortho_4x12`.
Look in the folder for community layouts(`.../qmk_firmware/layouts/community/`), to see if you can find your layout (`LAYOUT_ortho_4x12`). It's found in folder `.../qmk_firmware/layouts/community/ortho_4x12/`
If you have found a folder called `.../qmk_firmware/layouts/community/ortho_4x12/joppa` for your keyboard layout then you are ready to go. If not, then you have to copy the folder `.../qmk_firmware/layouts/community/ortho_4x12/manna-harbour_miryoku/` and rename it to `.../qmk_firmware/layouts/community/ortho_4x12/joppa/`.
Now you could be ready to flash your keyboard. Flashing is done with the instruction on Miryoku website. [Find your Keyboard on the page](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku). When your keyboard is found. you could replace `manna-harbour_miryoku` with `joppa` . Here is the [description to flash the Lets'split keyboard](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku#ortho_4x12):

```bash
make lets_split:manna-harbour_miryoku:\
    MIRYOKU_MAPPING=SPLIT \
    MIRYOKU_ALPHAS=QWERTY \
    MIRYOKU_NAV=VI \
    MIRYOKU_CLIPBOARD=WIN
```

Here under is the modified version of this command you could use. All the options could work except `MIRYOKU_ALPHAS` this could always be `QWERTY` . my layout has only support for `QWERTY` :

```bash
make lets_split:joppa:\
    MIRYOKU_MAPPING=SPLIT \
    MIRYOKU_ALPHAS=QWERTY \
    MIRYOKU_NAV=VI \
    MIRYOKU_CLIPBOARD=WIN
```

## My keyboards

### [ Lets'split](https://falba.tech/product/lets-split-standard-lift-bamboo-wood-case-with-oil-finish/)

Follow instructions over, in the [Your keyboard](#your-keyboard) section to flash. There are different layouts. I find the layout above most attractive.  My operating system is Windows

### [Dactyl manuform 3x5_3](https://www.dlford.io/keyboard-build-guide-per-key-rgb-leds/)

This is a hardwired keyboard witch is built on [instructions on these page](https://www.dlford.io/keyboard-build-guide-per-key-rgb-leds/). My keyboard is without LED lightening. The communication between the halves is serial, set up as [this](https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/dactyl_manuform/readme.md#wiring).

#### Flashing trouble

Trouble when flashing the keyboard. All keys are dead if these criteria's is not met:
A litle tweak has to be done in this file
[.../qmk_firmware/keyboards/handwired/dactyl_manuform/3x5_3
/info.json](https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/dactyl_minidox/info.json). The property `diode_direction`. has to be set to `COL2ROW` instead of `ROW2COL`.

```json
    "diode_direction": "COL2ROW",
```

In the file [.../qmk_firmware/users/noholdkeymap/rules.mk](https://github.com/craftsmandigital/qmk-noholdkeymap/blob/main/rules.mk), these lines of config must be present:

```bash
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no     # Enable WS2812 RGB matrix
RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no
```

#### Here is the command to flash the Dactyl manuform 3x5_3

```bash
make handwired/dactyl_minidox:noholdkeymap
```

## Installation
### Step 1
Clone QMK environment and checkout the tag `0.23.6`
``` bash
cd /path/to/your/directory
git clone git@github.com:qmk/qmk_firmware.git
cd qmk_firmware
git checkout tags/0.23.6
```

 ### Step 2
Go into the `.../qmk_firmware/users/` folder and clone the `noholdkeymap` repo
``` bash
cd .../qmk_firmware/users
git clone git@github.com:craftsmandigital/qmk-noholdkeymap.git noholdkeymap
cd qmk_firmware
git checkout tags/0.23.6
```

### Step 3
- Copy the  `manna-harbour_miryoku` folder with content from [this point in manna-harbour_miryoku repo](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/layouts/community/split_3x5_3) into the path `.../qmk_firmware/layouts/community/split_3x5_3/`
- your folder structure could look like this now:`.../qmk_firmware/layouts/community/split_3x5_3/manna-harbour_miryoku`.
- Rename `manna-harbour_miryoku` folder to `noholdkeymap`
-  your folder structure could look like this now:`.../qmk_firmware/layouts/community/split_3x5_3/noholdkeymap`.
- Do the same process as over for my Lets'split keyboard. Here is the [point in repo for manna-harbour_miryoku](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/layouts/community/ortho_4x12)
	- The final result could look like this: `.../qmk_firmware/layouts/community/ortho_4x12/noholdkeymap`.

### Step 4
I have to do this. It is possible i have wired my keyboard in opposite direction than I could, or it  is a bug.

The property `diode_direction`. has to be set to `COL2ROW` instead of `ROW2COL`. This property is located in this file: [.../qmk_firmware/keyboards/handwired/dactyl_minidox/info.json](https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/dactyl_minidox/info.json)

```json
    "diode_direction": "COL2ROW",
```


