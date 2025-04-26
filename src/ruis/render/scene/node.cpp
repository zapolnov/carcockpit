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

#include "node.hpp"

using namespace ruis::render;

ruis::mat4 node::get_transformation_matrix() const
{
	if (std::holds_alternative<ruis::mat4>(this->transformation)) {
		return std::get<ruis::mat4>(this->transformation);
	} else {
		ASSERT(std::holds_alternative<trs_transformation>(this->transformation))

		const auto& trs = std::get<trs_transformation>(this->transformation);

		auto m = ruis::mat4().set_identity();
		m.translate(trs.translation);
		m.rotate(trs.rotation);
		m.scale(trs.scale);

		return m;
	}
}
