----------------------------------------------------------------------
			        - dandelion -
    Finite element method simulations for dandelion using FreeFem++
----------------------------------------------------------------------

Author :
Annamaria Kiss <annamaria.kiss@ens-lyon.fr.fr>
(Laboratoire Reproduction et Développement des Plantes, Univ Lyon, ENS de Lyon, UCB Lyon 1, CNRS, INRAE, F-69342, Lyon, France)
----------------------------------------------------------------------

FreeFem++ simulation scripte used in the following publication :
Madeleine Seale, Annamaria Kiss, Simone Bovio, Ignazio Maria Viola, Enrico
Mastropaolo, Arezki Boudaoud, Naomi Nakayama, "Dandelion pappus morphing is actuated by radially patterned material swelling", doi: https://doi.org/10.1101/2021.08.23.457337
----------------------------------------------------------------------

Dependency
--------
The scripte is interpreted and executed by the FreeFem++ software:
https://freefem.org/

Usage
-----
FreeFem++ dandelion.cpp [-param value]

If no option is given, the reference model is simulated, namely all parametervalues are chosen to have their reference values. Parameter values can be specified by using the parameter's name as option. Accepted options are the following (see Table 1 and Table 2 of the publication for parameter description and reference values).
- geometrical parameters: D, H, Hpod, R, Hside, Wside, Wvasculature, Dcavity
- vasculature displacement: dvasc
- swelling factors: scort, spod, sside, svasc


Example 1 : the reference model
================================
FreeFemm++ dandelion.cpp

nvertex=40
  --  mesh:  Nb of Triangles =   8774, Nb of Vertices 4629
  -- Solve : 
          min -0.292037  max 0.292132
----------------------
Areachanges (Awet/Adry) :
----------------------
cortex -> 1.67524
floral podium -> 1.61194
side -> 1.79592
vasculature -> 1.2898
----------------------
Generated side angle = 19.5215 degrees
----------------------
times: compile 0.008144s, execution 9.69662s,  mpirank:0
 CodeAlloc : nb ptr  5686,  size :562720 mpirank: 0
Ok: Normal End

Example 2 : higher swelling abilities for the cortex generates higher side angle
================================
FreeFem++ dandelion.cpp -scort 0.7


nvertex=40
  --  mesh:  Nb of Triangles =   8774, Nb of Vertices 4629
  -- Solve : 
          min -0.404528  max 0.404761
----------------------
Areachanges (Awet/Adry) :
----------------------
cortex -> 2.21836
floral podium -> 1.54942
side -> 1.54601
vasculature -> 1.25095
----------------------
Generated side angle = 31.9336 degrees
----------------------
times: compile 0.007776s, execution 10.0292s,  mpirank:0
 CodeAlloc : nb ptr  5686,  size :562720 mpirank: 0
Ok: Normal End

