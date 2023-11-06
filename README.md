# MiniRT

**MiniRT** is a C-based mini raytracer that utilizes a minimal graphics library.

A raytracer is a computer graphics technique used to create highly realistic images by simulating the behavior of light in a virtual 3D environment. In ray tracing, the fundamental concept revolves around tracing the path of light rays as they interact with objects and surfaces within a scene.


## 📸 Renders
<table align=center>
	<thead>
		<tr>
			<th colspan=2>Some renders</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><image src="assets/screenshots/suzanne.png"></image></td>
			<td><image src="assets/screenshots/lamborghini.png"></image></td>
		</tr>
		<tr>
			<td><image src="assets/screenshots/xwing.png"></image></td>
			<td><image src="assets/screenshots/earth.png"></image></td>
		</tr>
	</tbody>
</table>

<table align=center>
	<thead>
		<tr>
			<th colspan=2>Integrated post-processing effects</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><image src="assets/screenshots/chess_no_effects.png"></image></td>
			<td><image src="assets/screenshots/chess_black_and_white.png"></image></td>
		</tr>
		<tr>
			<td><image src="assets/screenshots/chess_inverse_color.png"></image></td>
			<td><image src="assets/screenshots/chess_inverse_black_and_white.png"></image></td>
		</tr>
	</tbody>
</table>

<table align=center>
	<thead>
		<tr>
			<th colspan=2>Interactive interface</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><image src="assets/screenshots/interface.png"></image></td>
		</tr>
	</tbody>
</table>

<table align=center>
	<thead>
		<tr>
			<th colspan=2>Bounding Volume Hierarchy Debugger</th>
		</tr>
	</thead>
	<tbody>
        <tr>
			<td><image src="assets/screenshots/bvh.png"></image></td>
        </tr>
	</tbody>
</table>

## 🔨 Build

⚠️ [Needs mlx prerequisites](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#installation)

```
make -j
./miniRT *.rt
```

Run default scene
```
make run
```
Run all renders
```
make render
```


## 🚀 Features

- Basic Geometric Shapes:
  - Sphere
  - Cylinder
  - Cone
  - Plane
- Interactive GUI with Object Manipulation
- Font Rendering from scratch using .ttf files
- Dynamic Camera Control with 3 Axes and Field of View (FOV)
- Multiple Colored Light Management
- Texture Mapping:
  - .ppm files
  - Checkerboard
  - Normal Maps for relief
- Full Phong Lighting Model
- Post-Production Effects:
  - Black & White
  - Color Inversion
- Integrated Screenshot Export
- 3D Mesh Import (.obj)
- Bounding Volume Hierarchy (BVH)
- Bilinear Interpolation for Resolution Adaptation while Maintaining 30 FPS
- Anti-Aliasing for Smooth Rendering
- Multi-Threading Support

## 🕹️ **Controls**

- **W** - Move the camera forward
- **A** - Move the camera left
- **S** - Move the camera backward
- **D** - Move the camera right
- **Q** - Camera peaking left
- **E** - Camera peaking right
- **Right Mouse Button** - Switch between camera and GUI mode
- **Mouse Movement** *[GUI Mode]* - Move object
- **Mouse Movement** *[Camera Mode]* - Adjust camera view direction
- **Mouse Scroll** *[GUI Mode]* - Increase or decrease value
- **Spacebar** - Move the camera up
- **Shift** - Move the camera down
- **H** - Hide the GUI
- **B** - Switch to the next post-processing effect
- **T** - Take screenshot
- **R** - Enable BVH debugger
- **DELETE** - Deselect object
- **COMMAND + S** *[MacOS]* - Save current scene
- **CTRL + S** *[Linux]* - Save current scene
- **Esc** - Exit the program 

## 📚 **Resources**

- [Fonts](https://developer.apple.com/fonts/TrueType-Reference-Manual/)
- [Bézier curves](https://www.youtube.com/watch?v=aVwxzDHniEw&t)
- [The Cherno](https://www.youtube.com/watch?v=gfW1Fhd9u9Q&list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl)
- [Sebastian Lague](https://www.youtube.com/watch?v=Qz0KTGYJtUk)
- [The Book Series](https://raytracing.github.io/)
- [Normal Mapping](https://learnopengl.com/Advanced-Lighting/Normal-Mapping)
- [Normal Mapping2](https://www.youtube.com/watch?v=oOOeV3IU2Yo)
- [Texture Mapping](http://raytracerchallenge.com/bonus/texture-mapping.html)
- [Projective Camera Models](https://pbr-book.org/3ed-2018/Camera_Models/Projective_Camera_Models)
- [How To Build A BVH](https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/)
- [AABB Intersection Algorithm](https://medium.com/@bromanz/another-view-on-the-classic-ray-aabb-intersection-algorithm-for-bvh-traversal-41125138b525)
- [Shading And Lighting](https://cglearn.codelight.eu/pub/computer-graphics/shading-and-lighting#material-lambert-lighting-model-1)
- [Intersection equations](https://physique.cmaisonneuve.qc.ca/svezina/nyc/note_nyc/NYC_CHAP_6_IMPRIMABLE_4.pdf)


## 📝 Authors

- [Vincent Fries](https://github.com/V-Fries) ([**vfries**](https://profile.intra.42.fr/users/vfries))
- [Tom Damerose](https://github.com/tdameros) ([**tdameros**](https://profile.intra.42.fr/users/tdameros))
