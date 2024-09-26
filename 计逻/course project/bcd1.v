`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:10:13 12/25/2023 
// Design Name: 
// Module Name:    bcd1 
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
module bcd1(a,b,c,cin,cout);
	input [3:0] a,b;
	output [3:0] c;
	input cin;
	output cout;

	wire [4:0] sum;
	assign sum = {1'b0,a} + {1'b0,b} + {4'b0,cin};
	assign {cout,c} = (sum > 5'd9) ? sum + 5'd6 : sum;
endmodule