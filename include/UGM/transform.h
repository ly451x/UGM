#pragma once

#include "vec.h"
#include "point.h"
#include "normal.h"
#include "mat.h"
#include "scale.h"
#include "quat.h"
#include "euler.h"

#include "Interfaces/IMatrix/IMatrixMul.h"
#include "Interfaces/IMatrix/IMatrixInOut.h"

namespace Ubpa {
	template<typename T>
	struct transform : SIIT_CRTP<TemplateList<IMatrixInOut, IMatrixMul>, transform<T>, TypeList<TypeList<vec<T, 4>, Size<4>>, T>> {
		using SIIT_CRTP<TemplateList<IMatrixInOut, IMatrixMul>, transform<T>, TypeList<TypeList<vec<T, 4>, Size<4>>, T>>::SIIT_CRTP;
		using SIIT_CRTP<TemplateList<IMatrixInOut, IMatrixMul>, transform<T>, TypeList<TypeList<vec<T, 4>, Size<4>>, T>>::init;

		explicit transform(const mat<T, 4>& m) noexcept : transform(m[0], m[1], m[2], m[3]) {}
		
		explicit transform(const vec<T, 3>& translation) noexcept;
		explicit transform(const scale<T, 3>& scale) noexcept;
		transform(const vec<T, 3>& normalizedAxis, T radian) noexcept;
		explicit transform(const quat<T>& q) noexcept;
		explicit transform(const euler<T>& e) noexcept;

		// world space -> camera space
		static const transform look_at(const point<T,3>& pos, const point<T, 3>& target, const vec<T,3>& up = vec<T,3>(0, 1, 0)) noexcept;
		// orthographic, camera space -> clip space
		static const transform orthographic(T width, T height, T zNear, T zFar) noexcept;
		// perspcetive, camera space -> clip space
		// fovy: verticle field of view in radian
		// aspect : width / height
		static const transform perspcetive(T fovy, T aspect, T zNear, T zFar) noexcept;

		template<Axis axis>
		static const transform rotate_with(T angle) noexcept;

		const point<T,3> decompose_position() const noexcept { return { (*this)(0,3), (*this)(1,3), (*this)(2,3) }; }
		const scale<T, 3> decompose_scale() const noexcept;
		const mat<T, 3> decompose_rotation_matrix() const noexcept;
		const quat<T> decompose_quatenion() const noexcept;
		const euler<T> decompose_euler() const noexcept;
	};

	using transformf = transform<float>;
}

#include "transform.inl"