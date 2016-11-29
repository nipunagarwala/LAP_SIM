int LAPU::SYRK(int Global_index){
	while (1){
		switch(SYRK_Current_State){
			case SYRK_Flush0:
				SYRK_Next_State = SYRK_Flush1;
			break;
			case SYRK_Flush1:
				SYRK_Next_State = SYRK_MAC_Flush;
			break;
			case SYRK_MAC_Flush:
				Latency_Counter_Next = Lateny_Counter_Curr+1;
				if (Latency_Counter_Curr < (FMA_Latency - 1)){
					SYRK_Next_State = SYRK_MAC_Flush;
				}
				else{
					SYRK_Next_State = SYRK_End;
					Latency_Counter_Next = 0;
				}
			break;
			case SYRK_End:
				if Last_Sending == LAPU_Size{
					done = true;
				}
				Last_Sending++;
				//Reset all the counters
				Kc_Counter_Next = 0;
				Kc_Counter_Curr = 0;
				Mc_Counter_Next = 0;
				Mc_Counter_Curr = 0;
				N_Counter_Curr = 0;
				N_Counter_Next = 0;
			break;
		}
	}
	return 0;
}
