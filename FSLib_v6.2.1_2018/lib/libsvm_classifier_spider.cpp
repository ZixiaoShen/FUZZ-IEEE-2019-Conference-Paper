/* $Revision: 1.10 $ */
// Automatically generated by MATLAB Project Wizard version 1.0

//
// This is the gateway routine for a MATLAB Math/Graphics Library-based
// C MATLAB MEX File.

#include <memory.h>

#include <mex.h>
#include <mexarg.h>



char Versionstring[]="2.81";



#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

#include "svm.h"

//
struct svm_model
{
	svm_parameter param;	// parameter
	int nr_class;		// number of classes, = 2 in regression/one class svm
	int l;			// total #SV
	svm_node **SV;		// SVs (SV[l])
	double **sv_coef;	// coefficients for SVs in decision functions (sv_coef[n-1][l])
	double *rho;		// constants in decision functions (rho[n*(n-1)/2])
	
	// for classification only
	
	int *label;		// label of each class (label[n])
	int *nSV;		// number of SVs for each class (nSV[n])
				// nSV[0] + nSV[1] + ... + nSV[n-1] = l
	// XXX
	int free_sv;		// 1 if svm_model is created by svm_load_model
				// 0 if svm_model is created by svm_train
};


double *balanced_ridges=NULL;
double *Custom_Kernel;
int Custom_M,Custom_N;


