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

#include <variant>

#include <r4/quaternion.hpp>
#include <r4/vector.hpp>
#include <ruis/config.hpp>

#include "mesh.hpp"

namespace ruis::render {

struct trs_transformation {
	ruis::vec3 translation;
	ruis::quaternion rotation;
	ruis::vec3 scale;
};

constexpr trs_transformation identity_trs_transformation{
	.translation = {0, 0, 0},
	.rotation = {0, 0, 0, 1},
	.scale = {1, 1, 1}
};

class node
{
public:
	std::string name;

	std::shared_ptr<mesh> mesh_v;
	trs_transformation transformation;

	std::vector<utki::shared_ref<node>> children;

	ruis::mat4 get_transformation_matrix() const;
	// TODO: consider support for transformnation in form of a matrix which comes from GLTF file, e.g.
	// std::variant<ruis::mat4, trs> transformation;

	node(
		std::string name, //
		std::shared_ptr<mesh> mesh_v,
		const trs_transformation& transformation = identity_trs_transformation
	);
};

} // namespace ruis::render
