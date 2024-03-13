#include "gui.hpp"

#include <ruis/container.hpp>
#include <ruis/widgets/label/image.hpp>
#include <ruis/widgets/slider/scroll_bar.hpp>

#include "gauge.hpp"

using namespace std::string_literals;

using namespace carcockpit;

utki::shared_ref<ruis::widget> carcockpit::make_root_layout(utki::shared_ref<ruis::context> c){
    namespace m = ruis::make;
	using ruis::lp;

	return
		// clang-format off
		m::container(
			c,
			{
				.container_params = {
					.layout = ruis::layout::column
				}
			},
			{
                utki::dynamic_reference_cast<ruis::widget>(
                    utki::make_shared<ruis::horizontal_scroll_bar>(
                        c,
                        tml::read(R"(
                            lp{dx{fill}}
                        )")
                    )
                ),
                m::container(
                    c,
                    {
                        .widget_params = {
                            .lp = {
                                .dims = {lp::fill, 0},
                                .weight = 1
                            }
                        },
                        .container_params = {
                            .layout = ruis::layout::pile
                        }
                    },
                    {
                        m::image(
                            c,
                            {
                                .widget_params = {
                                    .lp = {
                                        .dims = {lp::fill, lp::fill}
                                    }
                                },
                                .image_params = {
                                    .img = c.get().loader.load<ruis::res::image>("ruis_img_gauge_scale")
                                }
                            }
                        ),
                        utki::dynamic_reference_cast<ruis::widget>(
                            utki::make_shared<ruis::gauge>(c,
                            tml::read(R"(
                                id{gauge}
                                lp{dx{fill} dy{fill}}
                                armFraction{0.75}
                                startAngle{225}
                                endAngle{-45}
                            )"))
                        )
                    }
                )
            }
		);
	// clang-format on
}
