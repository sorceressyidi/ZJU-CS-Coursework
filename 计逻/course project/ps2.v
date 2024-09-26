`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:58:21 12/24/2023 
// Design Name: 
// Module Name:    ps2 
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
module ps2(
	input clk, clrn, // 输入时钟、清零信号
	input ps2_clk, ps2_data, // PS/2 时钟和数据信号
	input rdn, // 读请求信号
	output [7:0] data, // 输出数据信号
	output ready, // 输出就绪信号
	output overflow // 输出溢出信号
);
	reg overflow; // FIFO 溢出标志
	reg [3:0] count; // PS/2 数据位计数器
	reg [9:0] buffer; // 存储 PS/2 数据的缓冲寄存器
	reg [7:0] fifo[7:0]; // 数据 FIFO
	reg [2:0] w_ptr, r_ptr; // FIFO 写入和读取指针
	reg [2:0] ps2_clk_sync; // 同步 PS/2 时钟的寄存器

	// 同步 PS/2 时钟信号
	always @(posedge clk) begin
		ps2_clk_sync <= {ps2_clk_sync[1:0], ps2_clk};
	end

	wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1]; // 用于在 PS/2 时钟上升沿进行数据采样

	// 主逻辑
	always @(posedge clk) begin
		if (clrn == 0) begin
		// 复位
			count <= 0;
			w_ptr <= 0;
			r_ptr <= 0;
			overflow <= 0;
		end else if (sampling) begin
			if (count == 4'd10) begin
				if ((buffer[0] == 0) && (ps2_data) && (~buffer[9:1])) begin
				// 检测起始位、停止位和校验位，将键盘扫描码存入 FIFO
					fifo[w_ptr] <= buffer[8:1];
					w_ptr <= w_ptr + 3'b1;
					overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
				end
				count <= 0; // 为下一个扫描码做准备
			end else begin
				buffer[count] <= ps2_data; // 存储 PS/2 数据
				count <= count + 3'b1; // 计数 PS/2 数据位
			end
		end
		if (!rdn && ready) begin
			// 读取请求，更新读指针，清除溢出标志
			r_ptr <= r_ptr + 3'b1;
			overflow <= 0;
		end
	end
	assign ready = (w_ptr != r_ptr); // 指示 FIFO 是否就绪
	assign data = fifo[r_ptr]; // 从 FIFO 中读取数据输出
endmodule
