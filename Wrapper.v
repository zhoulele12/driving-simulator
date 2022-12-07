`timescale 1ns / 1ps
/**
 * 
 * READ THIS DESCRIPTION:
 *
 * This is the Wrapper module that will serve as the header file combining your processor, 
 * RegFile and Memory elements together.
 *
 * This file will be used to generate the bitstream to upload to the FPGA.
 * We have provided a sibling file, Wrapper_tb.v so that you can test your processor's functionality.
 * 
 * We will be using our own separate Wrapper_tb.v to test your code. You are allowed to make changes to the Wrapper files 
 * for your own individual testing, but we expect your final processor.v and memory modules to work with the 
 * provided Wrapper interface.
 * 
 * Refer to Lab 5 documents for detailed instructions on how to interface 
 * with the memory elements. Each imem and dmem modules will take 12-bit 
 * addresses and will allow for storing of 32-bit values at each address. 
 * Each memory module should receive a single clock. At which edges, is 
 * purely a design choice (and thereby up to you). 
 * 
 * You must change line 36 to add the memory file of the test you created using the assembler
 * For example, you would add sample inside of the quotes on line 38 after assembling sample.s
 *
 **/

module Wrapper (clock, reset, ACL_MISO, ACL_MOSI, ACL_SCLK, ACL_CSN, LED,SEG,DP,AN, JA, JB);
	input clock, reset, ACL_MISO;
	
	output ACL_MOSI, ACL_SCLK, ACL_CSN, DP;
	output[14:0] LED;
	output [4:1] JA;
	input[4:1] JB;
	output[6:0] SEG;
	output[7:0] AN;
   
    wire [31:0] accelData, readAccelDataA, readAccelDataB, fullAccelData;
    wire rwe, mwe, w_4MHz, not_rst;
	wire[4:0] rd, rs1, rs2;
	wire[31:0] instAddr, instData, 
		rData, regA, regB,
		memAddr, memDataIn, memDataOut;
    wire[14:0] acl_data;
    
    assign not_rst = ~reset;

	// ADD YOUR MEMORY FILE HERE
	localparam INSTR_FILE = "C:/Users/cz169/Downloads/driving-simulator-main/driving-simulator-main/mult";
//	localparam INSTR_FILE = "C:/Users/cz169/Desktop/accel";
	wire [31:0] PCprobe;
	// Main Processing Unit
	processor CPU(.clock(w_4MHz), .reset(not_rst), 
								
		// ROM
		.address_imem(instAddr), .q_imem(instData),
									
		// Regfile
		.ctrl_writeEnable(rwe),     .ctrl_writeReg(rd),
		.ctrl_readRegA(rs1),     .ctrl_readRegB(rs2), 
		.data_writeReg(rData), .data_readRegA(regA), .data_readRegB(regB), 
		.PCprobe(PCprobe),
									
		// RAM
		.wren(mwe), .address_dmem(memAddr), 
		.data(memDataIn), .q_dmem(memDataOut)); 
	
	// Instruction Memory (ROM)
	ROM #(.MEMFILE({INSTR_FILE, ".mem"}))
	InstMem(.clk(w_4MHz), 
		.addr(instAddr[11:0]), 
		.dataOut(instData));
	
	wire [31:0] PCregister;
	// Register File
	regfile RegisterFile(.clock(w_4MHz), 
		.ctrl_writeEnable(rwe), .ctrl_reset(not_rst), 
		.ctrl_writeReg(rd),
		.ctrl_readRegA(rs1), .ctrl_readRegB(rs2), .data_writeRegAccel(fullAccelData), 
		.data_writeReg(rData), .data_readRegA(regA), .data_readRegB(regB), .data_readRegAccelA(readAccelDataA), .data_readRegAccelB(readAccelDataB),
		.PCprobe(PCprobe),.PCregister(PCregister));
						
	// Processor Memory (RAM)
	RAM ProcMem(.clk(w_4MHz), 
		.wEn(mwe), 
		.addr(memAddr[11:0]), 
		.dataIn(memDataIn), 
		.dataOut(memDataOut));
		
	 iclk_gen clock_generation(
    .clk100mhz(clock),
    .clk_4mhz(w_4MHz)
    );
    
    spi_master master(
    .iclk(w_4MHz),
    .miso(ACL_MISO),
    .sclk(ACL_SCLK),
    .mosi(ACL_MOSI),
    .cs(ACL_CSN),
    .Y(accelData),
    .outData(fullAccelData),
    .acl_data(acl_data)
    );
    
    seg7_control display_control(
    .displayDataA(readAccelDataA),
    .displayDataB(readAccelDataB),
    .displayDataC(PCregister),
    .clk100mhz(clock),
    .acl_data(acl_data),
    .seg(SEG),
    .dp(DP),
    .an(AN)
    );
    assign LED[0] = JB[1];
    assign LED[1] = fullAccelData[0] & ~fullAccelData[1] & ~fullAccelData[2] & ~fullAccelData[3];
    assign LED[2] = ~fullAccelData[0] & fullAccelData[1] & ~fullAccelData[2] & ~fullAccelData[3];
    assign LED[3] = fullAccelData[0] & fullAccelData[1] & ~fullAccelData[2] & ~fullAccelData[3];
    assign LED[4] = ~fullAccelData[0] & ~fullAccelData[1] & fullAccelData[2] & ~fullAccelData[3];
    assign LED[5] = fullAccelData[0] & ~fullAccelData[1] & fullAccelData[2] & ~fullAccelData[3];
    assign LED[6] = ~fullAccelData[0] & fullAccelData[1] & fullAccelData[2] & ~fullAccelData[3];
    assign LED[7] = fullAccelData[0] & fullAccelData[1] & fullAccelData[2] & ~fullAccelData[3];
    assign LED[8] = ~fullAccelData[0] & ~fullAccelData[1] & ~fullAccelData[2] & fullAccelData[3];
    assign LED[9] = fullAccelData[0] & ~fullAccelData[1] & ~fullAccelData[2] & fullAccelData[3];
    assign LED[10] = ~fullAccelData[0] & fullAccelData[1] & ~fullAccelData[2] & fullAccelData[3];
    assign LED[11] = fullAccelData[0] & fullAccelData[1] & ~fullAccelData[2] & fullAccelData[3];
    assign LED[12] = ~fullAccelData[0] & ~fullAccelData[1] & fullAccelData[2] & fullAccelData[3];
    assign LED[13] = fullAccelData[0] & ~fullAccelData[1] & fullAccelData[2] & fullAccelData[3];
    assign LED[14] = ~fullAccelData[0] & fullAccelData[1] & fullAccelData[2] & fullAccelData[3];
    assign LED[15] = fullAccelData[0] & fullAccelData[1] & fullAccelData[2] & fullAccelData[3]; 
    
    assign JA[1] = fullAccelData[0];
    assign JA[2] = fullAccelData[1];
    assign JA[3] = fullAccelData[2];
    assign JA[4]= fullAccelData[3];
    
//   ila_1 debug(.clk(w_4MHz), .probe0(regB), .probe1(rData), .probe2(regA), .probe3(PCregister));

endmodule
