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
#include "animation.hpp"

namespace ruis::render {

class animator
{
	utki::shared_ref<ruis::render::animation> animation;
	float weight;
	bool looping;
	double time;

public:
	explicit animator(utki::shared_ref<ruis::render::animation> anim, float weight_coeff = 1.0f, bool loop = false);
	animator(const animator&) = default;
	animator(animator&&) = default;
	animator& operator=(const animator&) = default;
	animator& operator=(animator&&) = default;
	virtual ~animator() = default;

	bool update(uint32_t dt);
};

} // namespace ruis::render
