# genode-taskmanager
The taskmanager is a userspace application for monitoring purpose. It shows all threads currently running on the machine, with their IDs, execution time, ram quota, ram used and overall system load.

### Building
The custom Makefile builds the entire Fiasco.OC and Genode system including its toolchain and external dependencies into a `build/` and `contrib/` directory respectively. To manually execute steps within the build process see the Makefile or the Genode documentation:
http://genode.org/documentation/developer-resources/getting_started

The toolchain installs executables to `/usr/local/genode-gcc` as part of the Genode `tool_chain` script. Everything else stays within the repository.

After a first clone of this branch run `make` once. This will do the following:

* build and install Genode toolchain for `arm` or `x86` (target `toolchain`)
* download required external libraries into the `contrib` folder (target `ports`)
* create the target-specific build directory (target `genode_build_dir`)
* build taskmanager (target `taskmanager`)

After this, only build the targets you need. Inter-target dependencies are not set properly. When changing target platform, use the make target `platform` to only rebuild `genode_build_dir` and `taskmanager`.

To run the Genode taskmanager type `make run`

The Makefile will need additional adjustments for other kernels than Fiasco.OC.

### Required packages
The following packages are required for building the Genode toolchain:

`sudo apt-get install libncurses5-dev texinfo autogen autoconf2.64 g++ libexpat1-dev flex bison gperf cmake libXml2-dev libtool zlib1g-dev libglib2.0-dev`

For building Genode:

`sudo apt-get install make pkg-config gawk subversion expect git`

For running Genode in QEMU:

`sudo apt-get install libxml2-utils syslinux`

Inside QEMU run, if you are told to:

`git submodule update --init pixman`
`git submodule update --init dtc`

For some additional ports you may need:

`sudo apt-get install xsltproc yasm iasl lynx`

### Folder structure
Custom repos:

| Folder                              | Description                                      |
| ----------------------------------- | ------------------------------------------------ |
| `repos/taskmanager/run/`                  	| run file configuration for task manager                  |
| `repos/taskmanager/src/taskmanager/re/`       | taskmanager                                      |
| `repos/taskmanager/src/idle/` 		| idle process to show system load                 |

The provided Makefile creates the following directories:

| Folder                      | Description               |
| --------------------------- | ------------------------- |
| `build/`                    | all build files           |
| `build/toolchain-TARGET/`   | Genode toolchain          |
| `build/genode-TARGET/`      | Genode build dir          |
| `contrib/`                  | external Genode libraries |

### Fine-grained CPU time
The Fiasco.OC kernel by default only returns timing information at a resolution of 1ms. Granularity can be increased by changing line 51 of `build/genode-TARGET/kernel/fiasco.oc/globalconfig.out` to
`CONFIG_FINE_GRAINED_CPUTIME=y`
