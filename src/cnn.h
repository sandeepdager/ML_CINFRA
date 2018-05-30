#ifndef __CNN_H__
#define __CNN_H__
#include<iostream>
#include<fstream>
#include<iomanip>
#include <math.h>
#include<typeinfo>
enum active
{
	act_relu = 0,
	act_tanh = 1,
	act_sigm = 2
};

template <int L, int W, int D, class T >
class tansor
{

	public:
		T data[D][W][L];
	/*
		inline tansor operator=( T  inp[D*W*L] )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=inp+(k*D*L+j*L+i);
			return tmp;
		}
	*/




		inline tansor operator+(const tansor& inp )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=this->data[k][j][i] + inp.data[k][j][i];
			return tmp;
		}

		inline tansor operator+(const T& inp )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=this->data[k][j][i] + inp;
			return tmp;
		}

		inline tansor operator-(const tansor& inp )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=this->data[k][j][i] - inp.data[k][j][i];
			return tmp;
		}

		inline tansor operator-(const T& inp )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=this->data[k][j][i] - inp;
			return tmp;
		}



		inline tansor operator*(const tansor& inp )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=this->data[k][j][i] * inp.data[k][j][i];
			return tmp;
		}

		inline tansor operator/(const tansor& inp )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=this->data[k][j][i]/inp.data[k][j][i];
			return tmp;
		}

		inline tansor operator/(const T& inp )
		{
			tansor<L,W,D,T> tmp;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][j][i]=this->data[k][j][i]/inp;
			return tmp;
		}

		inline T operator()(int x, int y, int z){ return data[z][y][x];};
		inline void operator()(int x, int y, int z, T val){ data[z][y][x] = val;};

		template < int A, int B, int C>
			inline tansor< A, B, C, T > get_slice(int I, int J, int K)
			{
				tansor< A, B, C, T > out;
				for(int k=K;k<(K+C);k++)
					for(int j=J;j<(J+B);j++)
						for(int i=I;i<(I+A);i++)
							out.data[k-K][j-J][i-I]=this->data[k][j][i];
				return out;
			}

		template< class TAN>
			inline bool set_slice(int I, int J, int K, TAN inp )
			{
				for(int k=0;k<inp.d();k++)
					for(int j=0;j<inp.w();j++)
						for(int i=0;i<inp.l();i++)
							this->data[K+k][J+j][I+i]=inp.data[k][j][i];
				return true;
			}

		inline void rst()
		{
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						this->data[k][j][i]=0;
			return;
		}

		inline void sq_fill()
		{
			int count=1;
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++,count++)
						this->data[k][j][i]=count;
			return;
		}

		inline void rst(int val)
		{
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						this->data[k][j][i]=val;
			return;
		}

		inline tansor<1,1,D,T> max_xy()
		{
			tansor<1,1,D,T> tmp;
			tmp.rst();
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][0][0]=((this->data[k][j][i])>tmp.data[k][0][0])? this->data[k][j][i]  : tmp.data[k][0][0]  ;
			return tmp;
		}

		inline tansor<L,W,1,T> max_z()
		{
			tansor<L,W,1,T> tmp;
			tmp.rst();
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[0][j][i]=((this->data[k][j][i])>tmp.data[0][j][i])? this->data[k][j][i]  : tmp.data[0][j][i]  ;
			return tmp;
		}

		inline tansor<1,1,D,T> avg_xy()
		{
			tansor<1,1,D,T> tmp;
			tmp.rst();
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][0][0]+=this->data[k][j][i];
			return tmp/(W*L);
		}

		inline tansor<1,1,D,T> sum_xy()
		{
			tansor<1,1,D,T> tmp;
			tmp.rst();
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[k][0][0]+=this->data[k][j][i];
			return tmp;
		}

		inline tansor<L,W,1,T> avg_z()
		{
			tansor<L,W,1,T> tmp;
			tmp.rst();
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[0][j][i]+=this->data[k][j][i];
			return tmp/D;
		}

		inline tansor<L,W,1,T> sum_z()
		{
			tansor<L,W,1,T> tmp;
			tmp.rst();
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						tmp.data[0][j][i]+=this->data[k][j][i];
			return tmp;
		}



		inline tansor<L,W,D,int> sort()
		{
			tansor<1,1,L*W*D,int> idx;
			tansor<1,1,L*W*D,T> in;
			in = this->reshape_zxy<1,1,L*W*D>();		
			idx.sq_fill();
			for(int k=0;k<L*W*D;k++)
			{
				for(int i=(k+1);i<L*W*D;i++)
				{
					if ( in(0,0,k) < in(0,0,i))
					{
					T sw = in(0,0,k);
					int swidx = idx(0,0,k);
					in(0,0,k,in(0,0,i));
					idx(0,0,k,idx(0,0,i));
					in(0,0,i,sw);
					idx(0,0,i,swidx);
					}
					
				}
			}
			return idx;
		}

		template < int A, int B, int C >
			inline tansor<A,B,C,T> reshape( )
			{
				tansor< A, B, C, T> tmp;
				int a, b, c;
				a=b=c=0;
				for(int k=0;k<D;k++)
				{
					for(int j=0;j<W;j++)
					{
						for(int i=0;i<L;i++)
						{
							tmp.data[c][b][a]=this->data[k][j][i];
							a++;
							if(a==A)
							{
								a=0;
								b++;
								if(b==B)
								{
									b=0;
									c++;
								}	
							}	


						}
					}
				}
				return tmp;
			}	

		template < int A, int B, int C >
			inline tansor<A,B,C,T> reshape_xyz( )
			{
				tansor< A, B, C, T> tmp;
				int a, b, c;
				a=b=c=0;
				for(int k=0;k<D;k++)
				{
					for(int j=0;j<W;j++)
					{
						for(int i=0;i<L;i++)
						{
							tmp.data[c][b][a]=this->data[k][j][i];
							a++;
							if(a==A)
							{
								a=0;
								b++;
								if(b==B)
								{
									b=0;
									c++;
								}	
							}	


						}
					}
				}
				return tmp;
			}	

		template < int A, int B, int C >
			inline tansor<A,B,C,T> reshape_yzx( )
			{
				tansor< A, B, C, T> tmp;
				int a, b, c;
				a=b=c=0;
				for(int k=0;k<L;k++)
				{
					for(int j=0;j<D;j++)
					{
						for(int i=0;i<W;i++)
						{
							tmp.data[c][b][a]=this->data[j][i][k];
							a++;
							if(a==A)
							{
								a=0;
								b++;
								if(b==B)
								{
									b=0;
									c++;
								}	
							}	


						}
					}
				}
				return tmp;
			}	

		template < int A, int B, int C >
			inline tansor<A,B,C,T> reshape_zxy( )
			{
				tansor< A, B, C, T> tmp;
				int a, b, c;
				a=b=c=0;
				for(int k=0;k<W;k++)
				{
					for(int j=0;j<L;j++)
					{
						for(int i=0;i<D;i++)
						{
							tmp.data[c][b][a]=this->data[i][k][j];
							a++;
							if(a==A)
							{
								a=0;
								b++;
								if(b==B)
								{
									b=0;
									c++;
								}	
							}	


						}
					}
				}
				return tmp;
			}

		
	

		void disp()
		{
			std::cout.precision(12);
			for(int k=0;k<D;k++)
			{
				std::cout<<"depth "<<k<<"=\n";
				for(int j=0;j<W;j++)
				{
					for(int i=0;i<L;i++)
					{
						std::cout<<"["<<(this->data[k][j][i])<<"]\t";

					}
					std::cout<<std::endl;	
				}
				std::cout<<std::endl;
			}
			return;
		}

		void size()
		{
			std::cout<<typeid(data[0][0][0]).name()<<" ["<<L<<"x"<<W<<"x"<<D<<"]"<<std::endl;
		}

		inline void load( const T init_data[D*W*L] )
		{
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						this->data[k][j][i]=(T) init_data[k*L*W+j*L +i];
		}

		inline void load_xyz( const T init_data[D*W*L] )
		{
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						this->data[k][j][i]=(T) init_data[k*L*W+j*L +i];
		}

		inline void load_zxy( const T init_data[D*W*L] )
		{
			for(int k=0;k<W;k++)
				for(int j=0;j<L;j++)
					for(int i=0;i<D;i++)
						this->data[i][k][j]=(T) init_data[k*L*D+j*D +i];
		}

		inline void load_yzx( const T init_data[D*W*L] )
		{
			for(int k=0;k<L;k++)
				for(int j=0;j<D;j++)
					for(int i=0;i<W;i++)
						this->data[j][i][k]=(T) init_data[k*D*W+j*W +i];
		}




		/*	
			inline void load( const T* init_data )
			{
			for(int k=0;k<D;k++)
			for(int j=0;j<W;j++)
			for(int i=0;i<L;i++)
			this->data[k][j][i]=(T) (init_data++);
			}
		 */
		inline int l(){return L;}
		inline int w(){return W;}
		inline int d(){return D;}

		tansor( const T init_data[D*W*L] )
		{
			for(int k=0;k<D;k++)
				for(int j=0;j<W;j++)
					for(int i=0;i<L;i++)
						this->data[k][j][i]=(T) init_data[k*L*W+j*L +i];
		}

		tansor(){}



};

