l = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,545.4,$GPRMC,220516\n\r$GPRMC,203522.00,A,5109.0262308,N,11401.8407342,W,0.004,133.4,130522,0.0,E,D*2B"
for i in l : 
    print("S1IN='"+i+"';")
    print("swatch(0.01);")