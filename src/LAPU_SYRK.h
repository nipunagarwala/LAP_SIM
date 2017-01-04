/*
   Copyright (c) 2010-2015, Ardavan Pedram and The University of Texas at Austin
   All rights reserved.
   
   This file is part of LAP_SIM and is under the BSD 3-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-3-Clause
*/

#ifndef LAPU_SYRK_H_
#define LAPU_SYRK_H_

#include "Parameters.h"
#include "Inv_Sqrt.h"
#include "PE_SYRK.h"
#include "IO.h"

class LAPU
{
public:
	LAPU();
	virtual ~LAPU();



	int Matmul_Kernel(int Global_index);
	int Syrk_Kernel(int Global_index, double **& A, bool init);

	int Cycle();
	int Return_Cycle_Count();
	int Return_LAPU_Power();

/*	int Execute( LAPU_Function Function, int Global_index, int Trsm_index);
	int Cycle();
*/

	int Drive_Buses();

	int Initialize_Mem( double ** Input_matrix, int row_number, int column_number, int offset);

	int Flush_Mem(double **& Input_matrix, int row_number, int column_number, int offset); //TODO who makes decision about the offset/?

	int Initialize_Mem_New( double ** Input_matrix, int row_number, int column_number, int offset, char matr);

	int Flush_Mem_New(double **& Input_matrix, int row_number, int column_number, int offset, char matr); //TODO who makes decision about the offset/?
	
  	int Assign_input_Matrix( double **& matrix_A, double **& matrix_B, double **& matrix_C);

	int Dump_PE_Registers(int row, int column);

	int Dump_All_PE_Registers();

	int Dump_PE_ALU(int row, int column, ALU_op operation_type);

	int Dump_All_PE_ALUs(ALU_op operation_type);


	int Dump_Row_Buses();
	int Dump_Column_Buses();


	int Dump_Matmul_SMachine();
	int Dump_Syrk_SMachine();

	int Dump_Sqrt_Unit();


private:






	enum Matmul_States { Matmul_Init, Matmul_FetchB, Matmul_FetchA, Matmul_BC0, Matmul_BC, Matmul_MAC_BC, Matmul_MAC_Flush, Matmul_End} Matmul_Current_State, Matmul_Next_State;
	enum Syrk_States { Syrk_BC0, Syrk_BC1, Syrk_BC2, Syrk_MAC_BC, Syrk_MAC_Flush0, Syrk_MAC_Flush1, Syrk_MAC_Flush2} Syrk_Current_State, Syrk_Next_State;






	//TODO do I need different State enums for different types of operatons?
	int Size;
	int i,j;
	PE  ** PE_Array;

	double ** Matrix_A;
	double ** Matrix_B;
	double ** Matrix_C;

	int Counter_Curr;
	int Counter_Next;

	int Latency_Counter_Curr;
	int Latency_Counter_Next;
 // Added for Matmul

	int Mc_Counter_Curr;
	int Mc_Counter_Next;

	int Kc_Counter_Curr;
	int Kc_Counter_Next;

	int N_Counter_Curr;
	int N_Counter_Next;

  int Ap_Counter_Curr;
  int Ap_Counter_Next;

  int Last_Sending;
  bool done;

///


	bool State_Start;

	int Cycles_Passed;

	double * Row_Buses_Write;
	double * Row_Buses_Read;

	double * Column_Buses_Write;
	double * Column_Buses_Read;

	Inv_Sqrt * Sqrt_Unit;
	IO * Mem_IF;

	int LAPU_Power_Consumed;
};

#endif /* LAPU_SYRK_H_ */
