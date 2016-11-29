int PE::Execute_SYRK (int Global_index, int Bpj_Counter, int Mc, int Kc, int Ap_Counter, int SYRK_Current_State, int Latency_Counter){
	switch(SYRK_Current_State){
		case SYRK_Flush0:
			//Prepare for next cycle's A broadcast
			//Read from B because A is stored there
			Write_My_Row_Reg_Next = Local_Mem.Reg_Read_New(Address_B_New, toA);
			//Broadcast to get A^T
			//Drive row bus for PEs on the diagonal
			if (My_Column == My_Row){
				*Write_My_Row_Bus = Write_My_Row_Reg_Curr;
			}
			//MAC
			//Mc!=0, Bpj!=0, Ap!= 0 => "finished" calculating first Cout
			//Kc == FMA_Latency-1 => still need to flush out the MAC pipeline to get final Cout result
			//Finish calculating one Cout block everytime Kc resets
			//So this just checks when Cout block is done and ready to be written to memory
			if ((Kc==FMA_Latency-1)&&(Mc!=0 ||  Bpj_Counter!=0 || Ap_Counter!=0)){ 
        		Scratch_Regs_Next[3]=ALU.Execute_MAC( Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
				Write_My_Col_Reg_Next=Scratch_Regs_Next[3];
			}
			//Kc == 0 => start calculating a new Cout block -> need to load in Cin
			else if (Kc==0){ // Loading accumulator takes a cycle, and we start new panel with kc=1
				ALU.Execute_MAC( Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
				ALU.Load_Accumulator(Scratch_Regs_Curr[1]);
			}
			else{ 
        		ALU.Execute_MAC( Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
        	}
		break;
		case SYRK_Flush1:
			//Broadcast to get A^T
			//Drive row bus for PEs on the diagonal
			if (My_Column == My_Row){
				*Write_My_Row_Bus = Write_My_Row_Reg_Curr;
			}
			//MAC
			//Mc!=0, Bpj!=0, Ap!= 0 => "finished" calculating first Cout
			//Kc == FMA_Latency-1 => still need to flush out the MAC pipeline to get final Cout result
			//Finish calculating one Cout block everytime Kc resets
			//So this just checks when Cout block is done and ready to be written to memory
			if ((Kc==FMA_Latency-1)&&(Mc!=0 ||  Bpj_Counter!=0 || Ap_Counter!=0)){ 
        		Scratch_Regs_Next[3]=ALU.Execute_MAC( Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
				Write_My_Col_Reg_Next=Scratch_Regs_Next[3];
			}
			//Kc == 0 => start calculating a new Cout block -> need to load in Cin
			else if (Kc==0){ // Loading accumulator takes a cycle, and we start new panel with kc=1
				ALU.Execute_MAC( Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
				ALU.Load_Accumulator(Scratch_Regs_Curr[1]);
			}
			else{ 
        		ALU.Execute_MAC( Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
        	}
		break;
		case SYRK_MAC_Flush:
			if (Latency_Counter<(FMA_Latency-1)){
				ALU.Execute_MAC(Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
			}
			else{
				Scratch_Regs_Next[2] = ALU.Execute_MAC(Scratch_Regs_Curr[0], (*Read_My_Row_Bus));
				Write_My_Col_Reg_Next = Scratch_Regs_Next[2];
				Cout_Counter = -1;
			}
		break;
		case SYRK_End:
			if (Cout_Counter < LAPU_Size){
				if (Cout_Counter >= 0){
					if (My_Row == Cout_Counter){
						*Write_My_Col_Bus = Write_My_Col_Reg_Curr;
					}
				}
				Cout_Counter++;
			}
		break;
	}
}