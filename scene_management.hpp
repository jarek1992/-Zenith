#pragma once

//basic types and material library
#include "common.hpp"
#include "material_library.hpp"

//geometry (shapes)
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "cube.hpp"
#include "triangle.hpp"
#include "model.hpp"
#include "constant_medium.hpp" //fog

//transformation and instances
#include "material_instance.hpp"
#include "translate.hpp"
#include "rotate_x.hpp"
#include "rotate_y.hpp"
#include "rotate_z.hpp"
#include "scale.hpp"

//headers
#include <memory>
#include <vector>
#include <string>

//struct to hold loaded .obj models assets for the scene
struct sceneAssetsLoader {
	shared_ptr<model> teapot;
	shared_ptr<model> torus;
	shared_ptr<model> bowl;
	shared_ptr<model> cylinder;
	shared_ptr<model> pyramid;
	shared_ptr<model> torus_knot;

	sceneAssetsLoader() {
		teapot = make_shared<model>("assets/models/teapot.obj", nullptr, 0.4);
		torus = make_shared<model>("assets/models/torus.obj", nullptr, 0.4);
		bowl = make_shared<model>("assets/models/bowl.obj", nullptr, 0.02);
		cylinder = make_shared<model>("assets/models/cylinder.obj", nullptr, 0.4);
		pyramid = make_shared<model>("assets/models/pyramid.obj", nullptr, 0.4);
		torus_knot = make_shared<model>("assets/models/torus_knot.obj", nullptr, 0.4);
		//add more .obj models here...
	}
};

//loading materials
void load_materials(MaterialLibrary& mat_lib) {
	//bump map textures
	auto wood_bump = make_shared<image_texture>("assets/bump_maps/wood_bump_map.jpg");
	auto scratches_bump = make_shared<image_texture>("assets/bump_maps/scratches_bump_map.jpg");
	auto concrete_bump = make_shared<image_texture>("assets/bump_maps/concrete_bump_map.jpg");
	auto water_bump = make_shared<image_texture>("assets/bump_maps/water_bump_map.jpg");

	//add some predefined materials to the library
	mat_lib.add("water", make_shared<dielectric>(1.33, water_bump, 0.8));
	mat_lib.add("turquoise_water", make_shared<dielectric>(1.33, color(0.85, 1.0, 0.98), water_bump, 2.0));
	mat_lib.add("red_diffuse", make_shared<lambertian>(color(0.8, 0.1, 0.1)));
	mat_lib.add("white_diffuse", make_shared<lambertian>(color(1.0, 1.0, 1.0)));
	mat_lib.add("copper", make_shared<metal>(color(0.95, 0.64, 0.54), 0.0));
	mat_lib.add("rough_copper", make_shared<metal>(color(0.89, 0.58, 0.51), 0.2));
	mat_lib.add("rough_gold", make_shared<metal>(color(1.0, 0.84, 0.0), 0.15));
	mat_lib.add("light_blue_diffuse", make_shared<lambertian>(color(0.1, 0.4, 0.9)));
	mat_lib.add("white_diffuse", make_shared<lambertian>(color(0.9, 0.9, 0.9)));
	mat_lib.add("wood_texture", make_shared<lambertian>(make_shared<image_texture>("assets/textures/fine-wood.jpg")));
	mat_lib.add("wood_bumpy_texture", make_shared<lambertian>(make_shared<image_texture>("assets/textures/fine-wood.jpg"), wood_bump, 8.0));
	mat_lib.add("gold_mat", make_shared<metal>(color(1.0, 0.8, 0.4), 0.0));
	mat_lib.add("scratched_gold_mat", make_shared<metal>(color(1.0, 0.8, 0.4), 0.0, scratches_bump, -1.0));
	mat_lib.add("mirror", make_shared<metal>(color(1.0, 1.0, 1.0), 0.0));
	mat_lib.add("scratched_mirror", make_shared<metal>(color(1.0, 1.0, 1.0), 0.0, scratches_bump, 1.0));
	mat_lib.add("brushed_aluminium", make_shared<metal>(color(1.0, 1.0, 1.0), 0.25));

	mat_lib.add("metal_colored1", make_shared<metal>(color(random_double(0, 1), random_double(0, 1), random_double(0, 1)), 0.53));
	mat_lib.add("metal_colored2", make_shared<metal>(color(random_double(0, 1), random_double(0, 1), random_double(0, 1)), 0.05));
	mat_lib.add("metal_colored3", make_shared<metal>(color(random_double(0, 1), random_double(0, 1), random_double(0, 1)), 0.15));
	mat_lib.add("metal_colored4", make_shared<metal>(color(random_double(0, 1), random_double(0,1), random_double(0, 1)), 0.75));

	mat_lib.add("white_metal", make_shared<metal>(color(1.0, 1.0, 1.0), 0.99));
	mat_lib.add("white_metal_bump", make_shared<metal>(color(0.9, 0.9, 0.9), 0.6, concrete_bump, 2.0));
	mat_lib.add("checker_texture", make_shared<lambertian>(make_shared<checker_texture>(0.5, color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9))));
	mat_lib.add("glass_bubble", make_shared<dielectric>(1.0 / 1.5));
	mat_lib.add("glass", make_shared<dielectric>(1.5));
	mat_lib.add("foggy_glass", make_shared<dielectric>(1.5, concrete_bump, 0.02));
	mat_lib.add("pure_mirror", make_shared<metal>(color(1.0, 1.0, 1.0), 0.0));
	mat_lib.add("random_diffuse", make_shared<lambertian>(color::random() * color::random()));
	mat_lib.add("random_neon_light", make_shared<diffuse_light>(color::random(0.1, 1.0) * 1.5));
	mat_lib.add("neon_pink", make_shared<diffuse_light>(color(1.0, 0.0, 0.5) * 6.0));
	mat_lib.add("neon_blue", make_shared<diffuse_light>(color(0.0, 0.5, 1.0) * 6.0));
	mat_lib.add("neon_green", make_shared<diffuse_light>(color(0.1, 1.0, 0.1) * 6.0));
	mat_lib.add("neon_yellow", make_shared<diffuse_light>(color(1.0, 0.8, 0.0) * 6.0));
	mat_lib.add("neon_white", make_shared<diffuse_light>(color(1.0, 1.0, 1.0) * 6.0));
	mat_lib.add("neon_red", make_shared<diffuse_light>(color(1.0, 0.1, 0.1) * 6.0));
	mat_lib.add("ceiling_emissive", make_shared<diffuse_light>(color(1.0, 0.0, 0.5) * 10.0));
	//... add more materials as needed

	//floor checker material 
	auto checker = make_shared<checker_texture>(0.5, color(0.1, 0.1, 0.1), color(0.9, 0.9, 0.9));
	mat_lib.add("reflective_checker_mat", make_shared<metal>(checker, 0.02));
}

