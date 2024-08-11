# Laboratory of Nuclear and Subnuclear physics 2: electron absorption simulation

The ide behinf this GEANT4 simulatin is to reproduce the behaviour of a muon in iron slabs. Counting the number of electrons that derive from the decayment of the muons in iron and the number of electrons absorbed and not absorbed.

## Design

The simulation is based on a mu- particle that is sent in the -y direction, passing through a 1 m thick concrete block before arriving in the iron slabs (there are also 2 0.001 mm silicon slabs, that will be removed).

The energy of the mu- is set to 500 MeV in the `run.mac` file (can be changed).

## Geant4 installation

The simulation has been developed on a machine with an Apple M1 processor and runned in a Linux x86_64 (Mint) Server.

To install Geant4 I reccomend to use conda environment (Anaconda or Miniconda) with [Conda Forge]([https://pages.github.com/](https://conda-forge.org)):

```
$ conda create -n lab2sim
$ conda activate lab2sim
$ conda config --add channels conda-forge
$ conda config --set channel_priority strict
$ conda install root geant4
```

Replace `lab2sim` with the name you like.

## Run the simulation

To run the simulation you can:

```
$ cd /path/to/lab2sim
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . -- -j $(nproc)
$ ./lab2run run.mac
```

The command `cmake --build . -- -j $(nproc)` can be replaced with `make`.
In this way with `./lab2run run.mac` the simulation is runned in batch mode, to see the actual simulation design the command to run is `./lab2run`, always in the build folder.


NOTE: you must be in your enviroment with geant4 and root installed.

Or you can just:
```
$ cd /path/to/lab2sim
$ bash run.bash
```

In this case the analysis is runned after the the end of the simulation.
Note: with this method is necessary to delete the build folder every time the file run.mac is changed.

## Analysis
The file `analysis.cpp` contains the analysis code, it has to be runned with root.
All the result are stored in the `result.txt` file.

##  run.mac file
The `run.mac` can be changed, right now it generates 6 run with 1000000 of events (muons) each run and every muon has an energy of 500 MeV.

## Additional notes
This is a rather basic simulation, that will be refined and expanded.

I do not recommend to run the simulation and analysis on a local computer, if it's possible is better to use a server.
