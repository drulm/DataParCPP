// ----------------------------------------------------------------------------------
//		Very Simple data-parallel class for educational purposes
// ----------------------------------------------------------------------------------

#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;


//	-------------- symbolic functions ---------------

/// <summary>
/// Adds the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>	
static T add(T x, T y)
{ 
	return x + y; 
}


/// <summary>
/// Subs the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>	
static T sub(T x, T y)
{ 
	return x - y; 
}


/// <summary>
/// Muls the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>	
static T mul(T x, T y)	
{ 
	return x * y; 
}


/// <summary>
/// Divs the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>	
static T div(T x, T y)	
{ 
	return x / y; 
}


/// <summary>
/// Mods the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>	
static T mod(T x, T y)	
{ 
	return x % y; 
}


/// <summary>
/// Ors the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>	
static T or(T x, T y)	
{ 
	return x | y; 
}


/// <summary>
/// Ands the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>	
static T and(T x, T y)	
{ 
	return x & y;
}


/// <summary>
/// Negs the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <returns></returns>
template <class T>	
static T neg(T x)
{ 
	return -x; 
}


/// <summary>
/// Nops the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <returns></returns>
template <class T>	
static T nop(T x)	
{
	return x; 
}


		//	-------------- special functions -----------------

template <class T>	
static T pow2(T x, T y)	
{
	return pow(x,y); 
}


		//	-------------- boolean functions -----------------

/// <summary>
/// Eqs the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>  
static bool eq(T x, T y)
{ 
	return x==y; 
}


/// <summary>
/// Nes the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>  
static bool ne(T x, T y)
{ 
	return x!=y; 
}


/// <summary>
/// Lts the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>  
static bool lt(T x, T y)
{ 
	return x<y; 
}


/// <summary>
/// Gts the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>  
static bool gt(T x, T y)
{ 
	return x>y; 
}


/// <summary>
/// Les the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>  
static bool le(T x, T y)
{ 
	return x<=y; 
}


/// <summary>
/// Ges the specified x.
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <returns></returns>
template <class T>  
static bool ge(T x, T y)
{ 
	return x>=y; 
}


//--------------------------------------------------------------------------------
//					CLASS PAR   ---    Simple data-parallel vectors
//--------------------------------------------------------------------------------
template <class T>
class par
{
	private:

		T		*data;					// data list
		int		N;						// Size of array
		static	bool	*flag;			// Is data element active
		static	int		flag_N;	


	public:

		/// <summary>
		/// Initializes a new instance of the <see cref="par{T}"/> class.
		/// </summary>
		/// <param name="n">The n.</param>
		par(const int n = 1)			//main constructor
		{ 
			N = n;	
			data = new T[n];
		}


		/// <summary>
		/// Finalizes an instance of the <see cref="par{T}"/> class.
		/// </summary>
		~par()							//destructor
		{ 
			delete [] data; 
		}


		/// <summary>
		/// Initializes a new instance of the <see cref="par{T}"/> class.
		/// </summary>
		/// <param name="x">The x.</param>
		par(const par<T> &x)			//copy construct
		{								//dup up to the space in new vector
			for (int i = 0; i < N; i++)
			{
				data[i] = x.data[i];
			}
		}
					
										// cast conversions
		/// <summary>
		/// Initializes a new instance of the <see cref="par{T}"/> class.
		/// </summary>
		/// <param name="d">The d.</param>
		par(const T &d)
		{
			for (int i = 0; i < N; i++)
			{
				data[i] = d;
			}
		}



//-----------------------------------------------------------------------
//			Main parallel operators
//-----------------------------------------------------------------------
		/// <summary>
		/// Par_bool_pars the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="f">if set to <c>true</c> [f].</param>
		/// <param name="y">The y.</param>
		/// -----------------------------------------------------------------------
		/// Main parallel operators
		/// -----------------------------------------------------------------------


		/// ----- BOOL ------

		friend void par_bool_par(par<T> &x, bool f(T, T), par<T> &y)
		{
			delete [] flag;
			flag = new bool[x.N];
			for (int i = 0; i < x.N; i++)
			{
				flag[i] = f(x.data[i], y.data[i]);
			}
			flag_N = x.N;
		}


		/// <summary>
		/// Par_bool_sings the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="f">if set to <c>true</c> [f].</param>
		/// <param name="t">The t.</param>
		friend void par_bool_sing(par<T> &x, bool f(T, T), const T &t)
		{
			static par<T> y(x.N);	
			y=t;
			par_bool_par(x,f,y);
		}


		// ------ PARALLEL ONLY ------

