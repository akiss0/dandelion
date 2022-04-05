/***************************
 * ----------------------------------------------------------------------
 * Dandelion pappus morphing is actuated by radially patterned material swelling
 * ----------------------------------------------------------------------
 * 
 * FreeFem++ simulation scripte used in the following publication :
 * 
 * Madeleine Seale, Annamaria Kiss, Simone Bovio, Ignazio Maria Viola, Enrico
 * Mastropaolo, Arezki Boudaoud, Naomi Nakayama, 
 * "Dandelion pappus morphing is actuated by radially patterned material swelling",
 * doi: https://doi.org/10.1101/2021.08.23.457337
 * 
 * Author :
 * Annamaria Kiss 
 * (annamaria.kiss@ens-lyon.fr, Laboratoire RDP, ENS Lyon)
 * 
 * ***************************/

include "getARGV.idp"

// reading script arguments
for (int i=0;i<ARGV.n;++i)
{ cout << ARGV[i] << " ";}
cout<<endl;

/***************************
*      GLOSSARY
*   nectary = floral podium
*   mesophyl = cortex
/****************************/

/*************************************************************
 *                  PARAMETERS
 * **********************************************************/

string output = getARGV("-out", ".");

// ---------------- geometrical parameters ----------------

// (lengths are measured in micrometers)
real units=200;

// actuator dimensions
real lx=getARGV("-D", 491.0)/units;       //sd =34.4
real ly=getARGV("-H", 240.0)/units;      //sd=36.0

// floral podium
real hnect = getARGV("-Hpod", 38.8)/units;   //sd=9.6
real Rmeasured=getARGV("-R", 363.0)/units;    //sd=49.4
real R=Rmeasured-hnect;

// side
real hside=getARGV("-Hside", 91.4)/units;     //12.6
real lside=getARGV("-Wside", 47.6)/units;     //6.6

// vasculature
real vthickness=getARGV("-Wvasculature", 34.3)/units;//5.5
real cwidth=getARGV("-Dcavity", 74.8)/units;    //15.2

// vasculature displacement (from vascular bundle distance)
real vd=getARGV("-dvasc", 15.3)/units; //15.3*0.22
real vposition=lx/2-vthickness-hnect/ly*(lx/2-cwidth/2-vthickness);

// mesh parameters
int nvertex=40;
cout << "nvertex="<<nvertex<<endl;

// ---------------- Material properties ----------------

// Poisson's ratio
real nu = 0.29;

// Young modulus
real Ev;   // vasculature Young modulus
real fEm; // cortex Em/Ev 
real fEn;  // floral podium En/Ev 
real fEs;  // side     Es/Ev 
	
// measured values for the density (Mean, SD)
real dm=0.668060839; //sd=0.04091249
real dn=1.01896008; //sd=0.015464575
real ds=0.918032482; //sd=0.075097509
real dv=0.882171532; //sd=0.066651037

// Young modulus is linked to measured densities
Ev=1;   // vasculature Young modulus
fEm=dm/dv; // cortex Em/Ev 
fEn=dn/dv;  // floral podium  En/Ev 
fEs=ds/dv;  // side     Es/Ev 

// -----   swelling ability of each region is a parameter
real ani = getARGV("-ani", 1.);// anisotropy of swelling property
real sm = -getARGV("-scort", 0.464888);// cortex swelling property
real sn = -getARGV("-spod", 0.443697);// floral podium swelling property
real ss = -getARGV("-sside", 0.573482);// side swelling property
real sv = -getARGV("-svasc", 0.236087);// vasculature swelling property


/*************************************************************
 *                  GEOMETRY and MESH
 * **********************************************************/

func real lineD(real xA, real xB, real yA, real yB)
{	return (yB-yA)/(xB-xA);
}

func real lineC(real xA, real xB, real yA, real yB)
{	return (yA*xB-yB*xA)/(xB-xA);
}

func real angleToVertical(real Mx, real My, real Nx, real Ny)
{ /*  Computes the sinus of angle between the MN vector and Oy   */
	return asin((Nx-Mx)/sqrt((Mx-Nx)^2+(My-Ny)^2))*180/pi;
}

// ----------------- External boundary/ -----------------

real rnect=lx/2-vthickness;
real tB=2*pi-acos(rnect/R);
real tA=pi+acos(rnect/R);
real xC=0;
real yC=sqrt(R*R-rnect*rnect);

