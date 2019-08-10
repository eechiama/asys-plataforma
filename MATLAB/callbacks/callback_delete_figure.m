function callback_delete_figure(hObj, event)

if( exist('hs.Serial') ==  1)
    fclose(hs.Serial);
end

% borro todos los objetos serial port creados en matlab.
if ( ~isempty(instrfind) )
    fclose(instrfindall);
    delete(instrfindall);
end

end