		/// <summary>
		/// Par_selfs the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="f">The f.</param>
		friend void par_self(par<T> &x, T f(T))
		{
			for (int i = 0; i < x.N; i++)
			{
				x.data[i] = f(x.data[i]);
			}
		}


		/// <summary>
		/// Par_to_pars the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <param name="f">The f.</param>
		/// <param name="x">The x.</param>
		friend void par_to_par(par<T> &y, T f(T), par<T> &x)
		{
			for (int i = 0; i < y.N; i++)
			{
				y.data[i] = f(x.data[i]);
			}
		}
		

		/// <summary>
		/// Par2_to_pars the specified z.
		/// </summary>
		/// <param name="z">The z.</param>
		/// <param name="f">The f.</param>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		friend void par2_to_par(par<T> &z, T f(T, T), par<T> &x, par<T> &y)
		{
			for (int i = 0; i < z.N; i++)
			{
				z.data[i] = f(x.data[i], y.data[i]);
			}
		}


//			------ SINGULAR (SCALAR) and PARALLEL ------
//				Singulars could involve broadcasts from master process

		/// <summary>
		/// Sing_to_pars the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <param name="f">The f.</param>
		/// <param name="t">The t.</param>
		friend void sing_to_par(par<T> &y, T f(T), const T &t)
		{
			for (int i = 0; i < y.N; i++)
			{
				y.data[i] = f(t);
			}
		}


		/// <summary>
		/// Par_and_sing_to_pars the specified z.
		/// </summary>
		/// <param name="z">The z.</param>
		/// <param name="f">The f.</param>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		friend void par_and_sing_to_par(par<T> &z, T f(T, T), par<T> &x, const T &t)
		{
			static par<T> y(x.N);
			y=t;
			par2_to_par(z,f,x,y);		
		}


		/// <summary>
		/// Par_and_sing_to_par_revs the specified z.
		/// </summary>
		/// <param name="z">The z.</param>
		/// <param name="f">The f.</param>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		friend void par_and_sing_to_par_rev(par<T> &z, T f(T, T), par<T> &x, const T &t)
		{
			static par<T> y(x.N);	
			y=t;
			par2_to_par(z,f,y,x);	
		}


//-----------------------------------------------------------------------
//			Arithmetic operators
//-----------------------------------------------------------------------
			//-----------------Z = op(X) ---------------------

		/// <summary>
		/// Operator-s this instance.
		/// </summary>
		/// <returns></returns>
		par<T> &operator - ()
		{ 
			static par<T> z(N); 
			par_to_par(z ,neg ,*this );
			return z;
		}


		/// <summary>
		/// Operator+s this instance.
		/// </summary>
		/// <returns></returns>
		par<T> &operator + ()
		{ 
			return *this; 
		}


			//-----------------Z = X (op) Y ------------------

		/// <summary>
		/// Operator+s the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		par<T> &operator + (par<T> &y)
		{
			static par<T> z(N); 
			par2_to_par(z, add, *this, y); 
			return z;
		}


		/// <summary>
		/// Operator-s the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		par<T> &operator - (par<T> &y)
		{
			static par<T> z(N); 
			par2_to_par(z, sub, *this, y); 
			return z;
		}

		
		/// <summary>
		/// Operator*s the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		par<T> &operator * (par<T> &y)
		{
			static par<T> z(N); 
			par2_to_par(z, mul, *this, y); 
			return z;
		}

		
		/// <summary>
		/// Operator/s the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		par<T> &operator / (par<T> &y)
		{
			static par<T> z(N); 
			par2_to_par(z, div, *this, y); 
			return z;
		}

		
		/// <summary>
		/// Operator%s the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		par<T> &operator % (par<T> &y)
		{
			static par<T> z(N); 
			par2_to_par(z, mod, *this, y); 
			return z;
		}

		
		/// <summary>
		/// Operator|s the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		par<T> &operator | (par<T> &y)
		{
			static par<T> z(N); 
			par2_to_par( z, or, *this, y); 
			return z;
		}

		
		/// <summary>
		/// Operator&s the specified y.
		/// </summary>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		par<T> &operator & (par<T> &y)
		{
			static par<T> z(N); 
			par2_to_par( z, and, *this, y); 
			return z;
		}

		
			//--------------- bool = X (op) Y		

		/// <summary>
		/// Operator==s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		friend bool operator == (par<T> &x, par<T> &y)
		{ 
			par_bool_par(x, eq, y); 
			return true; 
		}


