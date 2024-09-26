`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:06:44 12/25/2023 
// Design Name: 
// Module Name:    BCD 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module BCD(a,b,c);
	input [15:0] a,b;
	output [15:0] c;

	wire [3:0] carry;
	bcd1 m0(a[3:0],b[3:0],c[3:0],1'b0,carry[0]);
	bcd1 m1(a[7:4],b[7:4],c[7:4],carry[0],carry[1]);
	bcd1 m2(a[11:8],b[11:8],c[11:8],carry[1],carry[2]);
	bcd1 m3(a[15:12],b[15:12],c[15:12],carry[2],carry[3]);
	
endmodule
