#pragma once

#include <ruis/widget.hpp>
#include <ruis/widgets/base/blending_widget.hpp>
#include <ruis/widgets/base/fraction_widget.hpp>

#include <ruis/res/image.hpp>

namespace ruis{
class gauge :
		public ruis::blending_widget,
		public ruis::fraction_widget,
		virtual public ruis::widget
{
public:
	struct parameters{
		// TODO: naming convention
		std::shared_ptr<ruis::res::image> arrow;
		
		std::shared_ptr<ruis::res::image> shadow;
		
		real armFraction = 1;
		
		// TODO: use utki::deg_to_rad
		real startAngleRad = real(200) * real(utki::pi) / real(180);;
		real endAngleRad = real(-20) * real(utki::pi) / real(180);;
	};
private:
	parameters params;

	std::shared_ptr<const ruis::res::image::texture> arrowQuadTexture;
	std::shared_ptr<const ruis::res::image::texture> shadowQuadTexture;
public:
	gauge(const utki::shared_ref<ruis::context>& c, const tml::forest& desc);
	
	void on_lay_out()override;
	
	void render(const ruis::matrix4& matrix) const override;
};

namespace make{

struct gauge_parameters{

};

}

}