		/// <summary>
		/// Operator!=s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		friend bool operator != (par<T> &x, par<T> &y)
		{ 
			par_bool_par(x, ne, y); 
			return true; 
		}

		
		/// <summary>
		/// Operators the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		friend bool operator < (par<T> &x, par<T> &y)
		{ 
			par_bool_par(x, lt, y); 
			return true; 
		}

		
		/// <summary>
		/// Operator>s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		friend bool operator > (par<T> &x, par<T> &y)
		{ 
			par_bool_par(x, gt, y); 
			return true; 
		}

		
		/// <summary>
		/// Operators the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		friend bool operator <= (par<T> &x, par<T> &y)
		{ 
			par_bool_par(x, le, y); 
			return true; 
		}

		
		/// <summary>
		/// Operator>=s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		/// <returns></returns>
		friend bool operator >= (par<T> &x, par<T> &y)
		{ 
			par_bool_par(x, ge, y); 
			return true; 
		}


			//--------------- bool = X op T
		
		/// <summary>
		/// Operator==s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend bool operator == (par<T> &x, const T &t)
		{ 
			par_bool_sing(x, eq, t); 
			return true; 
		}

		
		/// <summary>
		/// Operator!=s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend bool operator != (par<T> &x, const T &t)
		{ 
			par_bool_sing(x, ne, t); 
			return true; 
		}

		
		/// <summary>
		/// Operators the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend bool operator < (par<T> &x, const T &t)
		{ 
			par_bool_sing(x, lt, t); 
			return true; 
		}

		
		/// <summary>
		/// Operator>s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend bool operator > (par<T> &x, const T &t)
		{ 
			par_bool_sing(x, gt, t); 
			return true; 
		}

		
		/// <summary>
		/// Operators the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend bool operator <= (par<T> &x, const T &t)
		{ 
			par_bool_sing(x, le, t); 
			return true; 
		}

		
		/// <summary>
		/// Operator>=s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend bool operator >= (par<T> &x, const T &t)
		{ 
			par_bool_sing(x, ge, t); 
			return true; 
		}

		
		/// <summary>
		/// Operator==s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend bool operator == (const T &t, par<T> &x)
		{ 
			par_bool_sing(t, eq, x); 
			return true; 
		}

		
		/// <summary>
		/// Operator!=s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend bool operator != (const T &t, par<T> &x)
		{ 
			par_bool_sing(t, ne, x); 
			return true; 
		}

		
		/// <summary>
		/// Operators the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend bool operator < (const T &t, par<T> &x)
		{ 
			par_bool_sing(t, lt, x); 
			return true; 
		}

		
		/// <summary>
		/// Operator>s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend bool operator > (const T &t, par<T> &x)
		{ 
			par_bool_sing(t, gt, x); 
			return true; 
		}

		
		/// <summary>
		/// Operator>=s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend bool operator >= (const T &t, par<T> &x)
		{ 
			par_bool_sing(t, ge, x); 
			return true; 
		}

		
		/// <summary>
		/// Operators the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend bool operator <= (const T &t, par<T> &x)
		{ 
			par_bool_sing(t, le, x); 
			return true; 
		}


			//--------------- Z = X (op) T ----------------------------
		
		/// <summary>
		/// Operator+s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &operator + (par<T> &x, const T &t)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par(z, add, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator+s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &operator + (const T &t, par<T> &x)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par_rev(z, add, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator-s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &operator - (par<T> &x, const T &t)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par(z, sub, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator-s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &operator - (const T &t, par<T> &x)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par_rev(z, sub, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator*s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &operator * (par<T> &x, const T &t)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par(z, mul, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator*s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &operator * (const T &t, par<T> &x)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par_rev(z, mul, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator/s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &operator / (par<T> &x, const T &t)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par(z, div, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator/s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &operator / (const T &t, par<T> &x)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par_rev(z, div, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator%s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &operator % (par<T> &x, const T &t)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par(z, mod, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator%s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &operator % (const T &t, par<T> &x)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par_rev(z, mod, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator|s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &operator | (par<T> &x, const T &t)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par(z, or, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator|s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &operator | (const T &t, par<T> &x)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par_rev(z, or, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator&s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &operator & (par<T> &x, const T &t)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par(z, and, x, t); 
			return z;
		}

		
		/// <summary>
		/// Operator&s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &operator & (const T &t, par<T> &x)
		{
			static par<T> z(x.N); 
			par_and_sing_to_par_rev(z, and, x, t); 
			return z;
		}


// ---------------------------------------------------------------------
//			Input / Output  <<   >>
// ---------------------------------------------------------------------
		
		/// <summary>
		/// Operators the specified out.
		/// </summary>
		/// <param name="out">The out.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend ostream &operator << (ostream &out, par<T> &x)
		{
			for (int i = 0; i < x.N; i++)
			{
				out << setw(12) << x.data[i];
			}
			return out;
		}

		
		/// <summary>
		/// Operator>>s the specified in.
		/// </summary>
		/// <param name="in">The in.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend istream &operator >> (istream &in, par<T> &x)
		{
			for (int i = 0; i < x.N; i++)
			{
				in >> x.data[i];
			}
			return in;
		}


