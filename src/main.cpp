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

#include <clargs/parser.hpp>
#include <ruis/container.hpp>
#include <ruis/layouts/linear_layout.hpp>
#include <ruisapp/application.hpp>

using namespace std::string_literals;

namespace {
utki::shared_ref<ruis::widget> build_root_layout(utki::shared_ref<ruis::context> c)
{
	namespace m = ruis::make;
	using ruis::lp;

	return
		// clang-format off
		m::container(
			c,
			{
				.widget_params = {
					.id = "root"s
				},
				.container_params = {
					.layout = ruis::column_layout::instance
				}
			},
			{}
		);
	// clang-format on
}
} // namespace

namespace carcockpit {

class application : public ruisapp::application
{
public:
	application(bool window, std::string_view res_path) :
		ruisapp::application( //
			"carcockpit"s,
			[]() {
				// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
				ruisapp::window_params wp(r4::vector2<unsigned>(1024, 600));
				return wp;
			}()
		)
	{
		this->set_fullscreen(!window);

		this->gui.init_standard_widgets(*this->get_res_file());

		this->gui.context.get().loader.mount_res_pack(*this->get_res_file(papki::as_dir(res_path)));

		auto c = build_root_layout(this->gui.context);
		this->gui.set_root(c);
	}
};

const ruisapp::application_factory app_fac([](auto args) {
	bool window = false;

	// TODO: look in /usr/local/share/carcockpit first?
	std::string res_path = "/usr/share/carcockpit"s;

	clargs::parser p;

	p.add("window", "run in window mode", [&]() {
		window = true;
	});

	p.add("res-path", "resources path, default = /usr/share/carcockpit", [&](std::string_view v) {
		res_path = v;
	});

	p.parse(args);

	return std::make_unique<application>(window, res_path);
});

} // namespace carcockpit
