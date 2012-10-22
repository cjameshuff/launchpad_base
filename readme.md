
Starter project for the EK-LM4F120XL Stellaris Launchpad evaluation board:
https://estore.ti.com/Stellaris-LaunchPad.aspx


# Toolchain

A bare-metal ARM GCC toolchain and OpenOCD can be installed with this script: https://github.com/esden/summon-arm-toolchain


# Programming

The Launchpad on-board programmer interface uses an ICDI protocol that is not yet supported by OpenOCD. However, there's a simple flasher tool that will do the job: https://github.com/utzig/lm4tools


# Linux USB Permissions

udev may need to be configured to make the LaunchPad accessible to non-superusers. If programming only works with `sudo`:
Ensure the user is in the plugdev group. `groups USERNAME` should give a list of groups containing 'plugdev'. If not, add the user with `sudo useradd -G plugdev USERNAME`.

Create a file in /etc/udev/rules.d/ named something like '11-lm4f-launchpad.rules', with the following contents:

    ATTRS{idProduct}=="00fd", ATTRS{idVendor}=="1cbe", MODE="666", GROUP="plugdev"

Run `sudo udevadm trigger` to reload the udev rules.


# Makefile

The makefile puts intermediate object files in a separate `obj` directory tree, and generates dependencies automatically. Add source files to the SOURCES variable, `.c`, `.cpp`, and `.s` extensions are recognized. Object files have .o appended to the full file name, so it is possible to have sources files whose names differ only in extension.

There's a couple new targets in addition to the usual `make clean` and default `make` targets:

* `make disasm` generates disassembly output.
* `make flash` flashes a Stellaris LaunchPad using lm4flash.


# StellarisWare

Pick a location for the StellarisWare libraries, such as /embedded/StellarisWare. Adjust STELLARIS_ROOT in the makefile if you put it elsewhere.

Build/rebuild the driverlib library: simply `cd` to StellarisWare/driverlib and run `make`


# LICENSE

Unless noted otherwise, all code is released under the MIT license.
