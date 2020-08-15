function callback_Serial_Open(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');

% Si ya se abrió exitosamente un puerto:
if(info.SerialOpened == 1)
    errordlg('Ya se abrió un puerto serie.');
    return;
end

% Por las dudas, borro todos los objetos serial port creados en matlab.
if ( ~isempty(instrfind) )
    fclose(instrfindall);
    delete(instrfindall);
end

% Obtengo info sobre puertos serie disponibles
A = instrhwinfo('serial');
% if ( isempty(A.AvailableSerialPorts) )
%     errordlg('No hay ningún puerto serie disponible.');
%     return;
% end

path = get( hs.Edit_Port, 'string' );

% Verifico que el puerto especifiado figure como puerto serie
inx = find( ismember(A.AvailableSerialPorts, path) ) ;
if ( isempty(inx) )
    errordlg('No se pudo encontrar el puerto serie especificado.');
    return;
end

hs.Serial = serial(path);
pause(0.3);

set(hs.Serial,'baudrate',115200);
set(hs.Serial,'databits',8);
set(hs.Serial,'parity','n');
set(hs.Serial,'stopbits',1);
set(hs.Serial,'timeout',40); %4 segundos para el timeout.
set(hs.Serial,'InputBufferSize',160384);
set(hs.Serial,'OutputBufferSize',160384);

fopen(hs.Serial);
fprintf(hs.Serial,'$M0#');

% actualizo el flag asociado a la gui
info.SerialOpened=1;
setappdata(hs.Figure,'info',info);

guidata(hObj.Parent,hs);

msgbox('Puerto Serie abierto exitosamente.');
end