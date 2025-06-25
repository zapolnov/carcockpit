/*
carcockpit - Car cockpit example GUI project

Copyright (C) 2024-2025 Gagistech Oy <gagisechoy@gmail.com>

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
#include <utki/shared_ref.hpp>
#include <ruis/config.hpp>

namespace ruis::render {

struct node;
struct accessor;

struct gltf_animation_sampler {
	enum class interpolation {
		linear,
		step,
		cubic_spline
	};

	std::shared_ptr<accessor> input;
	std::shared_ptr<accessor> output;
	interpolation interpolation_v;
};

struct gltf_animation_channel {
	enum class path {
		translation,
		rotation,
		scale,
		weights,
	};

	std::shared_ptr<gltf_animation_sampler> sampler;
	std::shared_ptr<node> target_node;
	path target_path;
};

struct gltf_animation {
	std::string name;
	real duration;
	std::vector<std::shared_ptr<gltf_animation_sampler>> samplers;
	std::vector<gltf_animation_channel> channels;
};

} // namespace ruis::render
