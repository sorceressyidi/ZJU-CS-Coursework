`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:23:05 12/24/2023 
// Design Name: 
// Module Name:    KeyBoard 
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
module KeyBoard(
	input clk,		//输入时钟信号
	input ps2_clk, //PS2时钟信号
	input ps2_data,//PS2数据信号
	output [1:0] key//输出键盘状态
);
	//定义键盘状态
	localparam NoKey=2'b00;
	localparam Up=2'b01;
	localparam Down=2'b10;
	localparam OtherKey=2'b11;
	//PS2接口实例化
	wire ready,overflow;
	wire [7:0] raw_data;
	reg [7:0] last_raw,data;
	ps2 m0(clk,1'b1,ps2_clk,ps2_data,1'b0,raw_data,ready,overflow);
	always@(posedge clk)begin
		if(ready&&raw_data!=8'he0)begin
			if(last_raw==8'hf0)
				data<=8'h00;
			else if(raw_data!=8'hf0)
				data<=raw_data;
			last_raw<=raw_data;
		end
	end
	//判断键盘状态
	assign key=(data==8'h00)?NoKey:
				  (data==8'h1d||data==8'h43||data==8'h75||data==8'h29)?Up:
				  (data==8'h1b||data==8'h42||data==8'h72)?Down:
				  OtherKey;
endmodule
