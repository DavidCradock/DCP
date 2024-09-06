# DCP

DCP is an abbreviation for <b>D</b>ave's <b>C</b>ode <b>P</b>aradise.

DCP is a collection of dynamic libraries, static libraries and executable projects.

DCP has a solution file for Visual Studio, found in the root directory called "DCP.sln", which contains all the projects, used to build everything, including the Doxygen documentation.

The main static library is called "DavesCodeLibrary" or DCL for short.

The executables are used to develop DCL, show examples of how to use it and test various parts out to make sure they're working as expected. Some are also custom created tools such as font file generation.

DCL is a collection of code which includes (or will do) features such as...
- Opening a window.
- Access to input devices such as keyboard, mouse and various joysticks.
- AI, including neural networks, finite state machines and steering/flocking.
- Audio playback and maybe recording with various effects such as reverb, delay etc.
- Graphics rendering using either OpenGL, Software based or Vulkan.
- Image handling (loading/saving/manipulation with filters etc)
- Mathematics for vectors, matricies, planes, quaternions etc
- Networking, both TCP and UDP
- Physics, probably using other people's physics engines such as Box2D and Bullet and then later, my own rigid/soft body simulation.
- Spatial partitioning for both 2D (Quad tree) and 3D (Oct tree)

DCL is being created to allow me to create all kinds of cool stuff such as 2D and 3D hardware accelerated games and applications.

To view more information, please download the project and goto /Output/Documentation/html/index.html to view the Doxygen generated documentation for the whole project, thanks!