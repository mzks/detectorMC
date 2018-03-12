#! /bin/csh -f
./rock rock.mac
root -q -l -b FillTree.C 
root -q -l -b FillTreeE.C 

root -l Plot.C
#root -l CalcSagitta.C


