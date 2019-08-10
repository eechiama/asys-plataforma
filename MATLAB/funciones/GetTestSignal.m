function signal = GetTestSignal(port)

signal = zeros(1,85);
new_datos = fread(port,3*85);

i=0;
while i<85
    inx = 2 + 3*i;
    signal(i+1) = new_datos(inx);
    i = i+1;
end

end