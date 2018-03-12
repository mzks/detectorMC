# README

## How to run

```
$ mkdir build
$ cd build
$ cmake ../source
$ make && make install
$ cd ../bench
$ ../bin/rock rock.mac
```

## Generator information
Main macro is bench/rock.mac

```
# create physics
/physics_lists/em/GammaNuclear true
/physics_lists/em/MuonNuclear true

# change detector parameter
/rock/det/setField 0.0 tesla
/rock/det/setMaxStep  0.1 cm

#/gun/rock/vtx 1 #top
#/gun/rock/particle 2 #n
/rock/det/setBoronSize 5.0 mm

##total neutron flux
/gun/rock/vtx 3 #flux
/gun/rock/particle 4 #real n spectrum

#/tracking/verbose 1

/run/initialize
/run/beamOn 100000
```

Using `/gun/rock/particle 4`, create real flux.
Neutron spectrum is ascii table, `total_table.dat`.

This generator is written in `source/src/rockParticleGun.cc`.
line 187 - 

Now, Mizukoshi generator is out.
```
    // -- AndleX is the angle from normal line of sphere
    // -- Mizukoshi generator
    // -- Cos weighted generator
    // -- cumulative distribution function of cos
    //
    //G4double angleX = asin(2*RandFlat::shoot(0.0,1.0)-1.0);
    
    // -- Taisyaku generator
    G4double angleX = RandFlat::shoot(0.0,pi);

```
