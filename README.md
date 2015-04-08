MaskRay is a proof-of-concept raytracer.

Features
--------
- path traced global illumination
- kd-tree speed up
- arbitrary BRDF, even BSSRDF

Repository
----------
https://github.com/zxytim/MaskRay

Screenshots
-----------
<!--<img class="screenshots" src="http://static.zxytim.com/cg/0-lambertian.png" alt="A first image with Lambertian surface">-->
<!--<img class="screenshots" src="http://static.zxytim.com/cg/1-reflect-refract-simple-caustic.png" alt="reflect and refract, simple caustic">-->
<!--<img class="screenshots" src="http://static.zxytim.com/cg/3-evident-caustic.png" alt="an evident caustic. small light source causes more noise">-->
<!--<img class="screenshots" src="http://static.zxytim.com/cg/4-humanoid.png" alt="a humanoid mesh">-->
<!--<img class="screenshots" src="http://static.zxytim.com/cg/7-glass-dragon-1280x720.png" alt="glass dragon, rendered with kd-tree">-->
<img class="screenshots" src="examples/dragon-4k.png" alt="glass dragon, rendered with kd-tree">

TODOs
-----
- Depth of Field
- Motion Blur
- SAH-based kd-tree, tweaks, (or VVH-based kd-tree ?)
- more BRDFs
- Metropolis Light Transport
- Photon Map
- MPI implementation
- Grid-computing-like loosely-aggregated rendering cluster
- Hardware acceleration (CUDA)
- Glass broken effect
- Command line interface
- Scene description script spec
- Obj file implementation
- Instancing -- transformation on renderable
