function new_datos = GetSamples(port,SampleQty)

new_datos = zeros(1,SampleQty);

binarydata = fread(port,4*SampleQty);

i=0;
while i<SampleQty
    inx = 2 + 4*i;
    new_datos(i+1) = bitshift( binarydata(inx), 8) + binarydata(inx+1);
    i = i+1;
end

end