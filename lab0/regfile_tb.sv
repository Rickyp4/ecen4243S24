module stimulus ();

    logic         clk; 
	logic 	    we3; 
	logic [4:0]   ra1, ra2, wa3; 
	logic [31:0]  wd3;
	logic [31:0] rd1, rd2;

   regfile rw (clk, we3, ra1, ra2, wa3, wd3, rd1, rd2);
   

   // Setup the clock to toggle every 1 time units 
   initial 
     begin	
	clk = 1'b1;
	forever #5 clk = ~clk;
     end

   initial
     begin
	// Gives output file name
	// Tells when to finish simulation
	#500 $finish;		
     end
   
   initial 
     begin      
    #0 ra1 = 5'b0;
    #0 ra2 = 5'b0;
    #0 wa3 = 5'b0;
    #0 wd3 = 32'b0;
    #0 we3 = 1'b0;
    #20 we3 = 1'b1;
    #5 wa3 = 5'b10010;
     #0 wd3 = 32'b01011101010101011111010101010110;
     #5 ra1 = 5'b10010;
     #10 wa3 = 5'b01101;
     #0 wd3 = 32'b01010101010101010101010101010110;
     #5 ra2 = 5'b01101;
    #20 we3 = 1'b1;
     #5 wa3 = 5'b11110;
     #0 wd3 = 32'b00000101010101010001010101010110;
     #5 ra1 = 5'b11110;
     #10 wa3 = 5'b00001;
     #0 wd3 = 32'b00000000000000000000000000000111;
     #5 ra2 = 5'b00001;
     end

endmodule // FSM_tb

