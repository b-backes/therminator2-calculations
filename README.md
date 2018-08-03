# therminator2-calculations

The scripts read files in a directory *gev with util 100 root files named as event*.root.
In the *gev directory, the Particles.C file must be added.
The ratios.c file must be in the *gev directory as well. It reads a counts.dat file and calculates 
the ratios between K+/Pi+ and K-/Pi-.
In order to generate the counts.dat file one must run ./Particles.sh
