/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:44:23 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/27 19:18:43 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include "main.h"
#include "parsing.h"

t_rgb	ambient(t_material m, t_light l);

int get_color_at(t_image img, int x, int y)
{
  return (img.buffer[x + (y * img.res.width)]);
}

t_rgb cb(t_uv uv, int a, int b) {
	const double u = floor(uv.u * a);
	const double v = floor(uv.v * b);
	
	if ((int)(u + v) % 2)
		return color(1, 1, 1);
	return black();
}

// t_rgb	shade_hit_bm(t_world w, t_comp comps, t_light l, t_intersection	inter)
// {
//     t_uv uv = uv_of_sphere(inter.shape.sphere, comps.over_point);


//   const t_vec pu = pu_sphere(comps.over_point);
//   const t_vec pv = pv_sphere(comps.over_point, comps.shape.sphere);

//     t_fpair ij = ij_of_map(g_img.res, uv);
//     int i = ij.i;
//     int j = ij.j;
//   	const t_vec			lightv = normalize(
// 			sub(l.position, comps.over_point));
// 	
// 	t_point p = comps.over_point;
//     t_color ucolor = (t_color)(int)g_img.buffer[i + (j * g_img.res.width)];
// 	
//     // t_color ucolor = (t_color)(int)linear_interpolation(i, j, g_img);

//   comps.shape.sphere.material.color = color((float)ucolor.red / 255.0, (float)ucolor.green / 255.0, (float)ucolor.blue / 255.0);
// 	// comps.shape.sphere.material.color = cb(uv, 10, 10);
// 	const double		light_dot_normal = dot(lightv, normalize(opose(bm_normal_at(comps.shape.sphere, p, g_img))));
// 	// const double		light_dot_normal = dot(lightv, comps.normalv);

// 	// if (is_shadowed(w, comps.over_point, l) == true
// 	// 	|| light_dot_normal < 0)
// 	// 	return (black());

// 	return diffuse(comps.shape.super.material, l, light_dot_normal);
// }

t_rgb shade_hit_normal(t_world w, t_comp comps, t_light l, bool amb) {
	double				reflect_dot_eye;
	const t_material	m = comps.shape.super.material;
	t_vec				reflectv;
	const t_vec			lightv = normalize(
			sub(l.position, comps.over_point));
	const double		light_dot_normal = dot(lightv, comps.normalv);

	if (is_shadowed(w, comps.over_point, l) == true
		|| light_dot_normal < 0)
	{
		if (amb == false)
			return (ambient(m, l));
		return black();
	}
	reflectv = reflect(opose(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	return (rgb_sub(lighting(
			m,
			l,
			light_dot_normal,
			reflect_dot_eye), ambient(m, l)));
}

t_rgb shade_hit_texture() {
	puts("shade_hit_texture :: todo\n");
	exit(1);
	return black();
};

t_rgb shade_hit_checkerboard(t_point p, t_shape shape) {
	t_uv	uv;
	t_pair	ab;

	uv = (t_uv) {0,0};
	ab = pair(0, 0);
	if (shape.type == Sphere)
		uv = uv_of_sphere(shape.sphere, p), ab = pair(30, 30);
	else if (shape.type == Plane)
		uv = uv_of_plane(shape.plane.normal, p), ab = pair(10, 10);
	else if (shape.type == Cylinder)
		uv = uv_of_cylinder(shape.cylinder, p), ab = pair(30, 30);
	else
		ft_exit(parse_string("uv : checkerboard : unknown type\n"), 1);
	return checkerboard(uv,
					 shape.super.checkerboard_color1,
					 shape.super.checkerboard_color2,
					 ab);
};

t_vec	reflect(t_vec in, t_vec norm)
{
	return (sub(in, scalar(norm, 2.0 * dot(in, norm))));
}

bool	is_shadowed(t_world w, t_point p, t_light l)
{
	const t_vec				v = sub(l.position, p);
	const double			d = magnitude(v);
	const t_vec				direction = normalize(v);
	const t_ray				r = ray(p, direction);
	const t_intersection	i = intersect_world(w, r).intersections[0];

	return ((i.t >= 0 && i.t < d) == true);
}

t_rgb	color_at(t_world w, t_ray r)
{
	const t_hit		h = intersect_world(w, r);
	t_rgb			c;
	t_comp			comp;
	t_intersection	inter;
	int				index;

	c = black();
	index = 0;
	if (h.count == 0)
		return (c);
	inter = hit(h);
	if (inter.t < 0)
		return (c);
	while (index < w.amount_of_lights)
	{
		comp = prepare_computations(inter, r);
		if (inter.shape.super.color_type == Normal)
			c = rgb_sum(shade_hit_normal(w, comp, w.lights[index], index), c);
		else if (inter.shape.super.color_type == Checkerboard)
		{
			c = shade_hit_checkerboard(comp.over_point, inter.shape);
			break ;
		}
		else if (inter.shape.super.color_type == Texture)
		{
			c = shade_hit_texture();
			break;
		}
		++index;
	}
	return (c);
}
