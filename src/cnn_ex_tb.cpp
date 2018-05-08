// Place system includes here
#include <iostream>

#include "cnn_ex.h"

// -------------------------------------------
// Start of MAIN
#define CW_CHECK_STREAM(istr, fname, desc) if (istr.fail()) { std::cerr << "Could not open " << desc << " file '" << fname << std::endl; return -1; }
using namespace std;
int main(int argc, char *argv[])
{
	fstream img_i,img_o;
	//img_i.open("IMAGE.TXT", fstream::in);
	img_i.open("cifar10bin/test_batch.bin",ios::binary|ios::in);
	img_o.open("IMAGE_OUT.TXT",ios::binary|ios::out);
	CW_CHECK_STREAM(img_i,"IMAGE.TXT","INPUT FILE");	
	// Place local testbench variables here
	//ac_int<12, false > output;
	int count=0;
	//int inp_int, out_count=0; 


	bitmap_image image(32,32);
	tansor< 32, 32, 3, float > image_in;		
	tansor< 1, 1, 10, float > class_out;		
	// Main test iterations start here
	cifar10 img_cifar;
	for (int iteration = 1; iteration <= N_IMG; ++iteration) {
		//img_i>>inp_int;
		//char inp_img[1024];

		img_i.read((char*)&img_cifar,sizeof(cifar10));

		for(int y=0;y<32;y++)
		{
			for(int x=0;x<32;x++)
			{
				image.set_pixel(x,y,img_cifar.r[y*32+x],img_cifar.g[y*32+x],img_cifar.b[y*32+x]);
				image_in(x,y,0,(float) img_cifar.r[y*32+x]);
				image_in(x,y,1,(float) img_cifar.g[y*32+x]);
				image_in(x,y,2,(float) img_cifar.b[y*32+x]);
			}
		}
		image.save_image("image_out.bmp");

		if(iteration<=HIEGHT*WIDTH)
			count++;
		else
			count=0;

		// Call original function and capture data
#ifdef TEST
		CNN_test(image_in, class_out);
#else
		CNN(image_in, class_out);
#endif
std::cout<<"Input Class: \n";	
		switch(img_cifar.lable)
		{
		case 0:
		std::cout<<"Airplane"<<std::endl;
		break;

		case 1:
		std::cout<<"Automobile"<<std::endl;
		break;

		case 2:
		std::cout<<"Bird"<<std::endl;
		break;

		case 3:
		std::cout<<"Cat"<<std::endl;
		break;
	
		case 4:
		std::cout<<"Deer"<<std::endl;
		break;

		case 5:
		std::cout<<"Dog"<<std::endl;
		break;
	
		case 6:
		std::cout<<"frog"<<std::endl;
		break;
				
		case 7:
		std::cout<<"Hourse"<<std::endl;
		break;		

		case 8:
		std::cout<<"Ship"<<std::endl;
		break;
	
		case 9:
		std::cout<<"Truck"<<std::endl;
		break;
		
		default:
		std::cout<<"Wrong Output class"<<std::endl;
		break;
			
		};

std::cout<<"Output Class: \n";	
class_out.disp();
/*
		switch(img_cifar.lable)
		{
		case 0:
		std::cout<<"Airplane"<<std::endl;
		break;

		case 1:
		std::cout<<"Automobile"<<std::endl;
		break;

		case 2:
		std::cout<<"Bird"<<std::endl;
		break;

		case 3:
		std::cout<<"Cat"<<std::endl;
		break;
	
		case 4:
		std::cout<<"Deer"<<std::endl;
		break;

		case 5:
		std::cout<<"Dog"<<std::endl;
		break;
	
		case 6:
		std::cout<<"frog"<<std::endl;
		break;
				
		case 7:
		std::cout<<"Hourse"<<std::endl;
		break;		

		case 8:
		std::cout<<"Ship"<<std::endl;
		break;
	
		case 9:
		std::cout<<"Truck"<<std::endl;
		break;
		
		default:
		std::cout<<"Wrong Output class"<<std::endl;
		break;
			
		}
*/				
		// Flushing ac_channel based outputs
		/*
		   while (out.available(1))
		   { 
		   output = out.read();
		   if((out_count!=0)&&(out_count<=HIEGHT*WIDTH))
		   img_o<<output<<endl;
		   out_count++;      
		//std::cout<<output<<std::endl;
		}
		 */
	}
	// Return success
	img_i.close();	
	img_o.close();	
	return 0 ;
}
