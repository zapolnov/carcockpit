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

class gltf
{
	uint32_t time = 0;
	std::vector<utki::shared_ref<animator>> animators{};

public:
	std::vector<utki::shared_ref<scene>> scenes{};
	std::vector<utki::shared_ref<animation>> animations{};

	std::shared_ptr<scene> default_scene;

	gltf() = default;
	gltf(const gltf&) = default;
	gltf(gltf&&) = default;
	gltf& operator=(const gltf&) = default;
	gltf& operator=(gltf&&) = default;
	virtual ~gltf() = default;

	void play_animation(const std::string& name, bool loop) { play_animation(name, 1.0f, loop); }
	void play_animation(const std::string& name, float weight = 1.0f, bool loop = false);

	void update(uint32_t dt);
};

} // namespace ruis::render