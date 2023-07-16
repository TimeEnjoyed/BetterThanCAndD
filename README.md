# 2023 Codejam

## Project Description

This was supposed to be a nostalgia clip fetcher, but unfortunately, due to time constraints,
the project was not able to be finished by the end of the Codejam. The way it was supposed
to work was that the user would type the name of a browser source (already created by the user),
and the OBS plugin would change the URL of the browser source to a random clip from a streamer
(likely the user).

## Build Instructions
Compilation was just tested on Linux. CMake, nlohmann/json, and libcpr/cpr are required to build
the project.

To build, one can type on a terminal in the root directory of the project:
```
$ mkdir build # ni -ItemType "Directory" build
$ cd build    # sl build
$ cmake ..    # cmake ..
$ make        # cmake --build .
$ sudo cp codejam.so /usr/lib/x86_64-linux-gnu/obs-plugins/codejam.so   # Copy-Item codejam.so "Whever the OBS plugins for Windows are kept"

```

## Links Containing Information
The details for the CodeJam can be found [here](https://codejam.timeenjoyed.dev/).
