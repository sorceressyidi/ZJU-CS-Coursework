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
	input clk, clrn, // ����ʱ�ӡ������ź�
	input ps2_clk, ps2_data, // PS/2 ʱ�Ӻ������ź�
	input rdn, // �������ź�
	output [7:0] data, // ��������ź�
	output ready, // ��������ź�
	output overflow // �������ź�
);
	reg overflow; // FIFO �����־
	reg [3:0] count; // PS/2 ����λ������
	reg [9:0] buffer; // �洢 PS/2 ���ݵĻ���Ĵ���
	reg [7:0] fifo[7:0]; // ���� FIFO
	reg [2:0] w_ptr, r_ptr; // FIFO д��Ͷ�ȡָ��
	reg [2:0] ps2_clk_sync; // ͬ�� PS/2 ʱ�ӵļĴ���

	// ͬ�� PS/2 ʱ���ź�
	always @(posedge clk) begin
		ps2_clk_sync <= {ps2_clk_sync[1:0], ps2_clk};
	end

	wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1]; // ������ PS/2 ʱ�������ؽ������ݲ���

	// ���߼�
	always @(posedge clk) begin
		if (clrn == 0) begin
		// ��λ
			count <= 0;
			w_ptr <= 0;
			r_ptr <= 0;
			overflow <= 0;
		end else if (sampling) begin
			if (count == 4'd10) begin
				if ((buffer[0] == 0) && (ps2_data) && (~buffer[9:1])) begin
				// �����ʼλ��ֹͣλ��У��λ��������ɨ������� FIFO
					fifo[w_ptr] <= buffer[8:1];
					w_ptr <= w_ptr + 3'b1;
					overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
				end
				count <= 0; // Ϊ��һ��ɨ������׼��
			end else begin
				buffer[count] <= ps2_data; // �洢 PS/2 ����
				count <= count + 3'b1; // ���� PS/2 ����λ
			end
		end
		if (!rdn && ready) begin
			// ��ȡ���󣬸��¶�ָ�룬��������־
			r_ptr <= r_ptr + 3'b1;
			overflow <= 0;
		end
	end
	assign ready = (w_ptr != r_ptr); // ָʾ FIFO �Ƿ����
	assign data = fifo[r_ptr]; // �� FIFO �ж�ȡ�������
endmodule