//build scene geometry
hittable_list build_geometry(MaterialLibrary& mat_lib, const sceneAssetsLoader& assets, bool use_fog, double fog_density, color fog_color) {
	//global material library
	hittable_list world;

	// - 1. FLOOR -
	auto ground_geom = make_shared<sphere>(point3(0.0, -1000.0, 0.0), 1000.0, nullptr);
	world.add(make_shared<material_instance>(ground_geom, mat_lib.get("reflective_checker_mat")));

	//auto floor_cube = make_shared<cube>(point3(-8.0, -0.01, -8.0), point3(8.0, 0.01, 8.0), nullptr);
	//world.add(make_shared<material_instance>(floor_cube, mat_lib.get("scratched_gold_mat")));

	//// - 2. free standing geometries (in the middle)
	////torus
	//auto torus_instance = make_shared<material_instance>(assets.torus, mat_lib.get("white_diffuse"));
	//auto torus_final = make_shared<translate>(torus_instance, point3(0.0, 0.0, 0.0));
	//world.add(torus_final);

	////cylinder
	//auto cylinderl_instance = make_shared<material_instance>(assets.cylinder, mat_lib.get("scratched_mirror"));
	//auto cylinder_final = make_shared<translate>(cylinderl_instance, point3(0.0, 0.0, -1.5));
	//world.add(cylinder_final);

	////pyramid
	//auto pyramid_instance = make_shared<material_instance>(assets.pyramid, mat_lib.get("rough_copper"));
	//auto pyramid_scaled = make_shared<scale>(pyramid_instance, vec3(1.5, 1.5, 1.5));
	//auto pyramid_final = make_shared<translate>(pyramid_scaled, point3(2.0, 0.0, 1.0));
	//world.add(pyramid_final);

	////torus knot	
	//auto torus_knot_instance = make_shared<material_instance>(assets.torus_knot, mat_lib.get("white_diffuse"));
	//auto torus_knot_final = make_shared<translate>(torus_knot_instance, point3(1.0, 0.0, 2.0));
	//world.add(torus_knot_final);

	//bowl
	auto bowl_instance = make_shared<material_instance>(assets.bowl, mat_lib.get("wood_texture"));
	auto bowl_rotated = make_shared<rotate_x>(bowl_instance, -90.0);
	auto bowl_final = make_shared<translate>(bowl_rotated, point3(0.2, 0.4, 0.0));
	world.add(bowl_final);

	////teapot
	//auto teapot_inst = make_shared<material_instance>(assets.teapot, mat_lib.get("white_metal"));
	//auto rot_teapot_x = make_shared<rotate_x>(teapot_inst, -90.0);
	//auto rot_teapot_y = make_shared<rotate_y>(rot_teapot_x, 30.0);
	//auto teapot_scaled = make_shared<scale>(rot_teapot_y, vec3(0.8, 0.8, 0.8));
	//auto teapot_final = make_shared<translate>(teapot_scaled, point3(-1.0, 0.9, 0.0));
	//world.add(teapot_final);

	//sphere
	auto big_sphere_geom = make_shared<sphere>(point3(0.0, 0.0, 0.0), 1.0, nullptr);
	auto random_col = color(random_double(0, 1), random_double(0, 1), random_double(0, 1));

	auto sphere_instance1 = make_shared<material_instance>(big_sphere_geom, mat_lib.get("metal_colored1"));
	auto sphere_scaled1 = make_shared<scale>(sphere_instance1, vec3(0.3, 0.3, 0.3));
	auto sphere_instance2 = make_shared<material_instance>(big_sphere_geom, mat_lib.get("metal_colored2"));
	auto sphere_scaled2 = make_shared<scale>(sphere_instance2, vec3(0.3, 0.3, 0.3));
	auto sphere_instance3 = make_shared<material_instance>(big_sphere_geom, mat_lib.get("metal_colored3"));
	auto sphere_scaled3 = make_shared<scale>(sphere_instance3, vec3(0.3, 0.3, 0.3));
	auto sphere_instance4 = make_shared<material_instance>(big_sphere_geom, mat_lib.get("metal_colored4"));
	auto sphere_scaled4 = make_shared<scale>(sphere_instance4, vec3(0.3, 0.3, 0.3));

	auto sphere_final1 = make_shared<translate>(sphere_scaled1, point3(0.0, 0.5, -0.5));
	auto sphere_final2 = make_shared<translate>(sphere_scaled2, point3(0.0, 0.5, -1.0));
	auto sphere_final3 = make_shared<translate>(sphere_scaled3, point3(0.5, 0.5, -0.75));
	auto sphere_final4 = make_shared<translate>(sphere_scaled4, point3(0.25, 1.0, -0.75));

	world.add(sphere_final1);
	world.add(sphere_final2);
	world.add(sphere_final3);
	world.add(sphere_final4);

	////cube
	//auto big_cube_geom = make_shared<cube>(point3(0.0, 0.0, 0.0), nullptr);
	//auto big_cube_instance1 = make_shared<material_instance>(big_cube_geom, mat_lib.get("white_metal"));
	//auto big_cube_instance2 = make_shared<material_instance>(big_cube_geom, mat_lib.get("mirror"));
	//
	//world.add(make_shared<translate>(big_cube_instance1, point3(0.0, 1.0, 3.0)));
	//world.add(make_shared<translate>(big_cube_instance2, point3(0.0, 1.0, -3.0)));

	
	//auto sphere_diffuse = make_shared<material_instance>(big_sphere_geom, mat_lib.get("white_diffuse"));
	//auto sphere_metal_bumpy = make_shared<material_instance>(big_sphere_geom, mat_lib.get("scratched_gold_mat"));
	//auto sphere_glass = make_shared<material_instance>(big_sphere_geom, mat_lib.get("glass"));
	//auto sphere_emissive = make_shared<material_instance>(big_sphere_geom, mat_lib.get("neon_red"));

	//world.add(make_shared<translate>(sphere_diffuse, point3(0.0, 1.0, 4.5)));
	//world.add(make_shared<translate>(sphere_metal_bumpy, point3(0.0, 1.0, 2.0)));
	//world.add(make_shared<translate>(sphere_glass, point3(0.0, 1.0, -0.5)));
	//world.add(make_shared<translate>(sphere_emissive, point3(0.0, 1.0, -3.0)));

	//// - 3. RANDOM SPREADED GEOMETRIES
	//// 
	////master geometries (local prefabicats)
	//auto master_cube = make_shared<cube>(point3(-0.2, -0.2, -0.2), point3(0.2, 0.2, 0.2), nullptr);
	//auto master_sphere = make_shared<sphere>(point3(0.0, 0.0, 0.0), 0.2, nullptr);
	////material filters
	//auto regular_mats = mat_lib.get_regular_names();
	////for loop to randomize location of small cubes and spheres*/
	//for (int a = -15; a < 15; a++) {
	//	for (int b = -15; b < 15; b++) { //create the grid a(-15, 15) / b(-15, 15)
	//		point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()); //point3(x,(y = const),z)

	//		if ((center - point3(4.0, 0.2, 0.0)).length() > 0.9) {
	//			std::string selected_mat_name;
	//			shared_ptr<hittable> geometry;
	//			//scale
	//			vec3 scale_v(1.0, 1.0, 1.0); //default scale
	//			//select random number 0.0 - 1.0
	//			double dice_roll = random_double();

	//			//1. Probability distribution
	//			if (dice_roll < 0.15) {
	//				//25% chance to draw white diffuse
	//				selected_mat_name = "random_diffuse";
	//				
	//				if (random_double() < 0.5) {
	//					geometry = master_sphere;
	//				} else {
	//					geometry = master_cube;
	//				}
	//			} else if (dice_roll < 0.45) {
	//				//30% chance to draw glass material(0.15 + 0.30 = 0.45)
	//				selected_mat_name = (random_double() < 0.7) ? "glass" : "glass_bubble";
	//				geometry = master_sphere;
	//				double s = random_double(0.9, 1.0);
	//				scale_v = vec3(s, s, s);
	//			} else {
	//				//55% left draw random material left materials from the list (excluding emissive/neaons using regular_mats)
	//				int random_idx = random_int(0, static_cast<int>(regular_mats.size()) - 1);
	//				selected_mat_name = regular_mats[random_idx];

	//				if (random_double() < 0.5) {
	//					geometry = master_sphere;
	//				} else {
	//					geometry = master_cube;
	//				}

	//				//scale to difference
	//				double s = random_double(0.9, 1.0);
	//				scale_v = vec3(s, s, s);
	//			}

	//			//2. get material
	//			auto obj_mat = mat_lib.get(selected_mat_name);

	//			//3. scale
	//			auto scaled_obj = make_shared<scale>(geometry, scale_v);

	//			//4. rotation (only cubes)
	//			shared_ptr<hittable> rotated_obj = scaled_obj;
	//			if (geometry == master_cube) {
	//				rotated_obj = make_shared<rotate_y>(scaled_obj, random_double(0.0, 90.0));
	//			}

	//			//5. applying material to the instance through material_instance class
	//			auto instance = make_shared<material_instance>(rotated_obj, obj_mat);

	//			//6. final position translation
	//			world.add(make_shared<translate>(instance, center));
	//		}
	//	}
	//}

	// - 4. LIGHT PLANE 
	/*auto light_geom = make_shared<cube>(point3(-0.2, -0.2, -0.2), point3(0.2, 0.2, 0.2), nullptr);
	auto light_instance = make_shared<material_instance>(light_geom, mat_lib.get("ceiling_emissive"));
	world.add(make_shared<translate>(light_instance, point3(0.0, 15.0, 0.0)));*/

	// - 5. environmental fog
	if (use_fog) {
		//set radius and center of the fog volume (can be adjusted to fit the scene better)
		auto fog_boundary = make_shared<sphere>(point3(0.0, 0.0, 0.0), 50.0, nullptr);
		//fog density 0.1 is extremely high (impenetrable wall). 
		//values 0.001 - 0.02 gives best visual results.
		world.add(make_shared<constant_medium>(fog_boundary, fog_density, fog_color));
	}
	return world;
}