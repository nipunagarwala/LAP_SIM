#include "LAPU.h"

using namespace std;



int LAPU::Matmul_Kernel(int Global_index){

	// Define a new counter to keep track of initial state of Kernel Ap_Counter

	startCntr = 0;
	while (1){
		switch (Matmul_Current_State){

			case Syrk_MAC_BC:

	/* 1. (i-4) Perform MAC on the values present in registers

	   2. (i-3) Read BC value into register

	   3. (i-2) BC 

	   4. (i-1) Prepare for BC

	   5. i  Pull another row of A_{k} from memory using
	   		address generation and store in memory


	   	On the side, Memory A stores the necessary
	   	A_{j}^{T} that is being used for the column major
	   	version of SYRK. It is updated periodically, when
	   	the column shifts to the next one, then becoming
	   	A_{j+1}^{T}.

	   	Memory B stores the current block of A being used
	   	to get the particular 4x4 C_{ij} block. It has dual
	   	buffering and reads and writes A_{c} values
	   	constantly, due to its streaming nature.


	*/

			Matmul_Next_State=Matmul_MAC_BC;

			Kc_Counter_Next=(Kc_Counter_Curr+1) % Kernel_Size;
			if (Kc_Counter_Curr== (Kernel_Size -1)){
				Mc_Counter_Next=(Mc_Counter_Curr+LAPU_Size)% Kernel_Size;
				if (Mc_Counter_Curr==(Kernel_Size-LAPU_Size)){
					N_Counter_Next=(N_Counter_Curr+LAPU_Size)% Panel_Size;
					if (N_Counter_Curr== (Panel_Size -LAPU_Size)){
                  		Ap_Counter_Next = (Ap_Counter_Curr + 1)%NumofKernel;
                  		if (Ap_Counter_Curr == NumofKernels - 1){
							startCntr += 1
							if(startCntr == NumofKernels - 1) {
								Syrk_Next_State = Syrk_flush_0
							} else {
								Ap_Counter_Next = 0
							}
                  		}
                	}

				}

			}

			break;
		}
	}
	return 0;
}


int PE::Execute_Matmul (int Global_index, int Bpj_Counter, int Mc, int Kc, int Ap_Counter, int Matmul_Current_State,int Latency_Counter){

	switch(Syrk_Current_State){

		case 5: // SYRK MAC and BC
			if ((Ap_Counter%2)==0) Fill_Lower_Buffer_A = false;

			else Fill_Lower_Buffer_A = true;

      		if (!Fill_Lower_Buffer_A){
      			if(Bpj_Counter!=0 && Mc==0 && Kc==0){ 
      				 Address_A_New = 1; 
        		}

      		} else {
      			if(Bpj_Counter!=0 && Mc==0 && Kc==0) //repeat for every starting computation of N
        			//The same reason as above
        		Address_A_New = (Kernel_Size * Kernel_Size)/(LAPU_Size*LAPU_Size) + 1;
      		}
      	break;

    }


}


