extern "C"{
	
/*
-s svm_type : set type of SVM (default 0)
0 -- C-SVC
1 -- nu-SVC
2 -- one-class SVM
3 -- epsilon-SVR
4 -- nu-SVR
-t kernel_type : set type of kernel function (default 2)
0 -- linear: u'*v
1 -- polynomial: (gamma*u'*v + coef0)^degree
2 -- radial basis function: exp(-gamma*|u-v|^2)
3 -- sigmoid: tanh(gamma*u'*v + coef0)
-d degree : set degree in kernel function (default 3)
-g gamma : set gamma in kernel function (default 1/k)
-r coef0 : set coef0 in kernel function (default 0)
-c cost : set the parameter C of C-SVC, epsilon-SVR, and nu-SVR (default 1)
-n nu : set the parameter nu of nu-SVC, one-class SVM, and nu-SVR (default 0.5)
-p epsilon : set the epsilon in loss function of epsilon-SVR (default 0.1)
-m cachesize : set cache memory size in MB (default 40)
-e epsilon : set tolerance of termination criterion (default 0.001)
-h shrinking: whether to use the shrinking heuristics, 0 or 1 (default 1)
-wi weight: set the parameter C of class i to weight*C, for C-SVC (default 1)
-v n: n-fold cross validation mode
	*/
	
	
	void mexFunction(
		int nlhs,              // Number of left hand side (output) arguments
		mxArray *plhs[],       // Array of left hand side arguments
		int nrhs,              // Number of right hand side (input) arguments
		const mxArray *prhs[]  // Array of right hand side arguments
		)
		
		/*
		prhs =  [X,Y , s , t , d , g ,r , c , n ,p , m ,e ,h ,wi,v];
		*/
	{
		
		int elements,max_index,i,j;
		
		struct svm_parameter param;		// set by parse_command_line
		struct svm_problem prob;		// set by read_problem
		struct svm_model *model;
		struct svm_node *x_space;
		
        mexarg arg;
        
		if( !(arg.require(nrhs,prhs,"C") & 
              arg.require(nrhs,prhs,"X") & 
              arg.require(nrhs,prhs,"Y") & 
              arg.require(nrhs,prhs,"svm_type") & 
              arg.require(nrhs,prhs,"kerneltype") & 
              arg.require(nrhs,prhs,"degree") & 
              arg.require(nrhs,prhs,"gamma") & 
              arg.require(nrhs,prhs,"coef0") & 
              arg.require(nrhs,prhs,"nu") & 
              arg.require(nrhs,prhs,"cachesize") & 
              arg.require(nrhs,prhs,"C") & 
              arg.require(nrhs,prhs,"eps") & 
              arg.require(nrhs,prhs,"p") & 
              arg.require(nrhs,prhs,"shrinking")
            ))
		{		
			mexPrintf("Libsvm interface. Used Libsvm version : %s\n",Versionstring);
			mexPrintf("Usage: [alpha,xSV,bias0]="\
            "libsvm_classifier_spider({'X',doublematrix},{'Y',doublematrix},\n"\
            "{'C',scalar},{'kerneltype',scalar},\n{'degree',scalar},{'gamma',scalar},\n"\
            " {'coef0',scalar},{'nu',scalar},{'cachesize',scalar},\n"\
            "{'eps',scalar},{'shrinking',scalar},{'p',scalar},{'balanced_ridge', optional scalar},{'kmatrix',K})");
			return;
		}
        
        mxArray *customK;
        if (arg.getmatrix(nrhs,prhs,"kmatrix",&customK))
      	{
			
			
			Custom_M = mxGetM( customK);
			Custom_N = mxGetN( customK);
			
			mexPrintf("Using Custom Kernel %d %d\n",Custom_M,Custom_N);
			
            if(0)
            {
                // really stupid!!!
                Custom_Kernel = Malloc( double, Custom_M*Custom_N);
                if ( Custom_Kernel)
                    memcpy( Custom_Kernel, mxGetData( customK), Custom_M*Custom_N*sizeof( double));
                else
                {
                    mexErrMsgTxt("No Memory for Kernel Matrix");
                    return;
                }
           }
           else
           
            Custom_Kernel = mxGetPr(customK);
               
		}
        
     
       
        mxArray *x,*y;
        arg.getmatrix(nrhs,prhs,"X",&x);
        arg.getmatrix(nrhs,prhs,"Y",&y);
        double *xdata=mxGetPr(x);
        double *ydata=mxGetPr(y);
       
        double svm_type,kernelType,degree,gamma,coef0,nu,cachesize,C,eps,p,shrinking;
        double balanced_ridge;
        
        arg.getscalar(nrhs,prhs,"C",&C);
        arg.getscalar(nrhs,prhs,"svm_type",&svm_type);
        arg.getscalar(nrhs,prhs,"kerneltype",&kernelType);
        arg.getscalar(nrhs,prhs,"degree",&degree);
        arg.getscalar(nrhs,prhs,"gamma",&gamma);
        arg.getscalar(nrhs,prhs,"coef0",&coef0);
        arg.getscalar(nrhs,prhs,"nu",&nu);
        arg.getscalar(nrhs,prhs,"cachesize",&cachesize);
        arg.getscalar(nrhs,prhs,"eps",&eps);
        arg.getscalar(nrhs,prhs,"p",&p);
        arg.getscalar(nrhs,prhs,"shrinking",&shrinking);
        
        
        balanced_ridges=Malloc(double,mxGetM(x));
        memset(balanced_ridges,0,sizeof(double)*mxGetM(x));
        
        if( arg.getscalar(nrhs,prhs,"balanced_ridge",&balanced_ridge))
        {
            double number=mxGetM(x);
            double  ypos=0;
            double  yneg=0;
            int iter;
            for(iter=0;iter<number;iter++)
                (ydata[iter]>0)?ypos++:yneg++;
            
            for(iter=0;iter<number;iter++)
                 if(ydata[iter]>0)
                     balanced_ridges[iter]=(ypos/number)*balanced_ridge;
                 else
                     balanced_ridges[iter]=(yneg/number)*balanced_ridge;
        }
        
        
		//return;
		
		
		memset(&param,0,sizeof(param)) ;
        
		param.cache_size=cachesize;
		param.C=C;
		param.eps=eps;
		param.p=p;
		param.shrinking=(int)shrinking;
		param.nr_weight=0;
		param.nu=nu;
		param.coef0=coef0;
		param.gamma=gamma;
		param.degree=degree;
		param.kernel_type=(int)kernelType;
		param.svm_type=(int)svm_type;
		
		// prepare libsvm data structure
		prob.l=mxGetM(x);
		elements = mxGetN(x);
		
//		mexPrintf("%d %d %f\n",prob.l,elements,nu);
		
		// alloc memory for data structure
		prob.y = Malloc(double,prob.l);
		prob.x = Malloc(struct svm_node *,prob.l);
		x_space = Malloc(struct svm_node,prob.l*(elements+1));
		
		max_index = 0;
		j=0;
		
		max_index = 0;
		j=0;
		
		for(i=0;i<prob.l;i++)
		{
			
			prob.x[i] = &x_space[i*(elements+1)];									
			prob.y[i] = ydata[i];
			
			for ( j=0; j < elements;j++)
			{
				
				x_space[i*(elements+1)+j].index=j+1;	
				x_space[i*(elements+1)+j].value=xdata[j*prob.l +i];
				
			}	
			
			x_space[i*(elements+1)+elements].index=-1;
			x_space[i*(elements+1)+elements].value=0;
		}	

        
		model = svm_train(&prob,&param);
		
		
		if(nlhs>0)	
		{	
                        plhs[0]=mxCreateDoubleMatrix(model->l,1,mxREAL);
                        double *p=mxGetPr(plhs[0]);
                        
                        for (int i=0;i<model->l;i++)
                            p[i]= model->sv_coef[0][i];
                        
                        //mexPrintf("alpha copied\n");
			
		}	
		
		if(nlhs>1)	
		{
			plhs[1]=mxCreateDoubleMatrix(model->l,elements,mxREAL);		
			double *xsv=mxGetPr(plhs[1]);
			//mexPrintf("%d %d\n",model->l,elements);
			for(i=0;i<model->l;i++)
			{
				
				for(j=0;j<elements;j++)
					xsv[j*model->l+i] = model->SV[i][j].value;
               
        	}
                        
        	
		}
		
		if(nlhs>2)	
		{
			plhs[2]=mxCreateDoubleMatrix(1,1,mxREAL);
                        double *b=mxGetPr(plhs[2]);
			 *b=-model->rho[0];
                        //mexPrintf("b0 copied\n");
		}
		
		if(nlhs>3)	
		{
            plhs[3]=mxCreateDoubleMatrix(1,1,mxREAL);
			*mxGetPr(plhs[3]) =param.C;
		}
		

                 //mexPrintf("%returning\n");

		svm_destroy_model(model);
		
		// free memory 
		free(prob.y);
		free(prob.x);	
		free(x_space);
           
        free(balanced_ridges);
	}
	
}
