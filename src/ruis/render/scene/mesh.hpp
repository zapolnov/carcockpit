/*
carcockpit - Car cockpit example GUI project

Copyright (C) 2024 Gagistech Oy <gagisechoy@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* ================ LICENSE END ================ */

#pragma once

#include <ruis/render/texture_2d.hpp>
#include <ruis/render/vertex_array.hpp>

namespace ruis::render {
struct material {
	std::string name;

	/**
	 * @brief Diffuse color texture.
	 */
	std::shared_ptr<ruis::render::texture_2d> tex_diffuse;

	/**
	 * @brief Normal map texture.
	 */
	std::shared_ptr<ruis::render::texture_2d> tex_normal;

	/**
	 * @brief ARM texture.
	 * ARM = ambient occlusion, roughness, metalness.
	 */
	std::shared_ptr<ruis::render::texture_2d> tex_arm;
};

struct primitive {
	utki::shared_ref<ruis::render::vertex_array> vao;
	utki::shared_ref<material> material_v;
};

struct mesh {
	std::string name;

	std::vector<utki::shared_ref<primitive>> primitives;
};

} // namespace ruis::render