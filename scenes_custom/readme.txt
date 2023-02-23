areaLight and derivatives:
Testing for area light implementation from two different angles, using the provided areaLight scene. _visibility test is pointed directly at the light itself, testing to make sure it's visible.

glazeTest and derivatives:
Testing for glaze and Blinn-Phong mirrored shaders, using the provided glazeTest scene. The point light versions replace the area lights with point lights, in order to test without area lights implemented. The BPM versions change the left sphere's shader to be Blinn-Phong mirrored.

gridOfBunniculas, gridOfBunnies, and derivates:
The Bunnicula scenes use my monster attributes to display 16 instanced bunnies that all have a different combination of depths at which they are visible and depths at which they cast shadows. They are in a mirrored box, with black edges to make it clear where the borders are. The Bunnies scenes remove the monster attributes, _ortho uses an orthographic camera instead of perspective, _nomirror removes the mirrored box, Glaze replaces the Lambertian shaders on the bunnies with glaze shaders, and MaxChaos moves the camera to a different point in the scene to give a different perspective. bunnicula_key.png shows the different visibility/shadow settings for each bunnicula. The first two digits mark the minimum and maximum reflection depth at which the object is visible. The next two mark the min/max depth at which the object casts a shadow.

lotsOfTrianglesGlaze:
The provided lotsOfTriangles scene, but using Glaze shaders instead of Lambertian.

monsterSphereScene:
A modified version of mirrorScene that shows off the monster attributes. The green sphere is a "vampire" - not visible in reflections - and the red sphere is a "Bloody Mary" - visible only in reflections. In 01, they cast shadows only when visible. In 02, they cast shadows only when not visible. _debug displays the scene without any monster attributes.

oneEgg:
Modified from the provided threeEgg scene, this creates three sphere instances, each with only one transformation - one translate, one scale, and one rotate. It is intended for debugging transforms rather than creating an interesting visual.

oneSphere and derivates:
Modified from the provided oneSphere scene. The initial difference is just a change in color. MultiLights tests the outcome of multiple bright white lights on a Lambertian object; MultiColoredLights tests the blending of color resulting from different colored light sources. threeSpheresMultiLight and twoSpheres are similarly derived and intended to test shadows.

PhongExp and derivates:
The same idea as the oneSphere modifications, only with Blinn-Phong shaders.

rowOfBunnys_notex:
The provided rowOfBunnys scene, but without textures and with an additional area light.

spheres_1K_GlazeBPM:
The provided spheres_1K scene, but with all shaders changed to glaze or Blinn-Phong mirrored.