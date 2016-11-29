int IO::IO_Execute_SYRK (int Global_index, int N, int Mc, int Kc, int Ap, int  Matmul_Current_State, int Latency_Counter_Curr){
	switch(SYRK_Current_State){
		case SYRK_Flush0:
			//no memory operations
		break;
		case SYRK_Flush1;
			//no memory operations
		break;
		case SYRK_MAC_Flush:
			//no memory operations but initialize counters for next state
			Cout_Counter = -2;
			last_x = Kernel_Size - LAPU_Size;
			last_y = Panel_Size - LAPU_Size;
		break;
		case SYRK_End:
			if (Cout_Counter<LAPU_Size){
				if (Cout_Counter>=0){
					for (i=0;i<LAPU_Size;i++){
						Matrix_C[last_x+ (NumofKernel-1)*Kernel_Size][last_y+i] = Read_Col_Buses[i];
					}
      	  			last_x++;
      			}
				Cout_Counter++;
			}
		break;
	}
}