// -------------------------------------------------
//			Indexing []
// -------------------------------------------------
		
		/// <summary>
		/// Operator[]s the specified i.
		/// </summary>
		/// <param name="i">The i.</param>
		/// <returns></returns>
		T &operator [] (int i)
		{ 
			return data[i]; 
		} 

// -------------------------------------------------
//			Casting []
// -------------------------------------------------
		
// ----------------------------------------------------------------------
//			Assignment = 
// ----------------------------------------------------------------------

			//------ PAR = PAR; -------
		
		/// <summary>
		/// Operator=s the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		par<T> &operator = (const par<T> &x)
		{
			if (flag != NULL)
			{
				for (int i = 0; i < N; i++)
				{
					if (flag[i])
					{
						data[i] = x.data[i];
					}
				}
			}
			else
			{
				for (int i = 0; i < N; i++)
				{
					data[i] = x.data[i];
				}
			}
			return *this;
		}


			//------ PAR = SING; -------
			//    Also, think of as a communication broadcast...
		
		/// <summary>
		/// Operator=s the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		par<T> &operator = (const T &t)
		{
			if (flag != NULL)
			{
				for (int i = 0; i < N; i++)
				{
					if (flag[i]) data[i] = t;
				}
			}
			else
			{
				for (int i = 0; i < N; i++)
				{
					data[i] = t;
				}
			}
			return *this;
		}

		
		/// <summary>
		/// Self_addresses the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		void friend self_address(par<T> &x)
		{
			for (int i = 0; i < x.N; i++)
			{
				x.data[i] = i;
			}
		}

		
		/// <summary>
		/// All_ons this instance.
		/// </summary>
		/*void friend all_on()
		{
			for (int i = 0; i < flag_N; i++)
			{
				flag[i] = true;
			}
		}*/

		
		/// <summary>
		/// All_ons the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		void friend all_on(par<T> &x)
		{
			delete [] flag;
			flag = new bool[x.N];
			for (int i = 0; i < flag_N; i++)
			{
				flag[i] = true;
			}
		}

		
		/// <summary>
		/// Reduce_sums the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		T friend reduce_sum(const par<T> &x)
		{	
			T sum;
			sum = 0;
			for (int i = 0; i < x.N; i++)
			{
				sum = sum + x.data[i];
			}
			return sum;
		}

		
		/// <summary>
		/// Pows the specified x.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="t">The t.</param>
		/// <returns></returns>
		friend par<T> &pow(par<T> &x, T t)
		{
			static par<T> z(x.N);
			par<T> y(x.N);
			y = t;
			par2_to_par( z, pow, x, y); 
			return z;
		}

		
		/// <summary>
		/// Pows the specified t.
		/// </summary>
		/// <param name="t">The t.</param>
		/// <param name="x">The x.</param>
		/// <returns></returns>
		friend par<T> &pow(T t, par<T> &x)
		{
		static par<T> z(x.N);
		par<T> y(x.N);
		y = t;
		par2_to_par( z, pow, y, x); 
		return z;
		}

		
		/// <summary>
		/// Dumpflagses this instance.
		/// </summary>
		/*void friend dumpflags()
		{
			for (int i = 0; i < flag_N; i++)
			{
				cout << flag[i];
			}
			cout<<endl;
		}*/

};			// ------------- END OF CLASS ----------------



/// <summary>
/// The flag
/// </summary>
template <class T>			// set flag to NULL at start
bool *par<T>::flag = NULL;


/// <summary>
/// The flag_ n
/// </summary>
template <class T>
int par<T>::flag_N = 0;		// Number of flags start at 0


//////////////////////////////////////////
// A parallel conditional statement, complete with "else" clause:
//   ifp (condition) {
//     then clause...
//   } else {
//     else clause...
//   }
// The brackets are only necessary when they would be in normal C.
// A collection condition should be provided.  Those processors that are
// already active and where the condition is true will execute the THEN
// part of the ifp, and those who are either already inactive or where
// the condition is false will execute the ELSE part of the ifp.  Note
// that both parts will be executed once, so any scalar expressions will
// be evaluated once.  
//   Implementation: loop() always returns true twice, and false once,
// so the FOR loop goes twice.  which() returns true the first time,
// and false the second time, with a different set of VPs active each time.
// Nesting is ok.

#define ifp(condition) \
    for (Active.restrict(condition); Active.loop(); ) \
    	if (Active.which())


