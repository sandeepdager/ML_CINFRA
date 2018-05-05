/*
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	fstream img_i,img_o;
	//img_i.open("IMAGE.TXT", fstream::in);
	img_i.open(argv[1],ios::in);
	img_o.open("w.h",ios::out);
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
		CNN(image_in, class_out);

		// Flushing ac_channel based outputs
	}
	// Return success
	img_i.close();	
	img_o.close();	
	return 0 ;
}
*/
// istream::get example




#include <iostream>     // std::cin, std::cout
#include <fstream>      // std::ifstream
#include <string.h>
#define NM 10


void strrev(char str[NM])
{
	char swap;
	for(int i=0 ; i<strlen(str)/2; i++)
	{
		swap=str[strlen(str)-1-i];
		str[strlen(str)-1-i]=str[i];
		str[i]=swap;
	}

}

bool pmatch( char pat[NM],char buff[NM])
{
bool match=true;
//	for(int j=0;j<NM; j++)
//		std::cout<<"\n"<<buff[j]<<std::endl;
	

	strrev(pat);
	for(int i=0;i<strlen(pat);i++)
	{
	if(pat[i]!=buff[i])
		match=false;			
	}
return match;	
}



int main () {
	char str[256]="weight.json", pat[NM], buff[NM]="";
	int lcount=0, wcount=0;
	std::cout << "Enter the name of an existing text file: ";
	//std::cin>>str;    // get c-string
	std::cout << "Enter pattern: ";
	//std::cin>>pat;    // get c-string
	std::ifstream is(str);     // open file
	bool q_t=0,wb=0;
	char c;
	while (is.get(c))          // loop getting single characters
	{

		strcpy(pat,",");
		for(int i=NM-1; i>0; i--)
			buff[i]=buff[i-1];			
		buff[0]=c;
		strcpy(pat,"filter");
		if(pmatch(pat,buff))
		{
		wb=0;
		lcount++;
		wcount=1;
		}
		strcpy(pat,"biases");
		if(pmatch(pat,buff))
		{
		wb=1;
		}
	
		strcpy(pat,"{\"sx\"");
		if(pmatch(pat,buff))
		{
		std::cout<<"\ntansor< ";
		}
		strcpy(pat,"w");
		if(pmatch(pat,buff))
		{
		wcount++;
		if(wb==1)
			std::cout<<"float >  l"<<lcount<<"b";
		else	
			std::cout<<"float >  l"<<lcount<<"w"<<(wcount-1) ;
		}

		strcpy(pat,"\"");
		
		if(pmatch(pat,buff))
			q_t=!q_t;
	
		if(q_t==1)
	          continue;	
		strcpy(pat,"}");
		if((c!='\"')&&(c!=':')&&(c!=']')&&(c!='['))
		std::cout << c;
		if(pmatch(pat,buff))
		{
			std::cout<<";\n";
		}
	}
	//std::cout<<"Pat match for "<<count<<" times"<<std::endl;
	is.close();                // close file
	return 0;
}