// top
border a1(t=0,1){x=lx/2+t*(lx/2-vthickness-lx/2);y=0;label=11;};
border a2(t=tB,tA){x=xC+R*cos(t);y=yC+R*sin(t);label=12;};
border a3(t=0,1){x=-lx/2+vthickness+t*(-lx/2-(-lx/2+vthickness));y=0;label=13;};
// left
border b1(t=0,1){x=-lx/2;y=t*(-ly);label=2;};
// bottom
border c1(t=0,1){x=-lx/2+t*(-cwidth/2-vthickness+lx/2);y=-ly;label=31;};
border c2(t=0,1){x=-cwidth/2-vthickness+t*vthickness;y=-ly;label=32;};
border c3(t=0,1){x=cwidth/2+t*vthickness;y=-ly;label=33;};
border c4(t=0,1){x=cwidth/2+vthickness+t*(lx/2-cwidth/2-vthickness);y=-ly;label=34;};
// right
border d1(t=0,1){x=lx/2;y=-ly+t*(ly);label=4;};

// -------------------- Internal boundary/ -----------------

real xA=-rnect; real yA=0;
real xB=-cwidth/2; real yB=-ly;
real D=lineD(xA, xB, yA, yB);
real C=lineC(xA, xB, yA, yB);
real delta=D^2*(C-yC)^2-(1+D^2)*((C-yC)^2-(R+hnect)^2);
real xM=(-D*(C-yC)+sqrt(delta))/(D^2+1);
real yM=D*xM+C;
real tN=2*pi+asin(-sqrt((R+hnect)^2-xM^2)/(R+hnect));
real tM=3*pi-tN;

// hole
border vide1(t=0,1){x=-cwidth/2+t*(xM+cwidth/2);y=-ly+t*(yM+ly);label=51;};
border vide2(t=tM,tN){x=xC+(R+hnect)*cos(t);y=yC+(R+hnect)*sin(t);label=52;};
border vide3(t=0,1){x=-xM+t*(cwidth/2+xM);y=yM+t*(-ly-yM);label=53;};

// ------------------- Define the mesh -------------------

mesh Th = buildmesh (a1(nvertex*vthickness)+a2(nvertex*2*rnect)+a3(nvertex*vthickness) // top
                     + b1(nvertex*ly) + d1(nvertex*ly) // sides
                     + c1(nvertex*lx/2) + c2(nvertex*vthickness) // left bottom
                     + vide1(nvertex*ly) + vide2(nvertex*(lx-2*vthickness)) + vide3(nvertex*ly)  //hole
                     + c3(nvertex*vthickness) + c4(nvertex*lx/2)  // right bottom
                     );

/*************************************************************
 *                  DEFINITION OF the REGIONS
 * **********************************************************/

real xA1=-(vposition+vthickness), yA1=-hnect;
real xB1=-cwidth/2-vthickness, yB1=-ly;
real xA2=(vposition+vthickness), yA2=-hnect;
real xB2=cwidth/2+vthickness, yB2=-ly;
real D1=lineD(xA1, xB1, yA1, yB1);
real C1=lineC(xA1, xB1, yA1, yB1);
real D2=lineD(xA2, xB2, yA2, yB2);
real C2=lineC(xA2, xB2, yA2, yB2);

func bool vasculatureBool(real xx, real yy)
{	return (((yy>D1*xx+C1) && (yy<D1*(xx-vthickness)+C1)) || ((yy>D2*xx+C2)&& (yy<D2*(xx+vthickness)+C2)) );
}

func bool nectaryBool(real xx, real yy)
{	return (yy>D1*(xx-vthickness)+C1)&&(yy>D2*(xx+vthickness)+C2);
}

func bool sideBool(real xx, real yy)
{	return   (yy>-hside) && (((xx<-lx/2+lside)&&(yy<D1*xx+C1)) || ( (xx>lx/2-lside)&& (yy<D2*xx+C2))  );
}

func bool mesophylBool(real xx, real yy)
{	return (!vasculatureBool(xx,yy)) && (!nectaryBool(xx,yy)) && (!sideBool(xx,yy));
}


/*************************************************************
 *                  DEFINE THE FINITE ELEMENT SPACE
 * **********************************************************/

fespace Vh(Th,[P2,P2]);  // vector on the mesh (displacement vector)
Vh [u1,u2], [v1,v2];

fespace Sh(Th, P2);   // scalar on the mesh, P2 elements
fespace Sh0(Th,P0);   // scalar on the mesh, P0 elements
fespace Sh1(Th,P1);   // scalar on the mesh, P1 elements

Sh0 strain, stress;

// bounding box for the plot (use the same for all images so that they can be superposed)
func bb=[[-lx/2*1.5,-ly*1],[lx/2*1.5,ly*.1]];
//real coef=1.;
//cout << "Coefficent of amplification:"<<coef<<endl;
plot(Th, ps=output+"/mesh-original.eps", bb=bb, wait=1);

// macro to redefine variables on the displaced mesh 
macro redefineVariable(vvv)
{	real[int] temp(vvv[].n);
	temp=vvv[]; vvv=0; vvv[]=temp;
	vvv=vvv;
}//


