
EK-LM4F120XL Stellaris Launchpad evaluation board: https://estore.ti.com/Stellaris-LaunchPad.aspx

Toolchain: https://github.com/esden/summon-arm-toolchain


The Launchpad on-board programmer interface uses an ICDI protocol that is not yet supported by OpenOCD. However, there's a simple flasher tool that will do the job:

https://github.com/utzig/lm4tools


Fixing permissions issues so 'sudo' isn't required for programming:
Ensure the user is in the plugdev group. `groups USERNAME` should give a list of groups containing 'plugdev'.
If not, add the user with `sudo useradd -G plugdev USERNAME`.

Create a file in /etc/udev/rules.d/ named something like '11-lm4f-launchpad.rules', with the following contents:

    ATTRS{idProduct}=="00fd", ATTRS{idVendor}=="1cbe", MODE="666", GROUP="plugdev"

Run `sudo udevadm trigger` to reload the udev rules.



# LICENSE

Unless noted otherwise, all code is released under the MIT license.
