module stimulus ();

     logic         clk, 
	logic 	    we3, 
	logic [4:0]   ra1, ra2, wa3, 
	logic [31:0]  wd3, 
	logic [31:0] rd1, rd2

   // Instantiate DUT
   FSM dut (Out, reset_b, clock, In);

   //regfile rw (clock, In, ra1, ra2, wa3, wd3, rd1, rd2);
   

   // Setup the clock to toggle every 1 time units 
   initial 
     begin	
	clock = 1'b1;
	forever #5 clock = ~clock;
     end

   initial
     begin
	// Gives output file name
	handle3 = $fopen("test.out");
	// Tells when to finish simulation
	#500 $finish;		
     end

   always 
     begin
	desc3 = handle3;
	#5 $fdisplay(desc3, "%b %b || %b", 
		     reset_b, In, Out);
     end   
   
   initial 
     begin      
	#0  reset_b = 1'b0;
	#12 reset_b = 1'b1;	
	#0  In = 1'b0;
	#20 In = 1'b1;
	#20 In = 1'b0;
     #25 ra1 = 5'b10010
     #0 ra2 = 5'b01101
     #0 wa3 = 5'b01010
     #0 wd3 = 32'b01010101010101010101010101010110
     end

endmodule // FSM_tb