real sqrt2=sqrt(2.);
macro epsilon(u1,u2)  [dx(u1),dy(u2),(dy(u1)+dx(u2))/sqrt2] // EOM
//the sqrt2 is because we want: epsilon(u1,u2)'* epsilon(v1,v2) $==  \epsilon(\bm{u}): \epsilon(\bm{v})$
macro div(u1,u2) ( dx(u1)+dy(u2) ) // EOM

/*************************************************************
 *                 SPATIAL DEPENDENCE OF MATERIAL PROPERTIES
 * **********************************************************/

// define region geometry as a finite element field

//string mutname="mnsv";
func vasculature=int(vasculatureBool(x,y));
func nectary=int(nectaryBool(x,y));
func side=int(sideBool(x,y));
func mesophyl=int(mesophylBool(x,y));

func geometry = 1*vasculature + 3*nectary + 2*side + 4*mesophyl;

// definition of FE variables for the structural domains
Sh0 vasculatureh=vasculature;
Sh0 nectaryh=nectary;
Sh0 sideh=side;
Sh0 mesophylh=mesophyl;

Sh0 geometryh=geometry;
string fname=output+"/geometry-original.eps";
plot(geometryh,fill=1, ps=fname, bb=bb, wait=1 );


// spatial dependence of Young modulus
func E=Ev*(vasculature + fEn*nectary + fEs*side + fEm*mesophyl);
Sh0 Eh=E;

// spatial dependence of the swelling property
func s=sv*vasculature + sn*nectary + ss*side + sm*mesophyl;
Sh0 sh=s;

// spatial dependence of the anisotropy of the swelling property
Sh0 anih=ani;

func mu=E/(2*(1+nu));
func lambda=E*nu/((1+nu)*(1-2*nu));

/*************************************************************
 *                  SOLVING THE FEM
 * **********************************************************/

solve Lame([u1,u2],[v1,v2])=
  int2d(Th)(
	    lambda*div(u1,u2)*div(v1,v2) 	
	    + 2.*mu*( epsilon(u1,u2)'*epsilon(v1,v2) ) 
	      )
  - int2d(Th) ( sh/(1.+anih)*((2.*mu+lambda)*dx(v1)+lambda*dy(v2)) )
  - int2d(Th) ( ani*sh/(1.+anih)*(lambda*dx(v1)+(2.*mu+lambda)*dy(v2)) )
+ on(32,u1=vd,u2=0) + on(33,u1=-vd,u2=0) 
  ;


/*************************************************************
 *                  RESULTS
 * **********************************************************/

// compute original region volumes
real voltotal0=int2d(Th)(1);
real volvasculature0=int2d(Th)(vasculatureh);
real volnectary0=int2d(Th)(nectaryh);
real volmesophyl0=int2d(Th)(mesophylh);
real volside0=int2d(Th)(sideh);


// move the mesh and plot the deformed mesh
mesh Th0=Th;
Th=movemesh(Th,[x+u1,y+u2]);

plot(Th, Th0,  ps=output+"/mesh-original+deformed-superposed.eps",bb=bb, wait=1);
plot(Th,  ps=output+"/mesh-deformed.eps",bb=bb, wait=1);

redefineVariable(geometryh);
plot(geometryh, fill=1, ps=output+"/geometry-deformed.eps",bb=bb, wait=1);

// compute deformed region volumes
redefineVariable(vasculatureh);
redefineVariable(nectaryh);
redefineVariable(sideh);
redefineVariable(mesophylh);

real voltotal=int2d(Th)(1);
real volvasculature=int2d(Th)(vasculatureh);
real volnectary=int2d(Th)(nectaryh);
real volside=int2d(Th)(sideh);
real volmesophyl=int2d(Th)(mesophylh);

// compute areachanges
real am=volmesophyl0/volmesophyl;
real an=volnectary0/volnectary;
real as=volside0/volside;
real av=volvasculature0/volvasculature;

// compute the generated side angle
real height=hside;
real Nx=lx/2+u1(lx/2.,0), Ny=u2(lx/2.,0);
real Mx=lx/2+u1(lx/2.,-height), My=-height+u2(lx/2.,-height);
real sideangle=angleToVertical(Mx, My, Nx, Ny);

/*************************************************************
 *        PRINT RESULTS
 * **********************************************************/
cout<<"----------------------"<<endl;
cout<<"Areachanges (Awet/Adry) :"<<endl;
cout<<"----------------------"<<endl;
cout<<"cortex -> "<<am<<endl;
cout<<"floral podium -> "<<an<<endl;
cout<<"side -> "<<as<<endl;
cout<<"vasculature -> "<<av<<endl;
cout<<"----------------------"<<endl;
cout<<"Generated side angle = "<<sideangle<<" degrees"<<endl;
cout<<"----------------------"<<endl;
