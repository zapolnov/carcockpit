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
#include <ruis/animation/animation.hpp>
#include <ruis/render/scene/node.hpp>
#include "gltf_animation.hpp"
#include <optional>

namespace ruis::render {

class gltf;

struct gltf_animated_transform
{
	std::optional<ruis::vec3> translation;
	std::optional<ruis::quaternion> rotation;
	std::optional<ruis::vec3> scale;

	void reset()
	{
		translation.reset();
		rotation.reset();
		scale.reset();
	}
};

class gltf_animator : public animation
{
	std::weak_ptr<gltf> gltf_v;
	utki::shared_ref<gltf_animation> animation;
	std::vector<gltf_animated_transform> node_transforms;
	float weight;
	bool looping;

	friend class gltf;

public:
	explicit gltf_animator(std::shared_ptr<gltf> gltf, utki::shared_ref<ruis::updater> updater, utki::shared_ref<gltf_animation> anim, float weight_coeff = 1.0f, bool loop = false);
	gltf_animator(const gltf_animator&) = default;
	gltf_animator(gltf_animator&&) = default;
	gltf_animator& operator=(const gltf_animator&) = default;
	gltf_animator& operator=(gltf_animator&&) = default;
	virtual ~gltf_animator() = default;

	void on_update(real factor) override;
	void on_end(uint32_t dt) override;
};

} // namespace ruis::render
