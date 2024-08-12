# Laboratory of Nuclear and Subnuclear physics 2: electron absorption simulation

The idea behind this GEANT4 simulation is to reproduce the behaviour of a muon in iron slabs. Counting the number of electrons that derive from the decay of the muons in iron and the number of absorbed and non-absorbed electrons.

## Design
<img width="159" alt="lab2runDesign" src="https://github.com/user-attachments/assets/95ec60b3-6cf8-4fc7-b00e-04dfa5c063ce">

The simulation involves a muon particle sent in the -y direction, passing through a 1-meter-thick concrete block before reaching the iron slabs. Note that there are also two 0.001 mm silicon slabs, which will be removed in next versions.

The energy of the muon is set to 500 MeV in the run.mac file, but this value can be changed.

## Geant4 installation

The simulation has been developed on a machine with an Apple M1 processor and run on a Linux x86_64 (Mint) server.

To install Geant4 I recommend using a Conda environment (Anaconda or Miniconda) with [Conda Forge]([https://pages.github.com/](https://conda-forge.org)):

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

The command cmake --build . -- -j $(nproc) can be replaced with make. Running ./lab2run run.mac executes the simulation in batch mode, to see the actual simulation design the command to run is `./lab2run`, always in the build folder.


NOTE: you must be in your enviroment with geant4 and root installed.

Or you can just:
```
$ cd /path/to/lab2sim
$ bash run.bash
```

In this case the analysis is runned after the end of the simulation.
Note: With this method, it is necessary to delete the build folder each time the run.mac file is changed.

## Analysis
The file `analysis.cpp` contains the analysis code, it has to be runned with root.
All the result are stored in the `result.txt` file.

##  run.mac file
The `run.mac` can be changed, right now it generates 6 run with 1000000 of events (muons) each run and every muon has an energy of 500 MeV.

With:

-`/gun/energy value unitOfMeasurement` the energy value of the muon can be changed;

-`/blocks/nBlocks numberOfSlabs` the number of slabs can be changed (every slab is 0.5 cm), but every time thenumber of slabs is changed the command `/run/reinitializeGeometry` is needed;

-`/gun/particle typeOfParticle` the type of particle can be changed;

-`/run/beamOn numberOfEvents` the number of events per run can be changed.


## Additional notes
This is a rather basic simulation, that will be refined and expanded.

I do not recommend to run the simulation and analysis on a local computer, if possible, it is better to use a server.
