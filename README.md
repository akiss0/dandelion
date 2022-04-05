# Dandelion pappus morphing

Plants can generate motion by absorbing and releasing water. By investigating the structure and properties of the actuator cell walls we have identified the mechanism by which the dandelion pappus closes and developed a structural computational model that can capture observed pappus closing.

This model was used to explore the contribution of differential material domains in the actuator function and the critical design features in the preprint "Madeleine Seale, Annamaria Kiss, Simone Bovio, Ignazio Maria Viola, Enrico Mastropaolo, Arezki Boudaoud, Naomi Nakayama, Dandelion pappus morphing is actuated by radially patterned material swelling, doi: https://doi.org/10.1101/2021.08.23.457337":https://www.biorxiv.org/content/10.1101/2021.08.23.457337v1

The "dandelion.cpp" FreeFem script implements the model.

## Dependency

The script is interpreted and executed by the FreeFem++ software (was tested on version 4.9): https://freefem.org/

## Usage

<pre>
FreeFem++ dandelion.cpp [-param value]
</pre>

If no option is given, the reference model is simulated, that is all parametervalues are chosen to have their reference values (see Table 1 and Table 2 of the publication for parameter description and reference values).

Other parameter values can be specified by using the parameter's name as option. Accepted options are the following.
- geometrical parameters: D, H, Hpod, R, Hside, Wside, Wvasculature, Dcavity
- vasculature displacement: dvasc
- swelling factors: scort, spod, sside, svasc

## Example 1 : the reference model

<pre>
FreeFem++ dandelion.cpp
</pre>

The simulation generates Figures 5a and 5e of the hydrated and dehydrated actuator tissue structure, the image of the initial mesh, the deformed one, as well as their superposition. It also prints out the areachange for each structural region corresponding to the simulation. These are the areachange values in the "Model output" serie of Figure 5b. The generated side angle value is also printed in degrees.

Finally, the compilation and executaion times are printed.

<pre>
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
</pre>

## Example 2 : higher swelling factor for the cortex generates higher side angle

<pre>
FreeFem++ dandelion.cpp -scort 0.7
</pre>

Here the swelling factor of the cortex region was chosen higher than its reference value, and as a result, the generated side angle comes out higher.

<pre>
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
</pre>
