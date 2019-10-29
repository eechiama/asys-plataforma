function callback_guardar_muestras(hObj, event)

hs = guidata(hObj.Parent);
info = getappdata(hs.Figure,'info');
muestras = getappdata(hs.Figure,'muestras');

% CHEQUEOS

ll=length(muestras);
if ll==0
    errordlg('No hay muestras para guardar.');
    return
end

if info.Sampling == 1
    errordlg('No se pueden guardar muestras mientras se está muestreando.');
    return
end

% bytes_remaining = get(handles.SerialPort, 'bytesavailable');
% if bytes_remaining ~= 0
%     msgbox('Aún hay muestras en el buffer del puerto serie.');
%     %return;
% end

% crear el archivo, w es write y discard existing contents
path = get( hs.Edit_File, 'string' );
hs.File=fopen(path,'wt');
fprintf(hs.File, '% Datos\n');

% escribo las muestras
i=1;
while i <= ll
    fprintf(hs.File,'%d\n',muestras(i));
    i= i + 1;
end

% cierro el archivo
fclose(hs.File);

msgbox('Muestras guardadas.');

end