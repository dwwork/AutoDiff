#ifndef ADBASE
#define ADBASE

#include "Macros.h"
#include "ForwardDeclarations.h"
#include "BinaryOp.h"
#include "ConstantOp.h"
#include "UnaryOp.h"

namespace AD
{

template <typename Derived>
class ADBase
{

public:

   static const int nDeriv = internal::traits<Derived>::nDeriv;

	ADBase()=default;
	ADBase(const ADBase<Derived>&)=default;
	ADBase(ADBase<Derived>&&)=default;
	~ADBase()=default;


	inline Derived& operator = (const ADBase<Derived>& B) {
      derived().eval() = B.derived().eval();
		return derived();
	}

	inline Derived& operator = (ADBase<Derived>&& B) {
      derived().eval() = B.derived().eval();
		return derived();
	}

	template<typename OtherDerived>
	inline Derived& operator = (const ADBase<OtherDerived>& B) {
      derived().eval() = B.derived().eval();
		return derived();
	}

// 	#<{(|*
// 	 * += and -= operators
// 	 |)}>#
// 	inline Derived& operator += (const T& B) {
// 		derived() = derived() + B;
// 		return derived();
// 	}
//
// 	template<typename OtherDerived>
// 	inline Derived& operator += (const ADBase<OtherDerived>& B) {
// #ifndef NDEBUG
// 		internal::debug::compare_dims(derived(),B.derived());
// #endif
// 		derived() = derived() + B.derived();
// 		return derived();
// 	}
//
// 	inline Derived& operator -= (const T& B) {
// 		derived() = derived() - B;
// 		return derived();
// 	}
//
// 	template<typename OtherDerived>
// 	inline Derived& operator -= (const ADBase<OtherDerived>& B) {
// #ifndef NDEBUG
// 		internal::debug::compare_dims(derived(),B.derived());
// #endif
// 		derived() = derived() - B.derived();
// 		return derived();
// 	}

	/************************************************/

   AutoDiff_BASE_BINARY_OP(AddBinOp,+)
   AutoDiff_BASE_BINARY_OP(SubBinOp,-)
   AutoDiff_BASE_BINARY_OP(MulBinOp,*)
   AutoDiff_BASE_BINARY_OP(DivBinOp,/)

   inline const UnaryOp<Derived,NegUnOp<nDeriv> > operator -() const {
      return UnaryOp<Derived,NegUnOp<nDeriv> >(derived(),NegUnOp<nDeriv>());
   }

   // FortCpp_BASE_BINARY_OP(LesBinOp,<)
   // FortCpp_BASE_BINARY_OP(GreBinOp,>)
   // FortCpp_BASE_BINARY_OP(LEqBinOp,<=)
   // FortCpp_BASE_BINARY_OP(GEqBinOp,>=)
   // FortCpp_BASE_BINARY_OP(EquBinOp,==)
   // FortCpp_BASE_BINARY_OP(NEqBinOp,!=)
   //
   //
	// FortCpp_UNARY_FUNC(SqrtUnOp,sqrt)
	// FortCpp_UNARY_FUNC(SinUnOp,sin)
	// FortCpp_UNARY_FUNC(CosUnOp,cos)
   //
	// inline const UnaryOp<Derived,NegUnOp<T> >operator -() const {
	// 	return UnaryOp<Derived,NegUnOp<T> >(this->derived(),NegUnOp<T>());
	// }

	//
	//  inline explicit operator bool() const {
	//    for(int i=0;i<derived().size();i++){
	//      if(derived()[i]) return 1;
	//    }
	//    return 0;
	//  }

	const Derived& derived() const { return *static_cast<const Derived*>(this); }
	Derived& derived() { return *static_cast<Derived*>(this); }

	// friend std::ostream& operator << (std::ostream& os, const ADBase<Derived>& A) {
	// 	for (int i=0; i<A.size(); i++) {
	// 		os << A.derived()[i] << ' ';
	// 	}
	// 	return os;
	// }
};

}; // end namespace AD

#endif
