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


%% real time plot
%   if( isempty(handles.AnimLine) )
%      handles.AnimLine = animatedline;
%      xlim([0 10]);
%      ylim([0 4096]);
%   end
%   
%   addpoints(handles.AnimLine,new_dato(1),new_dato(2));
%   drawnow;
%   
%   % chequeo si llegó al límite del eje x
%   lim=get(gca,'xlim');
%   if(  new_dato(1)>=lim(2) )
%     xlim([lim(2) lim(2)+5]);
%   end
