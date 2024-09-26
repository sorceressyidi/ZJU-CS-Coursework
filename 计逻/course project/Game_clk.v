`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:08:52 12/24/2023 
// Design Name: 
// Module Name:    Game_clk 
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
module Game_clk(
	input clk, // 输入时钟信号
	input rst, // 复位信号
	output reg clk_out, // 输出游戏时钟信号
	output reg [8:0] minEmpty // 输出最小空闲时间
);

	reg [17:0] tick = 0; // 游戏时钟计数器
	reg [17:0] maxtick = 150000; // 游戏时钟最大计数值，相当于 0.5 个 gameclk 周期
	reg [11:0] maxcnt = 0; // 计数器，用于调整游戏时钟频率

	always @(posedge clk) begin
		if (rst) begin
		// 复位条件
			tick <= 0;
			maxtick <= 150000;
			maxcnt <= 0;
			clk_out <= ~clk_out; // 产生最高频率
			minEmpty <= 240; // 初始最小空闲时间
		end else if (tick < maxtick) begin
		// 游戏时钟未达到最大计数值时，递增计数器
			tick <= tick + 1;
		end else begin
			// 游戏时钟计数达到最大值时的处理逻辑
			tick <= 0;
			if (maxcnt < 3000) begin
			// 在一定周期内递增计数器
			maxcnt <= maxcnt + 1;
			end else begin
				// 计数达到阈值时，重置计数器并调整游戏时钟频率
				maxcnt <= 0;
				if (maxtick > 80000) begin
				// 防止过度加速游戏时钟
					maxtick <= maxtick - 3555; // 增加游戏时钟频率
					minEmpty <= 36_000_000 / maxtick; // 计算最小空闲时间
				end
			end
			clk_out <= ~clk_out; // 切换游戏时钟信号
		end
	end
endmodule
