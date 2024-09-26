`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:33:09 12/17/2018 
// Design Name: 
// Module Name:    VGA 
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
module VGA(
           input clk,
			  input rst,
			  input [11:0]Din,
			  output reg[9:0]row,
			  output reg[9:0]col,
			  output reg read,
			  output reg[3:0]R,G,B,
			  output reg HS,VS
    );
	 
reg[9:0] hcnt,vcnt;                         //�м�����������
	 
always@(posedge clk or posedge rst)begin
	 if(rst) hcnt<=10'h0;                    //rstΪ1ʱ��ʼ��
	 else begin                              //ÿ��һ��ʱ�����ڣ��м�����������0-799��ѭ��
	     if(hcnt==10'd799) hcnt<=10'h0;      //��ɨ��һ��
        else hcnt<=hcnt+1;
    end
end

always@(posedge clk or posedge rst)begin
	 if(rst) vcnt<=10'h0;                    //rstΪ1ʱ��ʼ��
	 else begin                              
	     if(hcnt==10'd799) begin             //�м���ÿѭ��һ�Σ���ɨ��һ�У���������������0-525��ѭ��
           if(vcnt==10'd524)vcnt<=10'h0;
			  else vcnt<=vcnt+1;
		  end
    end
end

wire [9:0] row_addr = vcnt-10'd31;          //����������
wire [9:0] col_addr = hcnt-10'd144;         //����������
wire h_sync=hcnt>96?1:0;                    //��ͬ��
wire v_sync=vcnt>2?0:1;                     //��ͬ��

always@(posedge clk)begin
    row <=row_addr;
	 col <=col_addr;
	 HS<=h_sync;
	 VS<=v_sync;
	 read <=(hcnt>10'd144)&&(hcnt<10'd784)&&(vcnt>10'd31)&&(vcnt<10'd511);
                                            //�Ƿ�����Чλ��
    if(read)begin
	     B<=Din[11:8];                       //��ɫ�ź����
		  G<=Din[7:4];
		  R<=Din[3:0];
	 end
	 else
	 {R,G,B}<=12'h000;                       //Ĭ��Ϊ��ɫ
end
endmodule
