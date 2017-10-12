#include "rgb2yuv.h"


#define RM  0x00FF0000
#define GM  0x0000FF00
#define BM  0x000000FF

#define Rval(data) ( (data & RM) >> 16) 
#define Gval(data) ( (data & GM) >> 8) 
#define Bval(data) ( (data & BM) ) 


//#define SEL_SIMPLE	
#define SEL_SDTV1    // CCIR 601 
//#define SEL_SDTV2  // BT.601
//#define SEL_HDTV   // BT.701



//#define DBG_PRINT


int main()
{

#if defined(SEL_SIMPLE) || defined(SEL_SDTV1) || defined(SEL_SDTV2) || defined(SEL_HDTV)
	float Y,U,V;
	int rY,rU,rV;
#else
	int Y,U,V;
#endif
	int i;

	int size=0;

	size = sizeof(Data) / sizeof(unsigned int);


	for(i=0;i<size;i++)
	{

#if defined(SEL_SIMPLE)// refer to other site 

		Y = (  0.257 *  Rval(Data[i])  ) + (  0.504 * Gval(Data[i]) ) + (  0.098 * Bval(Data[i]) )  + 16 ;  
		U = (  -0.148 *  Rval(Data[i])  ) - (  0.291 * Gval(Data[i]) ) + (  0.439 * Bval(Data[i]) ) + 128;  
		V = (  0.439 *  Rval(Data[i])  ) - (  0.368 * Gval(Data[i]) ) - (  0.071 * Bval(Data[i]) ) + 128;  

#elif defined(SEL_SDTV1) //CCIR 601 , https://www.mikekohn.net/file_formats/yuv_rgb_converter.php, http://softpixel.com/~cwright/programming/colorspace/yuv/

		Y = (  0.299 *  Rval(Data[i])  ) + (  0.587 * Gval(Data[i]) ) + (  0.114 * Bval(Data[i]) ) ;  
		U = (  -0.168736 *  Rval(Data[i])  ) - (  0.331264 * Gval(Data[i]) ) + (  0.5000 * Bval(Data[i]) ) + 128 ;  
		V = (  0.5000 *  Rval(Data[i])  ) - (  0.418688 * Gval(Data[i]) ) - (  0.081312 * Bval(Data[i]) ) + 128;  

#elif defined(SEL_SDTV2) //BT.601 , https://en.wikipedia.org/wiki/YUV

		Y = (  0.299 *  Rval(Data[i])  ) + (  0.587 * Gval(Data[i]) ) + (  0.114 * Bval(Data[i]) ) ;  
		U = (  -0.14713 *  Rval(Data[i])  ) - (  0.28886 * Gval(Data[i]) ) + (  0.436 * Bval(Data[i]) );  
		V = (  0.615 *  Rval(Data[i])  ) - (  0.51499 * Gval(Data[i]) ) - (  0.10001 * Bval(Data[i]) );  

#elif defined(SEL_HDTV) //BT.709 , https://en.wikipedia.org/wiki/YUV

		Y = (  0.2126 *  Rval(Data[i])  ) + (  0.7152 * Gval(Data[i]) ) + (  0.0722 * Bval(Data[i]) );  
		U = (  -0.09991 *  Rval(Data[i])  ) - (  0.33609 * Gval(Data[i]) ) + (  0.436 * Bval(Data[i]) );  
		V = (  0.615 *  Rval(Data[i])  ) - (  0.55861 * Gval(Data[i]) ) - (  0.05639 * Bval(Data[i]) );  

#else
		Y = (  66 *  Rval(Data[i])  ) + (  129 * Gval(Data[i]) ) + (  25 * Bval(Data[i])  );  
		U = ( -38 *  Rval(Data[i])  ) - (  74 * Gval(Data[i]) ) +  (  112 * Bval(Data[i]) );  
		V = ( 112 *  Rval(Data[i])  ) - (  94 * Gval(Data[i]) ) -  ( 18 * Bval(Data[i])   );  

		Y = (Y>>8)+16;
		U = (U>>8)+128;
		V = (V>>8)+128;
#endif

		rY = Y;
		rU = U;
		rV = V;

#if defined(DBG_PRINT)
		printf("R=%d   G=%d  , B=%d \n",Rval(Data[i]),	Gval(Data[i]),	Bval(Data[i]) );
#endif

#if defined(SEL_SIMPLE) || defined(SEL_SDTV1) || defined(SEL_SDTV2)  || defined(SEL_HDTV)

	#if defined(DBG_PRINT)
		printf("Y=%f , U =%f , V=%f \n",Y,U,V);
		printf("Y=%d , U =%d , V=%d \n",rY,rU,rV);
	#else
	//	printf("{ %03d , %03d , %03d }, //%d/%d \n",rY,rU,rV,i,size);
		printf("{ %d , %d , %d }, //%d/%d \n",rY,rU,rV,i,size);
	#endif
#else

	#if defined(DBG_PRINT)
		printf("Y=%d , U =%d , V=%d \n",rY,rU,rV);
	#endif

#endif


	}

	return 0;
}
