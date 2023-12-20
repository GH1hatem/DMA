signal void send_line (void) {

	
swatch(0.01);  /* Wait 1/100 seconds */
S1IN='B';      /* Send a C */
swatch(0.01);
S1IN='O';
swatch(0.01);
S1IN='N';
swatch(0.01);  /* Wait 1/100 seconds */
S1IN='J';      /* Send a C */
swatch(0.01);
S1IN='O';
swatch(0.01);
S1IN='U';
swatch(0.01);
S1IN='R';
swatch(0.01);
S1IN='$';
}