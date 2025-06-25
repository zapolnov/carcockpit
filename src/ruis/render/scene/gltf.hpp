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
#include "scene.hpp"

namespace ruis::render {

class gltf : public std::enable_shared_from_this<gltf>
{
	std::vector<utki::shared_ref<gltf_animator>> animators{};

	friend class gltf_animator;

public:
	std::vector<utki::shared_ref<node>> nodes{}; // TODO: we only use size of this
	std::vector<utki::shared_ref<scene>> scenes{};
	std::vector<utki::shared_ref<gltf_animation>> animations{};

	std::shared_ptr<scene> default_scene;

	gltf() = default;
	gltf(const gltf&) = default;
	gltf(gltf&&) = default;
	gltf& operator=(const gltf&) = default;
	gltf& operator=(gltf&&) = default;
	virtual ~gltf() = default;

	// TODO: this is bad
	ruis::mat4 get_node_transformation_matrix(const node& node) const;

	void play_animation(utki::shared_ref<ruis::updater> updater, const std::string& name, bool loop) { play_animation(updater, name, 1.0f, loop); }
	void play_animation(utki::shared_ref<ruis::updater> updater, const std::string& name, float weight = 1.0f, bool loop = false);
};

} // namespace ruis::render