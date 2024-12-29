/* $XConsortium: man.c,v 1.6 94/04/17 20:45:28 dave Exp $ */
char *man[]={"\
\n\
\n\
\n\
XGAS(1)                  USER COMMANDS                    XGAS(1)\n\
\n\
\n\
\n\
NAME\n\
     xgas - animated simulation of an ideal gas\n\
\n\
SYNOPSIS\n\
     xgas [-option ...]\n\
\n\
DESCRIPTION\n\
     xgas is a physical simulation of an ideal gas  in  a  heated\n\
     box.   Gas  molecules  move  around  the box with velocities\n\
     dependent on their temperature.  A chamber consisting of two\n\
     boxes  contains  the  gas molecules; the temperature of each\n\
     box can be independently controlled by  a  scrollbar.   When\n\
     gas  molecules  collide  with  the  walls, their temperature\n\
     approaches that of the box.\n\
\n\
     Use mouse button 1 to create molecules one at a time at  the\n\
     cursor  position.   Use mouse button 2 to create the maximum\n\
     number of molecules at the cursor position.\n\
\n\
OPTIONS\n\
     This is a toolkit program;\n\
             all the usual toolkit options are available.\n\
\n\
     -as     Sets the autoStart resource.\n\
\n\
     -ts     Sets the timeStepSize resource.\n\
\n\
     -d      Sets the delay resource.\n\
\n\
     -rb     Sets the randomBounce resource.\n\
\n\
     -eq     Sets the equilibrium resource.\n\
\n\
     -mm     Sets the maxMolecules resource.\n\
\n\
     -fg     Sets the foreground.\n\
\n\
     -bg     Sets the background.\n\
\n\
RESOURCES\n\
     The xgas program uses the following X resources:\n\
\n\
     autoStart\n\
             Starts  the  simulation  automatically.   Good   for\n\
             canned demos.\n\
\n\
     timeStepSize\n\
             Specifies   the   simulated   time    duration    in\n\
             microseconds for each cycle of computation.\n\
\n\
     delay   Specifies the real time  interval  between  timestep\n\
             computations.\n\
\n\
     randomBounce\n\
             In each wall collision, a molecule  bounces  elasti-\n\
             cally (angle of incidence = angle of reflection).  A\n\
             component of randomness  is  added  to  this  angle.\n\
             RandomBounce  varies from 0.0 (no randomness) to 1.0\n\
             (completely random angle of incidence).\n\
\n\
",
"\
     equilibrium\n\
             During each wall  collision,  a  molecule's  kinetic\n\
             energy approaches that corresponding to the tempera-\n\
             ture of  the  wall.   If  equilibrium  is  1.0,  the\n\
             molecule  reaches  the wall temperature immediately.\n\
             For  values  between  1.0  and  0.0,  the   molecule\n\
             approaches the temperature of the wall more slowly.\n\
\n\
     maxMolecules\n\
             Specifies the maximum number  of  molecules  in  the\n\
             simulation.\n\
\n\
\n\
\n\
\n\
X Version 11         Last change: Release 5                     1\n\
\n\
\n\
\n\
\n\
\n\
\n\
XGAS(1)                  USER COMMANDS                    XGAS(1)\n\
\n\
\n\
\n\
SEE ALSO\n\
     X(1), xwd(1)\n\
\n\
BUGS\n\
     When the chamber is resized, molecules should be  rearranged\n\
     appropriately.   Instead, the molecule arrays are reinitial-\n\
     ized.\n\
\n\
AUTHOR\n\
     Larry Medwin\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
X Version 11         Last change: Release 5                     2\n\
\n\
\n\
\n\
"};