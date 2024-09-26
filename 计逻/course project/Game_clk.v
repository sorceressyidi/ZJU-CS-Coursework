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
	input clk, // ����ʱ���ź�
	input rst, // ��λ�ź�
	output reg clk_out, // �����Ϸʱ���ź�
	output reg [8:0] minEmpty // �����С����ʱ��
);

	reg [17:0] tick = 0; // ��Ϸʱ�Ӽ�����
	reg [17:0] maxtick = 150000; // ��Ϸʱ��������ֵ���൱�� 0.5 �� gameclk ����
	reg [11:0] maxcnt = 0; // �����������ڵ�����Ϸʱ��Ƶ��

	always @(posedge clk) begin
		if (rst) begin
		// ��λ����
			tick <= 0;
			maxtick <= 150000;
			maxcnt <= 0;
			clk_out <= ~clk_out; // �������Ƶ��
			minEmpty <= 240; // ��ʼ��С����ʱ��
		end else if (tick < maxtick) begin
		// ��Ϸʱ��δ�ﵽ������ֵʱ������������
			tick <= tick + 1;
		end else begin
			// ��Ϸʱ�Ӽ����ﵽ���ֵʱ�Ĵ����߼�
			tick <= 0;
			if (maxcnt < 3000) begin
			// ��һ�������ڵ���������
			maxcnt <= maxcnt + 1;
			end else begin
				// �����ﵽ��ֵʱ�����ü�������������Ϸʱ��Ƶ��
				maxcnt <= 0;
				if (maxtick > 80000) begin
				// ��ֹ���ȼ�����Ϸʱ��
					maxtick <= maxtick - 3555; // ������Ϸʱ��Ƶ��
					minEmpty <= 36_000_000 / maxtick; // ������С����ʱ��
				end
			end
			clk_out <= ~clk_out; // �л���Ϸʱ���ź�
		end
	end
endmodule
