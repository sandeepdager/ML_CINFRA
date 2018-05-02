
#include "cnn_ex.h"

#define TEST_SOFT_MAX
//#define TEST_LOAD
//#define TEST_INIT
//#define TEST_POOL
//#define TEST_RESHAPE
//#define TEST_SSLICE

//#pragma hls_design top
void CNN_test(ac_channel< ac_int<BIT_INP,0> > &inp_chan, ac_channel< ac_int<BIT_OUT,0> > &out_chan)
{

#ifdef TEST_RESHAPE
	tansor<6,6,3,int> tin;
	tansor<3,3,6,int> tout;
	tin.sq_fill();
	tout=tin.reshape<3,3,6>();
	tin.disp();
	tout.disp();
#endif

#ifdef TEST_SSLICE
	tansor<6,6,3,int> tin;
	tansor<8,8,3,int> tout;
	tin.sq_fill();
	tout.rst();
	tout.set_slice(1,1,0,tin);
	tin.disp();
	tout.disp();
#endif

#ifdef TEST_GSLICE
	tansor<6,6,3,int> tin;
	tansor<3,3,3,int> tout;
	tin.sq_fill();
	tout=tin.get_slice<3,3,3>(1,2,0);
	tin.disp();
	tout.disp();
#endif

#ifdef TEST_INIT
	const int W_L1[12] = { 1, 2, 3, 4, 11, 12, 13, 14, 21, 22, 23, 24 } ;
	tansor<2,2,3,int> tin(W_L1);
	tin.disp();
#endif

#ifdef TEST_LOAD
	const int W_L1[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 21, 22, 23, 24 } ;
	tansor<2,2,3,int> tin;
	tin.load(W_L1);
	tin.disp();
#endif

#ifdef TEST_SOFT_MAX
	tansor<1,1,9,float> tin;
	tansor<1,1,3,float> tout;
	tin.sq_fill();
	const float w1[9] = 	{0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09};
	const float w2[9] = 	{0.01,0.02,0.03,0.04,0.05,0.04,0.03,0.02,0.01};
	const float w3[9] = 	{0.09,0.08,0.07,0.06,0.05,0.04,0.03,0.02,0.01};
	tansor< 1,1,9, float > weight[3];
	
	weight[0].load(w1);
	weight[1].load(w2);
	weight[2].load(w3);	

	softmax< 9, 3, float > sfm;
	sfm.load(weight);
	tout=sfm.run(tin);
	tout.disp();
#endif






	//t2 = t1.get_slice<3,3,3>(1,2,0);
	//t3.rst(1);
	//tansor<3, 3, 3, int> weight[4];
	//for(int i=0; i<4 ; i++)
	//	weight[i].rst(i);
	//convolutional<3,9,3,9,3,4,1,int> conv1;
	//pooling<2,10,2,10,3,2,int> pool1;
	//activation<10,10,3, act_sigm, double > active1;
	//conv1.load(weight);
	//tinp.rst(2);
	//tpot= pool1.run(tpin);
	//tout = conv1.run(tinp, 0);
	//tain.disp();
	//tain = active1.run(tain);
	//tain.disp();





	//tpin.disp();
	//tpot.disp();
	//int val = t3.avg_xy() .avg_z() (0, 0, 0);
}



void CNN(tansor< 32, 32, 3, float >  &inp_image, tansor< 1, 1, 10, float >  &out_class)
{

////////layer_defs = [];
////////layer_defs.push({type:'input', out_sx:32, out_sy:32, out_depth:3});
////////layer_defs.push({type:'conv', sx:5, filters:16, stride:1, pad:2, activation:'relu'});
////////layer_defs.push({type:'pool', sx:2, stride:2});
////////layer_defs.push({type:'conv', sx:5, filters:20, stride:1, pad:2, activation:'relu'});
////////layer_defs.push({type:'pool', sx:2, stride:2});
////////layer_defs.push({type:'conv', sx:5, filters:20, stride:1, pad:2, activation:'relu'});
////////layer_defs.push({type:'pool', sx:2, stride:2});
////////layer_defs.push({type:'softmax', num_classes:10});


inp_image.disp();






}