template < int L, int W, int D, int act, class T=int >
class activation 
{
	public:
		tansor < L, W, D, T > run ( tansor < L, W, D, T > inp)
		{
			for(int k=0;k<D;k++)
			{
				for(int j=0;j<W;j++)
				{
					for(int i=0;i<L;i++)
					{
						switch(act)
						{
							case 2:
								inp(i,j,k, (T)(1/(1+exp(-1*inp(i,j,k)))));
								break;
							case 1:

								inp(i,j,k, (T)(tanh((inp(i,j,k)))));
								break;
							default:
								inp(i,j,k, ((inp(i,j,k)>=0)?inp(i,j,k):0));
								break;
						}
					}
				}
			}
			return inp;	
		}

};



template < int L, int LI, int W, int WI, int D, int S=1, class T=int >
class pooling
{
	public:
		tansor < LI/S, WI/S, D, T > run( tansor < LI, WI, D, T > inp )
		{ 
			tansor < L, W, D, T > s;
			tansor < LI/S, WI/S, D, T > tmp_out;


			for(int j=0;j<WI;j+=S)
			{
				for(int i=0;i<LI;i+=S)
				{
					s = inp.template get_slice< L,W,D >( i,j,0 );
					tmp_out.set_slice(i/S, j/S ,0 , (s.max_xy()) )  ;
				}
			}
			return tmp_out;
		}
		pooling(){};
};


