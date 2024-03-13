#include "gauge.hpp"

#include <ruis/util/util.hpp>

using namespace ruis;

gauge::gauge(utki::shared_ref<ruis::context> c, all_parameters p) :
	widget(std::move(c), std::move(p.widget_params)),
	blending_widget(this->context, std::move(p.blending_params)),
	fraction_widget(this->context, {}),
	params(std::move(p.params))
{}

void gauge::on_lay_out(){
	// TODO: naming convention
	auto arrowDim = this->params.arrow.get().dims();
	real armLength = arrowDim.x() * this->params.arm_fraction;
	
	if(armLength <= 0){
		return;
	}
	
	auto scale = (std::max(this->rect().d.x(), this->rect().d.y()) / 2) / armLength;
	
	this->arrow_tex = this->params.arrow.get().get(arrowDim * scale).to_shared_ptr();
	
	if(this->params.shadow){
		// TRACE(<< "this->shadow->dims() * scale = " << this->shadow->dims() * scale << std::endl)
		this->shadow_tex = this->params.shadow->get(this->params.shadow->dims() * scale).to_shared_ptr();
		// TRACE(<< "this->shadow_tex->dims() = " << this->shadow_tex->dims() << std::endl)
	}
}


void gauge::render(const matrix4& matrix) const {
	ASSERT(this->arrow_tex)
	
	if(!this->arrow_tex->dims.is_positive() || this->params.arm_fraction <= 0){
		return;
	}
	
	this->set_blending_to_renderer();
	
	matrix4 matr(matrix);
	matr.translate(this->rect().d / 2);
	matr.scale(this->rect().d / 2);
	
	matrix4 mmm;
	mmm.set_identity();
	mmm.rotate(-(this->params.start_angle_rad + (this->params.end_angle_rad - this->params.start_angle_rad) * this->fraction()));
	{
		auto div = this->arrow_tex->dims.x() * this->params.arm_fraction;
		ASSERT(div >= 0)
		mmm.scale(1 / div);
	}
	
	if(this->shadow_tex && this->shadow_tex->dims.is_positive()){
		auto arrowFraction = this->arrow_tex->dims.x() / this->shadow_tex->dims.x();
		
		const auto shadowOffset = real(0.025f);
		
		matrix4 m(matr);
		m *= matrix4().set_identity().translate(shadowOffset, shadowOffset) * mmm;
		m.scale(this->shadow_tex->dims);
		m.translate(-(1 - this->params.arm_fraction) * arrowFraction - (1 - arrowFraction) / 2, -0.5);
		this->shadow_tex->render(m);
	}
	
	{
		matrix4 m(matr);
		m *= mmm;
		m.scale(this->arrow_tex->dims);
		m.translate(-(1 - this->params.arm_fraction), -0.5);
		this->arrow_tex->render(m);
	}
}
