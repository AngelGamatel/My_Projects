#include "libs.h"
#include "Vector0.h"
#include "Vector1.h"
#include <fstream>

int main()
{
	Factory0 F0;
	Factory1 F1;
	Vector0 tmp;
    	//omp_set_num_threads (1);
    	size_t t, file_size, N=10000;
    	Vector* *array = new Vector*[N];
    	std::string where;
    	std::ifstream input("1");
    	if(!input.is_open()) std::cout << "file not found" << std::endl;
    	else
    	{
    	input >> file_size;
    	Vector* *vec = new Vector*[file_size];
    	for(size_t i=0; i<file_size; i++)
    	{
    		std::ostream* out; 
        	std::ofstream fout;
    		Vector0 vec_summ;
       		Vector0 vec_c; 
        	input >> t;
        	input >> where;
        	if(where == "cout") 
        	{
        		out = &std::cout;
        	} 
        	else
        	{
        		 fout.open(where);
        		 /*if(!fout.is_open()) {std::cout << "can not output" << std::endl; break;}*/
        		 
        		 out = &fout;
        	}
    		if(t==0)
    		{
			vec[i]=CreateData(input, &F0);
			   
   		}
    		else if(t==1)
    		{
		
			vec[i]=CreateData(input, &F1);
   		}
    		else  
    		{
    			*out << "\nERROR:I don't know this method" << std::endl;
    			return 0;
    		}
    		*out << "~~~~~\nsumm" << std::endl;
    		vec_summ=(*(vec[i]))+(*(vec[i]));
		vec_summ.output(*out);
		*out << "~~~~~\ncyclic shift" << std::endl;
        	vec_c= (*(vec[i]));
        	Fraction Fr;
        	Fr=vec_c[0];
       		for(size_t i=0; i<vec_c.Size()-1; i++)
        	{
            		vec_c[i]=vec_c[i+1];
        	}
        	vec_c[vec_c.Size()-1]=Fr;
        	vec_c.output(*out);
        	*out << "~~~~~\nshift+summ" << std::endl;
        	vec_summ=vec_summ + vec_c;
        	vec_summ.output(*out); 
        	*out << "~~~~~\ntask"  << std::endl;
    		vec[i]->output(*out);
    		if(fout.is_open())
    		{
    			fout.close();
    		}
    	}
    	input.close();
	cout << "~~~~~~~~~~~~~~~~~OMP~~~~~~~~~~~~~~~" << endl;
	size_t j;
    
	for (size_t j = 0; j < N; j ++)
	{
        size_t sizze=vec[0]->Size();
         array[j] = new Vector0(sizze);
         if(j%2)
         *array[j]=*vec[0];
         else *array[j]=*vec[1];
         
    }
    
	//auto start = chrono::system_clock::now();
        Vector0 sum1 = *array[0], sum2 = *array[N/4], sum3 = *array[N/2], sum4 = *array[3*N/4];
    	Vector0 move1 = *array[3*N/4 - 1], move2 = *array[N/2 - 1], move3 = *array[N/4 - 1], move4 = *array[N - 1];
    	auto start = chrono::system_clock::now();
        
        
        for(j=1;j<N; j++)
            sum1 = sum1 + *array[j];
        
        for (j = N - 1; j > 0; j--)
        	*array[j] = *array[j-1];
    	*array[0] = move4;
    	
    	auto end = chrono::system_clock::now();
    	
    	sum1.output(cout);
	int elapsed_ms = static_cast<int>(chrono::duration_cast<chrono::milliseconds>(end-start).count());
	
	cout << "time no paralel: " << elapsed_ms << " ms\n";
	
	sum1 = *array[0];
        
        auto start1 = chrono::system_clock::now();
        
    	#pragma omp parallel sections  private(j) shared(sum1,sum2,sum3,sum4)
    	//#pragma omp parallel sections  private(j) shared(sum1)
{
    
    
        /*#pragma omp section
        for(j=1;j<N; j++)
            sum1 = sum1 + *array[j];*/
    	//Sum
    	#pragma omp section
        {
    	for (j = 1; j < N/4; j ++)
        	sum1 = sum1 + *array[j];
        }
    	#pragma omp section
    	{
    	for (j = N/4 + 1; j < N/2; j ++)
        	sum2 = sum2 + *array[j];
        }
    	#pragma omp section
    	{
    	for (j = N/2 + 1; j < 3*N/4; j ++)
        	sum3 = sum3 + *array[j];
        }
    	#pragma omp section
    	{
    	for (j = 3*N/4 + 1; j < N; j ++)
        	sum4 = sum4 + *array[j];
        }
}
	
    	sum1 = sum1 + sum2 + sum3 + sum4;
    	//Shift
    	#pragma omp parallel sections  private(j)
	{
    	#pragma omp section
    	{
    	for (j = N - 1; j > 3*N/4; j--)
        	*array[j] = *array[j-1];
    	*array[3*N/4] = move1;
    	}
        #pragma omp section
        {
        for (j = 3*N/4 - 1; j > N/2; j--)
            *array[j] = *array[j-1];
        *array[N/2] = move2;
        }
    	#pragma omp section
    	{
    	for (j = N/2 - 1; j > N/4; j--)
        	*array[j] = *array[j-1];
    	*array[N/4] = move3;
    	}
    	#pragma omp section
    	{
    	for (j = N/4 - 1; j > 0; j--)
        	*array[j] = *array[j-1];
    	*array[0] = move4;
    	}
    }
	
	
	
	auto end1 = chrono::system_clock::now();
	sum1.output(cout);
	int elapsed_ms1 = static_cast<int>(chrono::duration_cast<chrono::milliseconds>(end1-start1).count());
    	cout << "time: " << elapsed_ms1 << " ms\n";
	// #pragma omp section
	
        for(size_t i=0; i<N; i++)
    	{
    		delete array[i];
    	}
    	//delete [] array;
    	
    	for(size_t i=0; i<file_size; i++)
    	{
    		delete vec[i];
    	}
    	delete [] vec;
        delete [] array;
    	}
	return 0;
}