//template < int LengthofWeight, int LengthofImage, int WidthofWeight, int WidthofImage, int DepthofInputVolume, int DepthofOutputVolume, int Stride, class T >
template < int L, int LI, int W, int WI, int D, int DO, int S=1, class T=int >
class convolutional
{
	tansor<L, W, D, T> s, w[DO];
	tansor < 1, 1, DO, T > b;
	public:
	tansor < LI/S, WI/S, DO, T > run( tansor < LI, WI, D, T > inp, T pad)
	{

		tansor < LI/S, WI/S, DO, T > tmp_out;
		tansor < LI+L-1, WI+W-1, D, T > inp_ext;
		inp_ext.rst(pad);
		inp_ext.set_slice(L/2,W/2,0, inp);
		for(int p=0;p<DO;p++)
		{
			for(int j=0;j<WI;j+=S)
			{
				for(int i=0;i<LI;i+=S)
				{
					s = inp_ext.template get_slice< L,W,D >( i,j,0 );
					tmp_out(i/S, j/S ,p , ((((s*w[p]) .sum_z()) .sum_xy()) (0,0,0)) + b(0, 0, p) )  ;
						
				}
			}
		}
		return tmp_out; 
	}

	void load(tansor<L, W, D, T> winp[])
	{
		for(int i = 0; i< DO; i++)
			w[i] = winp[i];
	};
	void load(tansor<L, W, D, T> winp[], tansor < 1, 1, DO, T > binp)
	{
		for(int i = 0; i< DO; i++)
			w[i] = winp[i];
		b=binp;

	};

	convolutional()
	{
		b.rst();
	};
};

//template < int LengthofWeight, int LengthofImage, int WidthofWeight, int WidthofImage, int DepthofInputVolume, int DepthofOutputVolume, int Stride, class T >
template < int DI, int DO, class T=int >
class softmax
{
	tansor<1, 1, DI, T> s, w[DO];
	tansor<1, 1, DO, T> b;
	
	public:
	tansor < 1, 1, DO, T > run( tansor < 1, 1, DI, T > inp)
	{

		//inp.disp();
		//w[0].disp();	
		tansor < 1, 1, DO, T > tmp;
		tansor < 1, 1, DO, T > tmp_out;
		T sigma=0, mx_val;
		for(int p=0;p<DO;p++)
			tmp(0, 0 ,p , ((((inp*w[p]) .sum_z()) (0,0,0))+ b(0, 0, p)))  ;
		mx_val=tmp.max_z() (0, 0, 0);
		tmp=tmp-mx_val;
		for(int p=0;p<DO;p++)
			tmp_out(0, 0 ,p , exp(tmp(0,0,p)))  ;


		sigma = tmp_out.sum_z() (0,0,0);
		return tmp_out/sigma; 
	}

	void load(tansor<1, 1, DI, T> winp[] )
	{
		for(int i = 0; i< DO; i++)
			w[i] = winp[i];
	};

	void load(tansor<1, 1, DI, T> winp[], tansor < 1, 1, DO, T > binp)
	{
		for(int i = 0; i< DO; i++)
			w[i] = winp[i];
		b=binp;

	};

	softmax()
	{
		b.rst();
	};
};
#endif

