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

	// clang-format off
	auto w = m::container(
        c,
        {
            .container_params = {
                .layout = ruis::layout::column
            }
        },
        {
            // TODO: should be slider, not scroll bar, band is not needed
            utki::dynamic_reference_cast<ruis::widget>(
                utki::make_shared<ruis::horizontal_scroll_bar>(
                    c,
                    tml::read(R"(
                        id{gauge_slider}
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

    auto gauge = w.get().try_get_widget_as<ruis::gauge>("gauge");
    ASSERT(gauge)
    auto weakGauge = utki::make_weak(gauge);
    
    auto slider = w.get().try_get_widget_as<ruis::fraction_widget>("gauge_slider");
    ASSERT(slider)

    slider->fraction_change_handler = [weakGauge](ruis::fraction_widget& s){
        if(auto g = weakGauge.lock()){
            g->set_fraction(s.fraction());
        }
    };

    return w;
}
