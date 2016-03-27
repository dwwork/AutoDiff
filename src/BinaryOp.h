#ifndef AutoDiff_BINARYOP_H
#define AutoDiff_BINARYOP_H

namespace AD
{

namespace internal
{
   template<typename Lhs,typename Rhs,typename Op>
   struct traits<BinaryOp<Lhs,Rhs,Op> >
   {
      static const int nDeriv = internal::traits<Lhs>::nDeriv;
   };
}; // end namespace internal

/*
 * Binary Op
 */
template<typename Lhs,typename Rhs,typename Op>
class BinaryOp : public ADBase<BinaryOp<Lhs,Rhs,Op> >
{
	typedef BinaryOp<Lhs,Rhs,Op> Derived;
   static const int nDeriv = internal::traits<Derived>::nDeriv;
   typedef AutoDiff<nDeriv> T;

protected:
	const Lhs& _lhs;
	const Rhs& _rhs;
	const Op&  _op;

public:
	BinaryOp(const Lhs& lhs,const Rhs& rhs,const Op& op): _lhs(lhs), _rhs(rhs), _op(op) {
	};
	BinaryOp(const BinaryOp& A) : _lhs(A._lhs), _rhs(A._rhs), _op(A._op) { }

	T eval() const {
		return _op.eval(_lhs.eval(),_rhs.eval());
	}

};

template<int nDeriv>
struct AddBinOp
{
   typedef AutoDiff<nDeriv> T;
   inline static const
      T eval(const T& lhs,const T& rhs){
         T a;
         a.x  = lhs.x + rhs.x;
         a.dx = lhs.dx + rhs.dx;
         return a;
      }
};

template<int nDeriv>
struct SubBinOp
{
   typedef AutoDiff<nDeriv> T;
   inline static const
      T eval(const T& lhs,const T& rhs){
         T a;
         a.x  = lhs.x - rhs.x;
         a.dx = lhs.dx - rhs.dx;
         return a;
      }
};

template<int nDeriv>
struct MulBinOp
{
   typedef AutoDiff<nDeriv> T;
   inline static const
      T eval(const T& lhs,const T& rhs){
         T a;
         a.x  = lhs.x * rhs.x;
         a.dx = lhs.dx*rhs.x + lhs.x*rhs.dx;
         return a;
      }
};

template<int nDeriv>
struct DivBinOp
{
   typedef AutoDiff<nDeriv> T;
   inline static const
      T eval(const T& lhs,const T& rhs){
         T a;
         a.x  = lhs.x / rhs.x;
         a.dx = (lhs.dx*rhs.x - lhs.x*rhs.dx)/(rhs.x*rhs.x);
         return a;
      }
};

}; // end namespace AD

#endif
